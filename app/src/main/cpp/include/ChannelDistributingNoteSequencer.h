#ifndef ANDROIDSYNTH_CDNS_H
#define ANDROIDSYNTH_CDNS_H

#include "INoteSequencer.h"

namespace mjmitchelldev_androidsynth {
    class ChannelDistributingNoteSequencer : public INoteSequencer {
        public:
            void TickFrame() override;
            void QueueEvent(std::unique_ptr<NoteEvent> event) override;
            void QueueEvents(std::vector<std::unique_ptr<NoteEvent>> events) override;

        protected:
        private:
            std::map<int, INoteSequencer*> _channels;
    };
}

#endif