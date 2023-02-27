#include "WavetableSynthesizer.h"
#include <cmath>
#include "Log.h"
#include "IAudioPlayer.h"
#include "WavetableOscillator.h"
#include "EnvelopeProcessor.h"
#include "ButterworthLowPassFilter.h"

namespace mjmitchelldev_androidsynth {
    float dBToAmplitude(float dB) {
        return std::pow(10.f, dB / 20.f);
    }

    WavetableSynthesizer::WavetableSynthesizer(std::unique_ptr<IAudioPlayer> audioPlayer)
    : _oscillators() {
        auto waveTable = _wavetableFactory.GetWaveTable(_currentWavetable);

        auto madeOscillator = std::make_unique<WavetableOscillator>(waveTable, SamplingRate);
        _oscillators.push_back(std::move(madeOscillator));
        madeOscillator = std::make_unique<WavetableOscillator>(waveTable, SamplingRate);
        _oscillators.push_back(std::move(madeOscillator));

        std::vector<std::unique_ptr<IAudioSource>> sources;
        for (auto &oscillator: _oscillators) {
            sources.push_back( std::make_unique<EnvelopeProcessor>(*oscillator, SamplingRate));
        }

        _signalSummer = std::make_unique<SignalSummer>(std::move(sources));
        _globalFilter = std::make_shared<ButterworthLowPassFilter>(std::move(_signalSummer), SamplingRate);

        _audioPlayer = std::move(audioPlayer);
        _audioPlayer->SetAudioSource(std::move(_globalFilter));
        _audioPlayer->SetSampleRate(SamplingRate);
    }

    WavetableSynthesizer::~WavetableSynthesizer() = default;

    bool WavetableSynthesizer::IsPlaying() const {
        LOGD("IsPlaying() called");
        return _isPlaying;
    }

    void WavetableSynthesizer::Play() {
        LOGD("Play() called");
        std::lock_guard<std::mutex> lock(_mutex);
        const auto result = _audioPlayer->Play();
        if (result == 0) {
            _isPlaying = true;
        } else {
            LOGD("Could not start playback.");
        }
    }

    void WavetableSynthesizer::SetFrequency(float frequencyInHz) {
        LOGD("Frequency set to %.2f Hz.", frequencyInHz);

        auto nextFrequency = frequencyInHz;
        for (auto &oscillator: _oscillators) {
            oscillator->SetFrequency(nextFrequency);
            nextFrequency = nextFrequency * 5/4;
        }
    }

    void WavetableSynthesizer::SetFilterCutoffFrequency(float frequencyInHz) {
        LOGD("Frequency set to %.2f Hz.", frequencyInHz);
        _globalFilter->updateFrequencyCutoff(frequencyInHz);
    }

    void WavetableSynthesizer::SetVolume(float volumeInDb) {
        LOGD("Volume set to %.2f dB.", volumeInDb);
        const auto amplitude = dBToAmplitude(volumeInDb);
        _oscillators[0]->SetAmplitude(amplitude);
        _oscillators[1]->SetAmplitude(amplitude);
    }

    void WavetableSynthesizer::SetWavetable(Wavetable wavetable) {
        if (_currentWavetable != wavetable) {
            _currentWavetable = wavetable;
            _oscillators[0]->SetWavetable(_wavetableFactory.GetWaveTable(wavetable));
            _oscillators[1]->SetWavetable(_wavetableFactory.GetWaveTable(wavetable));
        }
    }

    void WavetableSynthesizer::Stop() {
        LOGD("Stop() called");
        std::lock_guard<std::mutex> lock(_mutex);
        _audioPlayer->Stop();
        _isPlaying = false;
    }
}