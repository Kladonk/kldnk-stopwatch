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

#include "IStopwatch.h"
#include <list>
#include <memory>


class StopwatchBase : public IStopwatch
{
private:
    bool m_enabled;
    bool m_finished;
    uint64_t m_elapsedMillis;

    std::list<std::shared_ptr<IStopwatchEventListener>> m_eventListeners;
    std::list<std::shared_ptr<IStopwatchAction>> m_actions;

protected:
    StopwatchBase() { init(); };
    ~StopwatchBase() {};

    void init();

    virtual bool checkIfFinished() = 0;
    void finish();
    void setEnabled(bool enabled) { m_enabled = enabled; };
    void setFinished(bool finished) { m_finished = finished; };
    void setElapsedMillis(uint64_t elapsedMillis) { m_elapsedMillis = elapsedMillis; };
    void addElapsedMillis(uint64_t elapsedMillis) { m_elapsedMillis += elapsedMillis; };

    void fireEvent(IStopwatchEvent *event) { for (std::shared_ptr<IStopwatchEventListener> listener : m_eventListeners) { listener.get()->handle(event); }; delete event; };
    void executeActions()
    {
        for (std::shared_ptr<IStopwatchAction> action : m_actions)
        {
            IStopwatchAction *theAction = action.get();
            theAction->execute();
        }; 
    };

public:
    void start() override;
    void stop() override;
    void reset() override;
    void update(uint32_t elapsedMillis) override;
    uint64_t getCurrentValue() override { return getElapsedMillis(); };

    bool isEnabled() override { return m_enabled; };
    bool isFinished() override { return m_finished; };
    uint64_t getElapsedMillis() override { return m_elapsedMillis; };

    void addEventListener(IStopwatchEventListener *eventListener) override { m_eventListeners.push_back(std::shared_ptr<IStopwatchEventListener>(eventListener)); };
    void addAction(IStopwatchAction *action) override { m_actions.push_back(std::shared_ptr<IStopwatchAction>(action)); };
};
