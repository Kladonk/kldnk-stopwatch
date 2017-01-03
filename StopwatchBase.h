#pragma once

#include "IStopwatch.h"
#include <list>

class StopwatchBase : public IStopwatch
{
private:
    bool m_enabled;
    bool m_finished;
    uint64_t m_elapsedMillis;

    std::list<IStopwatchEventListener*> m_eventListeners;
    std::list<IStopwatchAction*> m_actions;

protected:
    StopwatchBase() { init(); };
    ~StopwatchBase() {};

    void init();

    virtual bool checkIfFinished() = 0;
    void finish();
    void setElapsedMillis(uint64_t elapsedMillis) { m_elapsedMillis = elapsedMillis; };
    void addElapsedMillis(uint64_t elapsedMillis) { m_elapsedMillis += elapsedMillis; };

    void fireEvent(const IStopwatchEvent& event) { for (IStopwatchEventListener *listener : m_eventListeners) { listener->handle(event); }; };
    void executeActions() { for (IStopwatchAction *action : m_actions) { action->execute(); }; };

public:
    void start() override;
    void stop() override;
    void reset() override;
    void update(uint32_t elapsedMillis) override;
    uint64_t getCurrentValue() override { return getElapsedMillis(); };

    bool isEnabled() override { return m_enabled; };
    bool isFinished() override { return m_finished; };
    uint64_t getElapsedMillis() override { return m_elapsedMillis; };

    void addEventListener(IStopwatchEventListener& eventListener) override { m_eventListeners.push_back(&eventListener); };
    void removeEventListener(IStopwatchEventListener& eventListener) override { m_eventListeners.remove(&eventListener); };

    void addAction(IStopwatchAction& action) override { m_actions.push_back(&action); };
    void removeAction(IStopwatchAction& action) override { m_actions.remove(&action); };
};
