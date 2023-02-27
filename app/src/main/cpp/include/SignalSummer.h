#pragma once

#include <vector>
#include <memory>
#include "IAudioSource.h"

namespace mjmitchelldev_androidsynth {
    class SignalSummer : public IAudioSource {
        public:
            SignalSummer(std::vector<std::unique_ptr<IAudioSource>> soundGenerators);
            float GetSample() override;
            void OnPlaybackStopped() override;

        protected:
            std::vector<std::unique_ptr<IAudioSource>> _soundGenerators;
    };
}