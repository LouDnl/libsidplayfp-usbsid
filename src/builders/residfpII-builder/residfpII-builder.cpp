/*
 * This file is part of libsidplayfp, a SID player engine.
 *
 * Copyright 2011-2025 Leandro Nini <drfiemost@users.sourceforge.net>
 * Copyright 2007-2010 Antti Lankila
 * Copyright 2001 Simon White
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

#include "residfpII.h"

#include <algorithm>
#include <new>
#include <utility>

#include "properties.h"
#include "residfpII-emu.h"

struct ReSIDfpIIBuilder::config
{
    Property<double> filter8580Curve;
    Property<double> filter6581Curve;
    Property<double> filter6581Range;
    Property<SidConfig::sid_cw_t> cws;
};


ReSIDfpIIBuilder::ReSIDfpIIBuilder(const char * const name) :
    sidbuilder(name),
    m_config(new config) {}

ReSIDfpIIBuilder::~ReSIDfpIIBuilder()
{
    // Remove all SID emulations
    remove();

    delete m_config;
}

// Create a new sid emulation.
libsidplayfp::sidemu* ReSIDfpIIBuilder::create()
{
    try
    {
        auto sid = new libsidplayfp::ReSIDfpII(this);
        if (m_config->filter6581Curve.has_value())
            sid->filter6581Curve(m_config->filter6581Curve.value());
        if (m_config->filter8580Curve.has_value())
            sid->filter8580Curve(m_config->filter8580Curve.value());
        if (m_config->filter6581Range.has_value())
            sid->filter6581Range(m_config->filter6581Range.value());
        if (m_config->cws.has_value())
            sid->combinedWaveforms(m_config->cws.value());
        return sid;
    }
    catch (std::bad_alloc const &)
    {
        // Memory alloc failed
        m_errorBuffer.assign(name()).append(" ERROR: Unable to create ReSIDfpII object");
        return nullptr;
    }

}

const char *ReSIDfpIIBuilder::getCredits() const
{
    return libsidplayfp::ReSIDfpII::getCredits();
}

void ReSIDfpIIBuilder::filter6581Curve(double filterCurve)
{
    m_config->filter6581Curve = filterCurve;
    for (libsidplayfp::sidemu* e: sidobjs)
        static_cast<libsidplayfp::ReSIDfpII*>(e)->filter6581Curve(filterCurve);
}

void ReSIDfpIIBuilder::filter6581Range(double filterRange)
{
    m_config->filter6581Range = filterRange;
    for (libsidplayfp::sidemu* e: sidobjs)
        static_cast<libsidplayfp::ReSIDfpII*>(e)->filter6581Range(filterRange);
}

void ReSIDfpIIBuilder::filter8580Curve(double filterCurve)
{
    m_config->filter8580Curve = filterCurve;
    for (libsidplayfp::sidemu* e: sidobjs)
        static_cast<libsidplayfp::ReSIDfpII*>(e)->filter8580Curve(filterCurve);
}

void ReSIDfpIIBuilder::combinedWaveformsStrength(SidConfig::sid_cw_t cws)
{
    m_config->cws = cws;
    for (libsidplayfp::sidemu* e: sidobjs)
        static_cast<libsidplayfp::ReSIDfpII*>(e)->combinedWaveforms(cws);
}
