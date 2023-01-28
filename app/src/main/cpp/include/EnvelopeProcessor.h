#pragma once

#include "AudioSource.h"
#include <memory>

namespace wavetablesynthesizer {

    enum class EnvelopeState { ATTACK, SUSTAIN, DECAY, RELEASE };

    class EnvelopeProcessor : public AudioSource {
        public:
            EnvelopeProcessor(std::shared_ptr<AudioSource> soundGenerator,
                float sampleRate);
            float getSample() override;
            void onPlaybackStopped() override;

        protected:
            std::shared_ptr<AudioSource> _soundGenerator;

        private:
            const float SustainGain = 0.9f;
            const float AttackTimeInSeconds = 1.3f;
            const float DecayTimeInSeconds = 1.3f;
            const float SustainTimeInSeconds = 3.0f;

            float _sampleRate;
            int64_t _currentFrame;
            EnvelopeState _state;

            void processState();
    };
}