//
// Created by lazza on 27/01/2023.
//

#include "ButterworthLowPassFilter.h"
#include <cmath>

//Second order butterworth filter
//algorithm taken from https://www.st.com/resource/en/application_note/an2874-bqd-filter-design-equations-stmicroelectronics.pdf

namespace wavetablesynthesizer {
    void ButterworthLowPassFilter::setCoefficients(int frequencyCutoff) {
        const double pi = M_PI;
        const double qFactor = M_SQRT1_2;

        auto normalisedCutoff = 2 * pi * (frequencyCutoff / _sampleRate);
        auto cutoffTangent = tan(normalisedCutoff / 2);
        auto cutoffTangentSquared = pow(cutoffTangent, 2.0);
        auto alpha = 1 + (cutoffTangent / qFactor) + cutoffTangentSquared;

        _a1 = 2 * (cutoffTangentSquared - 1) / alpha;
        _a2 = (1 - (cutoffTangent / qFactor) + cutoffTangentSquared) / alpha;

        _b0 = cutoffTangentSquared / alpha;
        _b1 = 2 * _b0;
        _b2 = _b0;
    }
}