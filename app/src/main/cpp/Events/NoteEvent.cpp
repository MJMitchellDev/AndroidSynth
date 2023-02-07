#include "NoteEvent.h"

namespace mjmitchelldev_androidsynth {
    Note_Event_Type NoteEvent::GetEventType() {
        return _eventType;
    }

    Note NoteEvent::GetNote() {
        return _note;
    }

    int NoteEvent::GetDeltaFromLastEventInMs() {
        return _deltaInMs;
    }

    int NoteEvent::GetChannel() {
        return _channel;
    }
}