#include "ChannelDistributingNoteSequencer.h"

namespace mjmitchelldev_androidsynth {

    void ChannelDistributingNoteSequencer::TickFrame() {
        for (const auto &[_, channel]: _channels)
            channel->TickFrame();
    }

    void ChannelDistributingNoteSequencer::QueueEvents(std::vector<std::unique_ptr<NoteEvent>> events) {
        for (auto & event : events)
        {
            QueueEvent(std::move(event));
        }
    }

    void ChannelDistributingNoteSequencer::QueueEvent(std::unique_ptr<NoteEvent> event)  {
        if (_channels.contains(event->GetChannel())) {
            auto channel = event->GetChannel();
            _channels[channel]->QueueEvent(std::move(event));
        }
    }
}