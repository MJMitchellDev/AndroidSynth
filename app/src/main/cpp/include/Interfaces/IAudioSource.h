#ifndef AUDIOSOURCE_H_
#define AUDIOSOURCE_H_


namespace mjmitchelldev_androidsynth {
    class IAudioSource {
        public:
            virtual ~IAudioSource() = default;
            virtual float GetSample() = 0;
            virtual void OnPlaybackStopped() = 0;
    };
}

#endif