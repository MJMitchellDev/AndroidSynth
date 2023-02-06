//
// Created by lazza on 27/01/2023.
//

//based on the following formula taken from: https://en.wikipedia.org/wiki/Digital_biquad_filter

// y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]

// where:
//     n: the specific sample number being processed
//     y: the array of previously filtered samples
//     x: the array of raw input samples
//     b: the solutions to the numerator quadratic function for any given filter definition
//     a: the solutions to the denominator quadratic function for any given filter definition.
//        a0 is always assumed to be 1 for simplicity

#pragma once
#include <memory>
#include "AudioSource.h"

namespace mjmitchelldev_androidsynth {
    struct BiquadFilterCoefficients {
        float a1;
        float a2;
        float b0;
        float b1;
        float b2;
    };

    class BiquadFilter : public AudioSource {
        public:
            BiquadFilter(std::shared_ptr<AudioSource> filterSource, int sampleRate);

            float GetSample() override;
            void OnPlaybackStopped() override;

            std::unique_ptr<BiquadFilterCoefficients> GetCoefficients();

            void updateFrequencyCutoff(int frequencyCutoff);
            float filterSample(float sample);

        protected:
            virtual void SetCoefficients(int frequencyCutoff) = 0;

            float _b0 = 0.0;
            float _b1 = 0.0;
            float _b2 = 0.0;
            float _a1 = 0.0;
            float _a2 = 0.0;

            int _sampleRate = 0;

        private:
            float _penultimateSample;
            float _penultimateFilteredSample;
            float _prepenultimateSample;
            float _prepenultimateFilteredSample;
            bool _initialized = false;

            std::shared_ptr<AudioSource> _filterSource;
    };
}