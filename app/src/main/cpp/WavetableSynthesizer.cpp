#include "WavetableSynthesizer.h"
#include <cmath>
#include "Log.h"
#include "OboeAudioPlayer.h"
#include "WavetableOscillator.h"
#include "EnvelopeProcessor.h"
#include "ButterworthLowPassFilter.h"

namespace wavetablesynthesizer {
    float dBToAmplitude(float dB) {
        return std::pow(10.f, dB / 20.f);
    }

    WavetableSynthesizer::WavetableSynthesizer() {
        _oscillators = std::vector<std::shared_ptr<WavetableOscillator>>{
                std::make_shared<WavetableOscillator>(_wavetableFactory.getWaveTable(_currentWavetable), SamplingRate),
                std::make_shared<WavetableOscillator>(_wavetableFactory.getWaveTable(_currentWavetable), SamplingRate)
        };

        auto sources = std::vector<std::shared_ptr<AudioSource>>{
                std::dynamic_pointer_cast<AudioSource>(std::make_shared<EnvelopeProcessor>(_oscillators[0],
                        SamplingRate)),
                std::dynamic_pointer_cast<AudioSource>(std::make_shared<EnvelopeProcessor>(_oscillators[1],
                        SamplingRate))
        };

        _signalSummer = std::make_shared<SignalSummer>(sources);
        _globalFilter =
                std::dynamic_pointer_cast<BiquadFilter>(std::make_shared<ButterworthLowPassFilter>(_signalSummer,
                        SamplingRate));

        //_audioPlayer = std::make_unique<OboeAudioPlayer>(_signalSummer, SamplingRate);
        _audioPlayer = std::make_unique<OboeAudioPlayer>(_globalFilter, SamplingRate);

    }

    WavetableSynthesizer::~WavetableSynthesizer() = default;

    bool WavetableSynthesizer::isPlaying() const {
        LOGD("isPlaying() called");
        return _isPlaying;
    }

    void WavetableSynthesizer::play() {
        LOGD("play() called");
        std::lock_guard<std::mutex> lock(_mutex);
        const auto result = _audioPlayer->play();
        if (result == 0) {
            _isPlaying = true;
        } else {
            LOGD("Could not start playback.");
        }
    }

    void WavetableSynthesizer::setFrequency(float frequencyInHz) {
        LOGD("Frequency set to %.2f Hz.", frequencyInHz);
        _oscillators[0]->setFrequency(frequencyInHz);
        _oscillators[1]->setFrequency(frequencyInHz * 5 / 4);
    }

    void WavetableSynthesizer::setFilterCutoffFrequency(float frequencyInHz) {
        LOGD("Frequency set to %.2f Hz.", frequencyInHz);
        _globalFilter->updateFrequencyCutoff(frequencyInHz);
    }

    void WavetableSynthesizer::setVolume(float volumeInDb) {
        LOGD("Volume set to %.2f dB.", volumeInDb);
        const auto amplitude = dBToAmplitude(volumeInDb);
        _oscillators[0]->setAmplitude(amplitude);
        _oscillators[1]->setAmplitude(amplitude);
    }

    void WavetableSynthesizer::setWavetable(Wavetable wavetable) {
        if (_currentWavetable != wavetable) {
            _currentWavetable = wavetable;
            _oscillators[0]->setWavetable(_wavetableFactory.getWaveTable(wavetable));
            _oscillators[1]->setWavetable(_wavetableFactory.getWaveTable(wavetable));
        }
    }

    void WavetableSynthesizer::stop() {
        LOGD("stop() called");
        std::lock_guard<std::mutex> lock(_mutex);
        _audioPlayer->stop();
        _isPlaying = false;
    }
}