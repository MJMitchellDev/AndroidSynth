#pragma once

#include "AudioSource.h"
#include <memory>

namespace mjmitchelldev_androidsynth {

    enum class EnvelopeState { ATTACK, SUSTAIN, DECAY, RELEASE };

    class EnvelopeProcessor : public AudioSource {
        public:
            EnvelopeProcessor(std::shared_ptr<AudioSource> soundGenerator,
                float sampleRate);
            float GetSample() override;
            void OnPlaybackStopped() override;

            void SetAdsr(float attack, float decay, float sustain, float release);
        protected:
            std::shared_ptr<AudioSource> _soundGenerator;

        private:
            float _sustainGain = 0.9f;
            float _attackTimeInSeconds = 1.3f;
            float _decayTimeInSeconds = 1.3f;
            float _sustainTimeInSeconds = 3.0f;
            float _releaseTimeInSeconds = 0.0f;

            float _sampleRate;
            int64_t _currentFrame;
            EnvelopeState _state;

            void processState();
    };
}