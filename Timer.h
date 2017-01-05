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

class Timer : public StopwatchBase
{
private:
    uint64_t m_initialValue;
    
public:
    Timer(uint64_t initialValue) : StopwatchBase(), m_initialValue(initialValue) {};
    ~Timer() {};

    uint64_t getInitialValue() { return m_initialValue; };
    uint64_t getCurrentValue() override { return getInitialValue() - getElapsedMillis(); };
    bool checkIfFinished() override { return ((int32_t)(getInitialValue() - getElapsedMillis())) <= 0; };
    void finish() { StopwatchBase::finish(); setElapsedMillis(0); };
};
