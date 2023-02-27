#pragma once

#include <vector>
#include "IAudioSource.h"
#include "IOscillator.h"
#include <atomic>

namespace mjmitchelldev_androidsynth {

    class WavetableOscillator : public IOscillator {
        public:
            WavetableOscillator() = default;
            WavetableOscillator(std::vector<float> waveTable, float sampleRate);
            WavetableOscillator(float sampleRate);

            float GetSample() override;
            void SetFrequency(float frequency) override;
            void SetAmplitude(float newAmplitude) override;
            void OnPlaybackStopped() override;
            virtual void SetWavetable(const std::vector<float> &wavetable);

        private:
            float InterpolateLinearly() const;
            void SwapWavetableIfNecessary();

            float _index = 0.f;
            std::atomic<float> _indexIncrement{0.f};
            std::vector<float> _waveTable;
            float _sampleRate;
            std::atomic<float> _amplitude{1.f};

            std::atomic<bool> _swapWavetable{false};
            std::vector<float> _wavetableToSwap;
            std::atomic<bool> _wavetableIsBeingSwapped{false};
    };
}