//
// Created by lazza on 27/01/2023.
//

#include "BiquadFilter.h"
namespace mjmitchelldev_androidsynth {
    BiquadFilter::BiquadFilter(std::unique_ptr<AudioSource> filterSource, int sampleRate) :
        _b0(0.0), _b1(0.0), _b2(0.0), _a1(0.0), _a2(0.0), _penultimateSample(0.0),
        _prepenultimateSample(0.0), _penultimateFilteredSample(0.0), _prepenultimateFilteredSample(0.0),
        _sampleRate(sampleRate)
    {
        _filterSource = std::move(filterSource);
    };

    float BiquadFilter::GetSample() 
    {
        if (!_initialized) {
            SetCoefficients(8000);
            _initialized = true;
        }

        return filterSample(_filterSource->GetSample());
    }

    void BiquadFilter::OnPlaybackStopped()  
    {
        _penultimateFilteredSample = 0.0;
        _penultimateSample = 0.0;
        _prepenultimateFilteredSample = 0.0;
        _prepenultimateSample = 0.0;
    }

    void BiquadFilter::updateFrequencyCutoff(int frequencyCutoff)
    {
        SetCoefficients(frequencyCutoff);
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

    std::unique_ptr<BiquadFilterCoefficients> BiquadFilter::GetCoefficients() 
    {
        auto result = std::make_unique<BiquadFilterCoefficients>();
        result->a1 = _a1;
        result->a2 = _a2;
        result->b0 = _b0;
        result->b1 = _b1;
        result->b2 = _b2;

        return result;
    }
}