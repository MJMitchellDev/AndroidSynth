#include "WavetableOscillator.h"
#include <cmath>
#include "MathConstants.h"

namespace mjmitchelldev_androidsynth {

    WavetableOscillator::WavetableOscillator(std::vector<float> waveTable,
            float sampleRate)
            : waveTable{std::move(waveTable)}, sampleRate{sampleRate} {}

    float WavetableOscillator::GetSample() {
        SwapWavetableIfNecessary();

        _index = std::fmod(_index, static_cast<float>(waveTable.size()));
        const auto sample = InterpolateLinearly();
        _index += indexIncrement;
        return amplitude * sample;
    }

    void WavetableOscillator::SwapWavetableIfNecessary() {
        wavetableIsBeingSwapped.store(true, std::memory_order_release);
        if (swapWavetable.load(std::memory_order_acquire)) {
            std::swap(waveTable, wavetableToSwap);
            swapWavetable.store(false, std::memory_order_relaxed);
        }
        wavetableIsBeingSwapped.store(false, std::memory_order_release);
    }

    void WavetableOscillator::SetFrequency(float frequency) {
        indexIncrement = frequency * static_cast<float>(waveTable.size()) /
                static_cast<float>(sampleRate);
    }

    void WavetableOscillator::OnPlaybackStopped() {
        _index = 0.f;
    }

    float WavetableOscillator::InterpolateLinearly() const {
        const auto truncatedIndex =
                static_cast<typename decltype(waveTable)::size_type>(_index);
        const auto nextIndex = (truncatedIndex + 1u) % waveTable.size();
        const auto nextIndexWeight = _index - static_cast<float>(truncatedIndex);
        return waveTable[nextIndex] * nextIndexWeight +
                (1.f - nextIndexWeight) * waveTable[truncatedIndex];
    }

    void WavetableOscillator::SetAmplitude(float newAmplitude) {
        amplitude.store(newAmplitude);
    }

    void WavetableOscillator::SetWavetable(const std::vector<float> &wavetable) {
        // Wait for the previous swap to take place if the oscillator is playing
        swapWavetable.store(false, std::memory_order_release);
        while (wavetableIsBeingSwapped.load(std::memory_order_acquire)) {
        }
        wavetableToSwap = wavetable;
        swapWavetable.store(true, std::memory_order_release);
    }
}