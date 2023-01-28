#pragma once

#include <memory>
#include <mutex>
#include "Wavetable.h"
#include "WavetableFactory.h"
#include "SignalSummer.h"
#include "BiquadFilter.h"

namespace wavetablesynthesizer {
    class WavetableOscillator;

    class AudioPlayer;

    constexpr auto SamplingRate = 48000;

    class WavetableSynthesizer {
        public:
            WavetableSynthesizer();
            ~WavetableSynthesizer();
            void play();
            void stop();
            bool isPlaying() const;
            void setFrequency(float frequencyInHz);
            void setVolume(float volumeInDb);
            void setWavetable(Wavetable wavetable);

        private:
            std::atomic<bool> _isPlaying{false};
            std::mutex _mutex;
            WavetableFactory _wavetableFactory;
            Wavetable _currentWavetable{Wavetable::SINE};
            std::vector<std::shared_ptr<WavetableOscillator>> _oscillators;
            std::shared_ptr<SignalSummer> _signalSummer;
            std::unique_ptr<AudioPlayer> _audioPlayer;
            std::shared_ptr<BiquadFilter> _globalFilter;
    };
}
