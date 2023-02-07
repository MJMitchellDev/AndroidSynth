#include "ChannelSequencer.h"

namespace mjmitchelldev_androidsynth {
    void ChannelSequencer::TickFrame() {
        _currentFrame += 1;

        auto totalTime = _currentFrame / _sampleRate;

        while (_nextEvent && _nextEvent->GetDeltaFromLastEventInMs() >= totalTime - _lastEventInMs)
        {
            processEvent(_nextEvent);
            SetNextEvent();
            _lastEventInMs = totalTime;
        }
    }

    void ChannelSequencer::processEvent(const std::shared_ptr<NoteEvent>& event) {
        switch (event->GetEventType()) {
            case Note_On:
                _signalGenerator->SetNote(event->GetNote());
                break;
            case Note_Off:
                _signalGenerator->ReleaseNote(event->GetNote());
                break;
            default:
                break;
        }
    }

    void ChannelSequencer::QueueEvents(std::vector<std::shared_ptr<NoteEvent>> events) {
        for (const auto& event : events)
            QueueEvent(event);
    }

    void ChannelSequencer::QueueEvent(std::shared_ptr<NoteEvent> event) {
        _eventQueue.push(event);

        if (!_nextEvent)
        {
            SetNextEvent();
        }
    }

    void ChannelSequencer::SetNextEvent() {
        _nextEvent = _eventQueue.front();
        _eventQueue.pop();
    }
}