#include "StopwatchBase.h"
#include "events/StopwatchStartEvent.h"
#include "events/StopwatchStopEvent.h"
#include "events/StopwatchResetEvent.h"


void StopwatchBase::init()
{
	m_enabled = false;
	m_finished = false;
	m_elapsedMillis = 0;
}


void StopwatchBase::start()
{
    m_enabled = true;
    fireEvent(StopwatchStartEvent(*this));
}


void StopwatchBase::stop()
{
    m_enabled = false;
    fireEvent(StopwatchStopEvent(*this));
}


void StopwatchBase::reset()
{
    init();
    fireEvent(StopwatchResetEvent(*this));
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
}
