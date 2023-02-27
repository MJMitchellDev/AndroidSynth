//
// Created by lazza on 23/02/2023.
//

#ifndef ANDROIDSYNTH_IOSCILLATORFACTORY_H
#define ANDROIDSYNTH_IOSCILLATORFACTORY_H

#include "IOscillator.h"
#include <memory>

namespace mjmitchelldev_androidsynth {
    class IOscillatorFactory {
        public:
            virtual ~IOscillatorFactory() = default;

            virtual std::unique_ptr<IOscillator> GetNewOscillator() = 0;
    };
}

#endif //ANDROIDSYNTH_IOSCILLATORFACTORY_H
