#include "ChannelDistributingNoteSequencer.h"

namespace mjmitchelldev_androidsynth {

    void ChannelDistributingNoteSequencer::TickFrame() {
        for (const auto &[_, channel]: _channels)
            channel->TickFrame();
    }

    void ChannelDistributingNoteSequencer::QueueEvents(std::vector <std::shared_ptr<NoteEvent>> events) {
        for (const auto &event: events) {
            QueueEvent(event);
        }
    }

    void ChannelDistributingNoteSequencer::QueueEvent(std::shared_ptr <NoteEvent> event) {
        if (_channels.contains(event->GetChannel())) {
            _channels[event->GetChannel()]->QueueEvent(event);
        }
    }
}