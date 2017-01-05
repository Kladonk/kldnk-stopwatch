/******************************************************************************
    Kladonk Stopwatch Plugin
    Copyright(C) 2016-2017 Jan Held <development@kladonk.de>

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#pragma once

#include "StopwatchBase.h"

class Stopwatch : public StopwatchBase
{
private:
    uint64_t m_maxMillis;

public:
    Stopwatch(uint64_t maxMillis) : StopwatchBase(), m_maxMillis(maxMillis) {};
    ~Stopwatch() {};

    uint64_t getMaxMillis() { return m_maxMillis; };

    bool checkIfFinished() override { return getMaxMillis() > 0 && getElapsedMillis() >= getMaxMillis(); };

    void finish() { StopwatchBase::finish(); setElapsedMillis(m_maxMillis); };
};
