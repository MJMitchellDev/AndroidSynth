//
// Created by lazza on 07/02/2023.
//

#ifndef ANDROIDSYNTH_NOTEEVENT_H
#define ANDROIDSYNTH_NOTEEVENT_H

#include "MusicConsts.h"

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
}

#endif //ANDROIDSYNTH_NOTEEVENT_H
