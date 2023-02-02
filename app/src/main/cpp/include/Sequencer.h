//
// Created by lazza on 29/01/2023.
//
#pragma once

#include <vector>
#include <memory>
#include <queue>
#include "ISquencedInstrument.h"

namespace mjmitchelldev_androidsynth {
    enum Note_Event_Type {
        Note_On, Note_Off
    };

    class NoteEvent {
        public:
            NoteEvent(int channel, Note_Event_Type eventType, int delta, Note note)
                : _channel(channel), _note(note), _eventType(eventType), _deltaInMs(delta)
            { }

            NoteEvent(int channel, Note_Event_Type eventType, int delta)
                    : _channel(channel), _eventType(eventType), _deltaInMs(delta)
            { }

            Note_Event_Type GetEventType();
            Note GetNote();
            int GetDeltaFromLastEventInMs();
            int GetChannel();
        private:
            int _channel;
            Note_Event_Type _eventType;
            Note _note;
            int _deltaInMs;
    };

    class INoteSequencer {
        public:
            virtual void TickFrame() = 0;
            virtual void QueueEvent(std::shared_ptr<NoteEvent> event) = 0;
            virtual void QueueEvents(std::vector<std::shared_ptr<NoteEvent>> events) = 0;
    };

    class ChannelSequencer : public INoteSequencer {
        public:
            void TickFrame() override;

        private:
            void processEvent(const std::shared_ptr<NoteEvent>& event);
            void QueueEvent(std::shared_ptr<NoteEvent> event) override;
            void QueueEvents(std::vector<std::shared_ptr<NoteEvent>> events) override;
            void SetNextEvent();

            std::shared_ptr<ISequencedInstrument> _signalGenerator;
            std::queue<std::shared_ptr<NoteEvent>> _eventQueue;
            float _lastEventInMs;
            int _currentFrame;

            std::shared_ptr<NoteEvent> _nextEvent;
            float _sampleRate;
    };

    class ChannelDistributingNoteSequencer : public INoteSequencer {
        public:
            void TickFrame() override;
            void QueueEvent(std::shared_ptr<NoteEvent> event) override;
            void QueueEvents(std::vector<std::shared_ptr<NoteEvent>> events) override;

        protected:
        private:
            std::map<int, std::shared_ptr<INoteSequencer>> _channels;
    };

}