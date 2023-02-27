//
// Created by lazza on 23/02/2023.
//

#include "OscillatorFactory.h"
#include "include/OscillatorFactory.h"
#include "WavetableOscillator.h"

namespace mjmitchelldev_androidsynth {
    OscillatorFactory::OscillatorFactory(float sampleRate) : _sampleRate(sampleRate) { }

    std::unique_ptr<IOscillator> OscillatorFactory::GetNewOscillator() {
        std::unique_ptr<IOscillator> oscillator = std::make_unique<WavetableOscillator>(_sampleRate);
        return std::move(oscillator);
    }
}
