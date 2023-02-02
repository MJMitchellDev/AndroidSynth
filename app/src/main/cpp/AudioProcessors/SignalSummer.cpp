#include "SignalSummer.h"

#include <utility>

namespace mjmitchelldev_androidsynth {
      SignalSummer::SignalSummer(std::vector<std::shared_ptr<AudioSource>> soundGenerators) {
          _soundGenerators = std::move(soundGenerators);
      }

    float SignalSummer::GetSample() {
        auto result = .0f;

        for (auto & soundGenerator : _soundGenerators) {
            result += soundGenerator->GetSample();
        }

        return result;
    }

    void SignalSummer::OnPlaybackStopped() {
        for (auto & soundGenerator : _soundGenerators)
        {
            soundGenerator->OnPlaybackStopped();
        }
    }
}