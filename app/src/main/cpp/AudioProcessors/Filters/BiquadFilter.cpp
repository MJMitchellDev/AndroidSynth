//
// Created by lazza on 27/01/2023.
//

#include "BiquadFilter.h"
namespace wavetablesynthesizer {
    BiquadFilter::BiquadFilter(std::shared_ptr<AudioSource> filterSource, int sampleRate) :
        _b0(0.0), _b1(0.0), _b2(0.0), _a1(0.0), _a2(0.0), _penultimateSample(0.0),
        _prepenultimateSample(0.0), _penultimateFilteredSample(0.0), _prepenultimateFilteredSample(0.0),
        _sampleRate(sampleRate)
    {
        _filterSource = std::move(filterSource);
    };

    float BiquadFilter::getSample() {
        if (!_initialized) {
            setCoefficients(8000);
        }

        return filterSample(_filterSource->getSample());
    }

    void BiquadFilter::onPlaybackStopped()  {
        _penultimateFilteredSample = 0.0;
        _penultimateSample = 0.0;
        _prepenultimateFilteredSample = 0.0;
        _prepenultimateSample = 0.0;
    }

    void BiquadFilter::updateFrequencyCutoff(int frequencyCutoff)
    {
        setCoefficients(frequencyCutoff);
        _initialized = true;
    }

    float BiquadFilter::filterSample(float sample)
    {
        auto filteredValue = (_b0 * sample) + (_b1 * _penultimateSample) + (_b2 * _prepenultimateSample)
            - (_a1 * _penultimateFilteredSample) - (_a2 * _prepenultimateFilteredSample);

        _prepenultimateSample = _penultimateSample;
        _prepenultimateFilteredSample = _penultimateFilteredSample;
        _penultimateSample = sample;
        _penultimateFilteredSample = filteredValue;

        return filteredValue;
    }
}