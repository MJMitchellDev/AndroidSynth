#pragma once

#include <vector>
#include <memory>
#include <queue>
#include "ISquencedInstrument.h"
#include "INoteSequencer.h"

namespace mjmitchelldev_androidsynth {
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
}