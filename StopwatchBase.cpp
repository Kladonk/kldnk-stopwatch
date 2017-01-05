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

#include "StopwatchBase.h"
#include "events/StopwatchStartEvent.h"
#include "events/StopwatchStopEvent.h"
#include "events/StopwatchResetEvent.h"
#include "events/StopwatchFinishEvent.h"


void StopwatchBase::init()
{
	m_enabled = false;
	m_finished = false;
	m_elapsedMillis = 0;
}


void StopwatchBase::start()
{
    m_enabled = true;
    fireEvent(new StopwatchStartEvent(*this));
}


void StopwatchBase::stop()
{
    m_enabled = false;
    fireEvent(new StopwatchStopEvent(*this));
}


void StopwatchBase::reset()
{
    init();
    fireEvent(new StopwatchResetEvent(*this));
}


void StopwatchBase::update(uint32_t elapsedMillis)
{
	if (isEnabled() && !isFinished())
	{
		addElapsedMillis(elapsedMillis);

		if (checkIfFinished())
		{
			finish();
		}
	}
}


void StopwatchBase::finish()
{
	m_enabled = false;
	m_finished = true;
	fireEvent(new StopwatchFinishEvent(*this));
    executeActions();
}
