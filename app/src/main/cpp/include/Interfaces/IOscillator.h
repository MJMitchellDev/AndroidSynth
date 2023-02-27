//
// Created by lazza on 23/02/2023.
//

#ifndef ANDROIDSYNTH_IOSCILLATOR_H
#define ANDROIDSYNTH_IOSCILLATOR_H

#include "IAudioSource.h"

namespace mjmitchelldev_androidsynth {
    class IOscillator : public IAudioSource {
        public:
            virtual ~IOscillator() = default;

            virtual void SetFrequency(float frequency) = 0;
            virtual void SetAmplitude(float newAmplitude) = 0;
    };
}

#endif //ANDROIDSYNTH_IOSCILLATOR_H
