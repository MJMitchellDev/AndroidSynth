#ifndef ANDROIDSYNTH_INOTESEQUENCER_H
#define ANDROIDSYNTH_INOTESEQUENCER_H

#include <vector>
#include <memory>
#include "NoteEvent.h"

namespace mjmitchelldev_androidsynth {
    class INoteSequencer {
        public:
            virtual ~INoteSequencer() = default;

            virtual void TickFrame() = 0;
            virtual void QueueEvent(std::unique_ptr<NoteEvent> event) = 0;
            virtual void QueueEvents(std::vector<std::unique_ptr<NoteEvent>> events) = 0;
    };
}

#endif //ANDROIDSYNTH_INOTESEQUENCER_H
