#pragma once

namespace mjmitchelldev_androidsynth {
    class AudioSource {
        public:
            virtual ~AudioSource() = default;
            virtual float GetSample() = 0;
            virtual void OnPlaybackStopped() = 0;
    };
}
