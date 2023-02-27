#pragma once

#include "IAudioSource.h"
#include <memory>

namespace mjmitchelldev_androidsynth {

    enum class EnvelopeState { ATTACK, SUSTAIN, DECAY, RELEASE };

    class EnvelopeProcessor : public IAudioSource {
        public:
            EnvelopeProcessor(IAudioSource & soundGenerator,
                float sampleRate);
            float GetSample() override;
            void OnPlaybackStopped() override;

            void SetAdsr(float attack, float decay, float sustain, float release);
            void SetSustainGain(float sustainGain);
        protected:
            IAudioSource *_soundGenerator;

        private:
            float _sustainGain = 0.9f;
            float _attackPeakGain = 1.0f;
            
            float _attackTimeInSeconds = 1.3f;
            float _decayTimeInSeconds = 1.3f;
            float _sustainTimeInSeconds = 3.0f;
            float _releaseTimeInSeconds = 0.0f;

            float _sampleRate;
            int64_t _currentFrameInCycle;
            EnvelopeState _state;

            void processState();
            float GetDecayValue(float sample);
    };
}