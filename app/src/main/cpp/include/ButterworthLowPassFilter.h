//
// Created by lazza on 27/01/2023.
//

// Second Order Low Pass Butterworth Filter
// https://en.wikipedia.org/wiki/Butterworth_filter

#include "BiquadFilter.h"
#include <math.h>

namespace mjmitchelldev_androidsynth {
    class ButterworthLowPassFilter : public BiquadFilter {
        public:
            ButterworthLowPassFilter(std::unique_ptr<IAudioSource> filterSource, int sampleRate)
                : BiquadFilter(std::move(filterSource), sampleRate)
            { }

            void SetCoefficients(int frequencyCutoff) override;
    };
}