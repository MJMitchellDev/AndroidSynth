#include "ChannelSequencer.h"

namespace mjmitchelldev_androidsynth {
    ChannelSequencer::ChannelSequencer(std::unique_ptr<ISequencedInstrument> instrument, float sampleRate)
    : _currentFrame(0), _lastEventInMs(0.0f) {
        _signalGenerator = std::move(instrument);
        _sampleRate = sampleRate;
    }

    void ChannelSequencer::TickFrame() {
        _currentFrame += 1;

        auto totalTime = (static_cast<float>(_currentFrame) / _sampleRate) * 1000;

        //Get all events that should have fired between this and the last frame
        while (_nextEvent && (static_cast<float>(_nextEvent->GetDeltaFromLastEventInMs()) <= totalTime - _lastEventInMs))
        {
            _lastEventInMs += static_cast<float>(_nextEvent->GetDeltaFromLastEventInMs());
            processEvent(_nextEvent);
            SetNextEvent();
        }
    }

    void ChannelSequencer::processEvent(std::unique_ptr<NoteEvent> const &event) {
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

    void ChannelSequencer::QueueEvents(std::vector<std::unique_ptr<NoteEvent>> events) {
        for (auto & event : events)
        {
            QueueEvent(std::move(event));
        }
    }

    void ChannelSequencer::QueueEvent(std::unique_ptr<NoteEvent> event) {
        _eventQueue.push(std::move(event));

        if (!_nextEvent)
        {
            SetNextEvent();
        }
    }

    void ChannelSequencer::SetNextEvent() {
        if (_eventQueue.empty()){
            _nextEvent = nullptr;
            return;
        }

        _nextEvent = std::move(_eventQueue.front());
        _eventQueue.pop();
    }
}