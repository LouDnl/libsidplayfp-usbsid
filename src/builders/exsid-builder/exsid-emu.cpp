/***************************************************************************
             exsid.cpp  -  exSID support interface.
                             -------------------
   Based on hardsid.cpp (C) 2001 Jarno Paananen

    copyright            : (C) 2015 Thibaut VARENE
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation.                            *
 *                                                                         *
 ***************************************************************************/

#include "exsid-emu.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sstream>

#include "driver/exSID.h"

namespace libsidplayfp
{

unsigned int exSID::sid = 0;

const char* exSID::getCredits()
{
    static std::string credits;

    if (credits.empty())
    {
        // Setup credits
        std::ostringstream ss;
        ss << "exSID V" << VERSION << " Engine:\n";
        ss << "\t(C) 2015 Thibaut VARENE\n";
        credits = ss.str();
    }

	return credits.c_str();
}

exSID::exSID(sidbuilder *builder) :
    sidemu(builder),
    m_instance(sid++),
    m_status(false),
    m_locked(false),
    m_optimisation(0)
{
    if (exSID_init() < 0)
        return;

    m_status = true;
    sidemu::reset();
}

exSID::~exSID()
{
    sid--;
    exSID_exit();
}

void exSID::reset(uint8_t volume)
{
    exSID_reset(volume);
    m_accessClk = 0;
}

unsigned int exSID::delay()
{
    event_clock_t cycles = eventScheduler->getTime(m_accessClk, EVENT_CLOCK_PHI1);
    m_accessClk += cycles;

    while (cycles > 0xffff)
    {
        exSID_delay(0xffff);
        cycles -= 0xffff;
    }

    return static_cast<unsigned int>(cycles);
}

void exSID::clock()
{
    const unsigned int cycles = delay();

    if (cycles)
        exSID_delay(cycles);
}

uint8_t exSID::read(uint_least8_t addr)
{
    const unsigned int cycles = delay();

    if (addr < 0x19 || addr > 0x1C)
    {
        if (cycles)
            exSID_delay(cycles);
        return 0x00;
    }

    //printf("in read, cycles: %d, addr: %hhx\n", cycles, addr);

    return exSID_clkdread(cycles, addr);
}

void exSID::write(uint_least8_t addr, uint8_t data)
{
    const unsigned int cycles = delay();

    if (addr > 0x18)
    {
        if (cycles)
            exSID_delay(cycles);
        return;
    }

    //printf("in write, cycles: %d, addr: %hhx, data: %hhx\n", cycles, addr, data);
    exSID_clkdwrite(cycles, addr, data);
}

void exSID::voice(unsigned int num, bool mute)
{
    // XXX NOT IMPLEMENTED
    printf("%s() not implemented. num: %d, mute: %d\n", __func__, num, mute);
}

void exSID::model(SidConfig::sid_model_t model)
{
    exSID_chipselect(model == SidConfig::MOS8580 ? XS_CS_CHIP1 : XS_CS_CHIP0);
}

void exSID::flush() {}

bool exSID::lock(EventScheduler* env)
{
    return sidemu::lock(env);
}

void exSID::unlock()
{
    sidemu::unlock();
}

// Set optimisation level
void exSID::optimisation(uint_least8_t level)
{
    m_optimisation = level;
    if (level)
        printf("WARNING: Optimisation active, timing accuracy not guaranteed!\n");
}

}