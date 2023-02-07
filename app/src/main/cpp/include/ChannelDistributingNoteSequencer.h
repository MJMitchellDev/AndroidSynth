#ifndef ANDROIDSYNTH_CDNS_H
#define ANDROIDSYNTH_CDNS_H

#include "INoteSequencer.h"
#include <vector>
#include <memory>
#include <queue>

namespace mjmitchelldev_androidsynth {
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

#endif