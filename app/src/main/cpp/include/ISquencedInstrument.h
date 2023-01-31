#include "MusicConsts.h"

namespace mjmitchelldev_androidsynth {
    class ISequencedInstrument {
        public:
            virtual void SetNote(Note note) = 0;
            virtual void StartPlaying() = 0;
            virtual void StopPlaying() = 0;
    };
}