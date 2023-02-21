#pragma once

#include <vector>
#include <memory>
#include <queue>
#include "ISquencedInstrument.h"
#include "INoteSequencer.h"

namespace mjmitchelldev_androidsynth {
    class ChannelSequencer : public INoteSequencer {
        public:
            ChannelSequencer(std::unique_ptr<ISequencedInstrument> instrument, float sampleRate);

            void TickFrame() override;
            void QueueEvent(std::unique_ptr<NoteEvent> event) override;
            void QueueEvents(std::vector<std::unique_ptr<NoteEvent>> events) override;
        private:
            void processEvent(std::unique_ptr<NoteEvent> const &event);
            void SetNextEvent();

            std::unique_ptr<ISequencedInstrument> _signalGenerator;
            std::queue<std::unique_ptr<NoteEvent>> _eventQueue;
            float _lastEventInMs;
            int _currentFrame;

            std::unique_ptr<NoteEvent> _nextEvent;
            float _sampleRate;
    };
}