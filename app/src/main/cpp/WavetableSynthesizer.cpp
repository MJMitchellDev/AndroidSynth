#include "WavetableSynthesizer.h"
#include <cmath>
#include "Log.h"
#include "AudioPlayer.h"
#include "WavetableOscillator.h"
#include "EnvelopeProcessor.h"
#include "ButterworthLowPassFilter.h"

namespace mjmitchelldev_androidsynth {
    float dBToAmplitude(float dB) {
        return std::pow(10.f, dB / 20.f);
    }

    WavetableSynthesizer::WavetableSynthesizer(std::unique_ptr<AudioPlayer> audioPlayer) {
        auto waveTable = _wavetableFactory.GetWaveTable(_currentWavetable); 
        auto oscillator1 = std::make_shared<WavetableOscillator>(waveTable, SamplingRate);
        auto oscillator2 = std::make_shared<WavetableOscillator>(waveTable, SamplingRate);

        _oscillators = std::vector<std::shared_ptr<WavetableOscillator>>{
            oscillator1, oscillator2
        };

        auto sources = std::vector<std::shared_ptr<AudioSource>>{
                std::make_unique<EnvelopeProcessor>(_oscillators[0], SamplingRate),
                std::make_unique<EnvelopeProcessor>(_oscillators[1], SamplingRate)
        };

        _signalSummer = std::make_unique<SignalSummer>(sources);
        _globalFilter = std::make_unique<ButterworthLowPassFilter>(std::move(_signalSummer), SamplingRate);

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
        _oscillators[0]->SetFrequency(frequencyInHz);
        _oscillators[1]->SetFrequency(frequencyInHz * 5 / 4);
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