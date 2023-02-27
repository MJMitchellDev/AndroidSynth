//
// Created by lazza on 23/02/2023.
//

#ifndef ANDROIDSYNTH_FILTEREDSQUAREWAVEINSTRUMENT_H
#define ANDROIDSYNTH_FILTEREDSQUAREWAVEINSTRUMENT_H

#include "ISquencedInstrument.h"
#include "IOscillator.h"
#include "IOscillatorFactory.h"
#include "IAudioSource.h"
#include <vector>

namespace mjmitchelldev_androidsynth {
    class FilteredSquareWaveInstrument : public IAudioSource, public ISequencedInstrument {
        public:
            FilteredSquareWaveInstrument(std::unique_ptr<IOscillatorFactory> oscillatorFactory);

            void SetNote(Note note) override;
            void ReleaseNote(Note note) override;
            void StartPlaying() override;
            void StopPlaying() override;
        private:
            std::vector<std::unique_ptr<IOscillator>> _oscillators;
            std::unique_ptr<IAudioSource> _soundGenerator;
    };

} // mjmitchelldev_androidsynth

#endif //ANDROIDSYNTH_FILTEREDSQUAREWAVEINSTRUMENT_H
