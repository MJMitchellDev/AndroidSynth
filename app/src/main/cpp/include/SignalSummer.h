#pragma once

#include <vector>
#include <memory>
#include "AudioSource.h"

namespace mjmitchelldev_androidsynth {
    class SignalSummer : public AudioSource {
        public:
            SignalSummer(std::vector<std::shared_ptr<AudioSource>> soundGenerators);
            float GetSample() override;
            void OnPlaybackStopped() override;

        protected:
            std::vector<std::shared_ptr<AudioSource>> _soundGenerators;
    };
}