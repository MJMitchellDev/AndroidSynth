#include "SignalSummer.h"

#include <utility>

namespace wavetablesynthesizer {
      SignalSummer::SignalSummer(std::vector<std::shared_ptr<AudioSource>> soundGenerators) {
          _soundGenerators = std::move(soundGenerators);
      }

    float SignalSummer::getSample() {
        auto result = .0f;

        for (auto & soundGenerator : _soundGenerators) {
            result += soundGenerator->getSample();
        }

        return result;
    }

    void SignalSummer::onPlaybackStopped() {
        for (auto & soundGenerator : _soundGenerators)
        {
            soundGenerator->onPlaybackStopped();
        }
    }
}