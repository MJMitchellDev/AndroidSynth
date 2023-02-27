#pragma once

#include <memory>
#include "IAudioSource.h"

namespace mjmitchelldev_androidsynth {
    class IAudioPlayer {
        public:
            virtual ~IAudioPlayer() = default;
            virtual int32_t Play() = 0;
            virtual void Stop() = 0;
            virtual void SetSampleRate(float sampleRate) = 0;
            virtual void SetAudioSource(std::shared_ptr<IAudioSource> audioSource) = 0;
    };
}
