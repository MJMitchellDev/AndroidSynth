#include "WavetableOscillator.h"
#include <cmath>
#include "MathConstants.h"

namespace mjmitchelldev_androidsynth {

    WavetableOscillator::WavetableOscillator(std::vector<float> waveTable,
            float sampleRate)
            : _waveTable{std::move(waveTable)}, _sampleRate{sampleRate} {}

    float WavetableOscillator::GetSample() {
        SwapWavetableIfNecessary();

        _index = std::fmod(_index, static_cast<float>(_waveTable.size()));
        const auto sample = InterpolateLinearly();
        _index += _indexIncrement;
        return _amplitude * sample;
    }

    void WavetableOscillator::SwapWavetableIfNecessary() {
        _wavetableIsBeingSwapped.store(true, std::memory_order_release);
        if (_swapWavetable.load(std::memory_order_acquire)) {
            std::swap(_waveTable, _wavetableToSwap);
            _swapWavetable.store(false, std::memory_order_relaxed);
        }
        _wavetableIsBeingSwapped.store(false, std::memory_order_release);
    }

    void WavetableOscillator::SetFrequency(float frequency) {
        _indexIncrement = frequency * static_cast<float>(_waveTable.size()) /
                static_cast<float>(_sampleRate);
    }

    void WavetableOscillator::OnPlaybackStopped() {
        _index = 0.f;
    }

    float WavetableOscillator::InterpolateLinearly() const {
        const auto truncatedIndex =
                static_cast<typename decltype(_waveTable)::size_type>(_index);
        const auto nextIndex = (truncatedIndex + 1u) % _waveTable.size();
        const auto nextIndexWeight = _index - static_cast<float>(truncatedIndex);
        return _waveTable[nextIndex] * nextIndexWeight +
                (1.f - nextIndexWeight) * _waveTable[truncatedIndex];
    }

    void WavetableOscillator::SetAmplitude(float newAmplitude) {
        _amplitude.store(newAmplitude);
    }

    void WavetableOscillator::SetWavetable(const std::vector<float> &wavetable) {
        // Wait for the previous swap to take place if the oscillator is playing
        _swapWavetable.store(false, std::memory_order_release);
        while (_wavetableIsBeingSwapped.load(std::memory_order_acquire)) {
        }
        _wavetableToSwap = wavetable;
        _swapWavetable.store(true, std::memory_order_release);
    }

    WavetableOscillator::WavetableOscillator(float sampleRate) {
        _sampleRate = sampleRate;
    }
}