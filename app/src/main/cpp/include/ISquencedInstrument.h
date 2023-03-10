#include "MusicConsts.h"

namespace mjmitchelldev_androidsynth {
    class ISequencedInstrument {
        public:
            virtual ~ISequencedInstrument() = default;

            virtual void SetNote(Note note) = 0;
            virtual void ReleaseNote(Note note) = 0;
            virtual void StartPlaying() = 0;
            virtual void StopPlaying() = 0;
    };
}