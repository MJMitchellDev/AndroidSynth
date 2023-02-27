//
// Created by lazza on 23/02/2023.
//

#ifndef ANDROIDSYNTH_OSCILLATORFACTORY_H
#define ANDROIDSYNTH_OSCILLATORFACTORY_H

#include "IOscillatorFactory.h"

namespace mjmitchelldev_androidsynth {
    class OscillatorFactory : public IOscillatorFactory {
        public:
            OscillatorFactory(float sampleRate);
            std::unique_ptr<IOscillator> GetNewOscillator() override;

        private:
            float _sampleRate;
    };
}


#endif //ANDROIDSYNTH_OSCILLATORFACTORY_H
