//
// Created by lazza on 29/01/2023.
//

#include "include/Sequencer.h"

namespace mjmitchelldev_androidsynth {

    void ChannelDistributingNoteSequencer::tickFrame() {
        for (const auto& [_, channel] : _channels)
            channel->tickFrame();
    }

    void ChannelDistributingNoteSequencer::queueEvents(std::vector<std::shared_ptr<NoteEvent>> events) {
        for (const auto& event : events)
        {
            queueEvent(event);
        }
    }

    void ChannelDistributingNoteSequencer::queueEvent(std::shared_ptr<NoteEvent> event) {
        if (_channels.contains(event->GetChannel()))
        {
            _channels[event->GetChannel()]->queueEvent(event);
        }
    }

    void ChannelSequencer::tickFrame() {
        _currentFrame += 1;

        auto totalTime = _currentFrame / _sampleRate;

        while (_nextEvent && _nextEvent->GetDeltaFromLastEventInMs() >= totalTime - _lastEventInMs)
        {
            processEvent(_nextEvent);
            _nextEvent = _eventQueue.front();
            _eventQueue.pop();
            _lastEventInMs = totalTime;
        }
    }

    void ChannelSequencer::processEvent(const std::shared_ptr<NoteEvent>& event) {
        if (event->GetEventType() == Note_On)
        {
            _signalGenerator->SetNote(event->GetNote());
            _signalGenerator->StartPlaying();
        }
        else
        {
            _signalGenerator->StopPlaying();
        }
    }

    void ChannelSequencer::queueEvents(std::vector<std::shared_ptr<NoteEvent>> events) {
        for (const auto& event : events)
            queueEvent(event);
    }

    void ChannelSequencer::queueEvent(std::shared_ptr<NoteEvent> event) {
        _eventQueue.push(event);

        if (!_nextEvent)
        {
            _nextEvent = _eventQueue.front();
            _eventQueue.pop();
        }
    }

    Note_Event_Type NoteEvent::GetEventType() {
        return _eventType;
    }

    Note NoteEvent::GetNote() {
        return _note;
    }

    u_int64_t NoteEvent::GetDeltaFromLastEventInMs() {
        return _deltaInMs;
    }

    int NoteEvent::GetChannel() {
        return _channel;
    }
}