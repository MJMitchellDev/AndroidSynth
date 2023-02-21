#pragma once

#include <memory>
#include <mutex>
#include "Wavetable.h"
#include "WavetableFactory.h"
#include "SignalSummer.h"
#include "BiquadFilter.h"
#include <atomic>

namespace mjmitchelldev_androidsynth {
    class WavetableOscillator;

    class AudioPlayer;

    constexpr auto SamplingRate = 48000.0f;

    class WavetableSynthesizer {
        public:
            WavetableSynthesizer(std::unique_ptr<AudioPlayer> audioPlayer);
            ~WavetableSynthesizer();
            void Play();
            void Stop();
            bool IsPlaying() const;
            void SetFrequency(float frequencyInHz);
            void SetVolume(float volumeInDb);
            void SetWavetable(Wavetable wavetable);
            void SetFilterCutoffFrequency(float frequencyInHz);

        private:
            std::atomic<bool> _isPlaying{false};
            std::mutex _mutex;
            WavetableFactory _wavetableFactory;
            Wavetable _currentWavetable{Wavetable::SINE};
            std::vector<std::shared_ptr<WavetableOscillator>> _oscillators;
            std::unique_ptr<SignalSummer> _signalSummer;
            std::unique_ptr<AudioPlayer> _audioPlayer;
            std::unique_ptr<BiquadFilter> _globalFilter;
    };
}
