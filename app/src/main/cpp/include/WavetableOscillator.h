#pragma once

#include <vector>
#include "AudioSource.h"
#include <atomic>

namespace mjmitchelldev_androidsynth {

    class WavetableOscillator : public AudioSource {
        public:
            WavetableOscillator() = default;
            WavetableOscillator(std::vector<float> waveTable, float sampleRate);

            float GetSample() override;
            virtual void SetFrequency(float frequency);
            virtual void SetAmplitude(float newAmplitude);
            void OnPlaybackStopped() override;
            virtual void SetWavetable(const std::vector<float> &wavetable);

        private:
            float InterpolateLinearly() const;
            void SwapWavetableIfNecessary();

            float index = 0.f;
            std::atomic<float> indexIncrement{0.f};
            std::vector<float> waveTable;
            float sampleRate;
            std::atomic<float> amplitude{1.f};

            std::atomic<bool> swapWavetable{false};
            std::vector<float> wavetableToSwap;
            std::atomic<bool> wavetableIsBeingSwapped{false};
    };
}