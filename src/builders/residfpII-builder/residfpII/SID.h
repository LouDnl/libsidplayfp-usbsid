/*
 * This file is part of libsidplayfp, a SID player engine.
 *
 * Copyright 2011-2025 Leandro Nini <drfiemost@users.sourceforge.net>
 * Copyright 2007-2010 Antti Lankila
 * Copyright 2004 Dag Lem <resid@nimrod.no>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SIDFP_H
#define SIDFP_H

#include <memory>
#include <cassert>
#include <cmath>
#include <cstdint>

#include "siddefs-fpII.h"
#include "ExternalFilter.h"
#include "Potentiometer.h"
#include "Voice.h"

#include "sidcxx11.h"

namespace reSIDfpII
{

class Filter;
class Filter6581;
class Filter8580;
class Resampler;

/**
 * SID error exception.
 */
class SIDError
{
private:
    const char* message;

public:
    SIDError(const char* msg) :
        message(msg) {}
    const char* getMessage() const { return message; }
};

/**
 * MOS6581/MOS8580 emulation.
 */
class SID
{
private:
    template<int m>
    static inline int clipper(float x)
    {
        assert(!std::signbit(x));
        constexpr float threshold = 28000.f;
        if (likely(x < threshold))
            return x;

        constexpr float max_val = static_cast<float>(m);
        constexpr float t = threshold / max_val;
        constexpr float a = 1. - t;
        constexpr float b = 1. / a;

        float value = (x - threshold) / max_val;
        value = t + a * std::tanh(b * value);
        return static_cast<int>(value * max_val);
    }

    /*
     * Soft Clipping implementation, splitted for test.
     */
    static inline int softClipImpl(float x)
    {
        return std::signbit(x) ? -clipper<32768>(-x) : clipper<32767>(x);
    }

    /*
     * Soft Clipping into 16 bit range [-32768,32767]
     */
    static inline short softClip(float x) { return static_cast<short>(softClipImpl(x)); }

private:
    /// Currently active filter
    Filter* filter;

    /// Filter used, if model is set to 6581
    Filter6581* const filter6581;

    /// Filter used, if model is set to 8580
    Filter8580* const filter8580;

    /// Resampler used by audio generation code.
    std::unique_ptr<Resampler> resampler;

    /**
     * External filter that provides high-pass and low-pass filtering
     * to adjust sound tone slightly.
     */
    ExternalFilter externalFilter;

    /// Paddle X register support
    Potentiometer potX;

    /// Paddle Y register support
    Potentiometer potY;

    /// SID voices
    Voice voice[3];

    /// Used to amplify the output by x/2 to get an adequate playback volume
    int scaleFactor;

    /// Time to live for the last written value
    int busValueTtl;

    /// Current chip model's bus value TTL
    int modelTTL;

    /// Time until #voiceSync must be run.
    unsigned int nextVoiceSync;

    /// Currently active chip model.
    ChipModel model;

    /// Currently selected combined waveforms strength.
    CombinedWaveforms cws;

    /// Last written value
    unsigned char busValue;

    /**
     * Emulated nonlinearity of the envelope DAC.
     *
     * @See Dac
     */
    float envDAC[256];

    /**
     * Emulated nonlinearity of the oscillator DAC.
     *
     * @See Dac
     */
    float oscDAC[4096];

private:
    /**
     * Age the bus value and zero it if it's TTL has expired.
     *
     * @param n the number of cycles
     */
    void ageBusValue(unsigned int n);

    /**
     * Calculate the numebr of cycles according to current parameters
     * that it takes to reach sync.
     *
     * @param sync whether to do the actual voice synchronization
     */
    void voiceSync(bool sync);

public:
    SID();
    ~SID();

    /**
     * Set chip model.
     *
     * @param model chip model to use
     * @throw SIDError
     */
    void setChipModel(ChipModel model);

    /**
     * Get currently emulated chip model.
     */
    ChipModel getChipModel() const { return model; }

    /**
     * Set combined waveforms strength.
     *
     * @param cws strength of combined waveforms
     * @throw SIDError
     */
    void setCombinedWaveforms(CombinedWaveforms cws);

    /**
     * SID reset.
     */
    void reset();

    /**
     * 16-bit input (EXT IN). Write 16-bit sample to audio input. NB! The caller
     * is responsible for keeping the value within 16 bits. Note that to mix in
     * an external audio signal, the signal should be resampled to 1MHz first to
     * avoid sampling noise.
     *
     * @param value input level to set
     */
    void input(int value);

    /**
     * Read registers.
     *
     * Reading a write only register returns the last char written to any SID register.
     * The individual bits in this value start to fade down towards zero after a few cycles.
     * All bits reach zero within approximately $2000 - $4000 cycles.
     * It has been claimed that this fading happens in an orderly fashion,
     * however sampling of write only registers reveals that this is not the case.
     * NOTE: This is not correctly modeled.
     * The actual use of write only registers has largely been made
     * in the belief that all SID registers are readable.
     * To support this belief the read would have to be done immediately
     * after a write to the same register (remember that an intermediate write
     * to another register would yield that value instead).
     * With this in mind we return the last value written to any SID register
     * for $2000 cycles without modeling the bit fading.
     *
     * @param offset SID register to read
     * @return value read from chip
     */
    unsigned char read(int offset);

    /**
     * Write registers.
     *
     * @param offset chip register to write
     * @param value value to write
     */
    void write(int offset, unsigned char value);

    /**
     * Setting of SID sampling parameters.
     *
     * Use a clock freqency of 985248Hz for PAL C64, 1022730Hz for NTSC C64.
     * The default end of passband frequency is pass_freq = 0.9*sample_freq/2
     * for sample frequencies up to ~ 44.1kHz, and 20kHz for higher sample frequencies.
     *
     * For resampling, the ratio between the clock frequency and the sample frequency
     * is limited as follows: 125*clock_freq/sample_freq < 16384
     * E.g. provided a clock frequency of ~ 1MHz, the sample frequency can not be set
     * lower than ~ 8kHz. A lower sample frequency would make the resampling code
     * overfill its 16k sample ring buffer.
     *
     * The end of passband frequency is also limited: pass_freq <= 0.9*sample_freq/2
     *
     * E.g. for a 44.1kHz sampling rate the end of passband frequency
     * is limited to slightly below 20kHz.
     * This constraint ensures that the FIR table is not overfilled.
     *
     * @param clockFrequency System clock frequency at Hz
     * @param method sampling method to use
     * @param samplingFrequency Desired output sampling rate
     * @param highestAccurateFrequency
     * @throw SIDError
     */
    void setSamplingParameters(
        double clockFrequency,
        SamplingMethod method,
        double samplingFrequency
    );

    /**
     * Clock SID forward using chosen output sampling algorithm.
     *
     * @param cycles c64 clocks to clock
     * @param buf audio output buffer
     * @return number of samples produced
     */
    int clock(unsigned int cycles, short* buf);

    /**
     * Clock SID forward with no audio production.
     *
     * _Warning_:
     * You can't mix this method of clocking with the audio-producing
     * clock() because components that don't affect OSC3/ENV3 are not
     * emulated.
     *
     * @param cycles c64 clocks to clock.
     */
    void clockSilent(unsigned int cycles);

    /**
     * Set filter curve parameter for 6581 model.
     *
     * @see Filter6581::setFilterCurve(double)
     */
    void setFilter6581Curve(double filterCurve);

    /**
    * Set filter range parameter for 6581 model
    *
    * @see Filter6581::setFilterRange(double)
    */
    void setFilter6581Range ( double adjustment );

    /**
     * Set filter curve parameter for 8580 model.
     *
     * @see Filter8580::setFilterCurve(double)
     */
    void setFilter8580Curve(double filterCurve);

    /**
     * Enable filter emulation.
     *
     * @param enable false to turn off filter emulation
     */
    void enableFilter(bool enable);
};

} // namespace reSIDfpII

#if RESID_INLINING || defined(SID_CPP)

#include <algorithm>

#include "Filter.h"
#include "ExternalFilter.h"
#include "Voice.h"
#include "resample/Resampler.h"

namespace reSIDfpII
{

RESID_INLINE
void SID::ageBusValue(unsigned int n)
{
    if (likely(busValueTtl != 0))
    {
        busValueTtl -= n;

        if (unlikely(busValueTtl <= 0))
        {
            busValue = 0;
            busValueTtl = 0;
        }
    }
}

RESID_INLINE
int SID::clock(unsigned int cycles, short* buf)
{
    ageBusValue(cycles);
    int s = 0;

    while (cycles != 0)
    {
        unsigned int delta_t = std::min(nextVoiceSync, cycles);

        if (likely(delta_t > 0))
        {
            for (unsigned int i = 0; i < delta_t; i++)
            {
                // clock waveform generators
                voice[0].wave()->clock();
                voice[1].wave()->clock();
                voice[2].wave()->clock();

                // clock envelope generators
                voice[0].envelope()->clock();
                voice[1].envelope()->clock();
                voice[2].envelope()->clock();

                const float sidOutput = static_cast<float>(filter->clock(voice[0], voice[1], voice[2]));
                const float c64Output = externalFilter.clock(sidOutput);
                if (unlikely(resampler->input(c64Output)))
                {
                    buf[s++] = softClip(scaleFactor * resampler->output());
                }
            }

            cycles -= delta_t;
            nextVoiceSync -= delta_t;
        }

        if (unlikely(nextVoiceSync == 0))
        {
            voiceSync(true);
        }
    }

    return s;
}

} // namespace reSIDfpII

#endif

#endif
