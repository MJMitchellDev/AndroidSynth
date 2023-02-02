#pragma once

#include <memory>
#include "AudioSource.h"

namespace mjmitchelldev_androidsynth {
    class AudioPlayer {
        public:
            virtual ~AudioPlayer() = default;
            virtual int32_t Play() = 0;
            virtual void Stop() = 0;
            virtual void SetSampleRate(float sampleRate) = 0;
            virtual void SetAudioSource(std::shared_ptr<AudioSource> audioSource) = 0;
    };
}
