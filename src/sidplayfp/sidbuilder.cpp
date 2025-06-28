/*
 * This file is part of libsidplayfp, a SID player engine.
 *
 * Copyright 2011-2025 Leandro Nini <drfiemost@users.sourceforge.net>
 * Copyright 2007-2010 Antti Lankila
 * Copyright 2000-2001 Simon White
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

#include "sidbuilder.h"

#include "sidemu.h"

#include "sidcxx11.h"

libsidplayfp::sidemu *sidbuilder::lock(libsidplayfp::EventScheduler *env, SidConfig::sid_model_t model, bool digiboost)
{
    // create new emu
    if (libsidplayfp::sidemu* sid = create())
    {
        if (sid->lock(env))
        {
            sid->model(model, digiboost);
            sidobjs.insert(sid);
            return sid;
        }
        else
            delete sid;
    }

    // Unable to locate free SID
    m_errorBuffer.assign(name()).append(" ERROR: No available SIDs to lock");
    return nullptr;
}

void sidbuilder::unlock(libsidplayfp::sidemu *device)
{
    emuset_t::iterator it = sidobjs.find(device);
    if (it != sidobjs.end())
    {
        (*it)->unlock();
        // should we cache these for later use?
        sidobjs.erase(it);
        delete *it;
    }
}

void sidbuilder::remove()
{
    for (auto sidobj: sidobjs)
        delete sidobj;

    sidobjs.clear();
}

const char* sidbuilder::credits() const
{
    return getCredits();
}
