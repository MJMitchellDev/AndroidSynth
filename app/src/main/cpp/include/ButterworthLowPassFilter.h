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
            ButterworthLowPassFilter(std::shared_ptr<AudioSource> filterSource, int sampleRate)
                : BiquadFilter(filterSource, sampleRate)
            { }

            void SetCoefficients(int frequencyCutoff) override;
    };
}