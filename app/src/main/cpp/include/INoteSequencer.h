#ifndef ANDROIDSYNTH_INOTESEQUENCER_H
#define ANDROIDSYNTH_INOTESEQUENCER_H

#include <memory>
#include "NoteEvent.h"

namespace mjmitchelldev_androidsynth {
    class INoteSequencer {
        public:
            virtual void TickFrame() = 0;
            virtual void QueueEvent(std::shared_ptr<NoteEvent> event) = 0;
            virtual void QueueEvents(std::vector<std::shared_ptr<NoteEvent>> events) = 0;
    };
}

#endif //ANDROIDSYNTH_INOTESEQUENCER_H
