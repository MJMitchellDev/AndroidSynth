#pragma once

#include <oboe/Oboe.h>
#include "AudioPlayer.h"

namespace mjmitchelldev_androidsynth {
    class AudioSource;

    class OboeAudioPlayer : public oboe::AudioStreamDataCallback,
                            public AudioPlayer {
        public:
            static constexpr auto channelCount = oboe::ChannelCount::Mono;

            OboeAudioPlayer(std::shared_ptr<AudioSource> source,
                    int samplingRate);
            OboeAudioPlayer();
            ~OboeAudioPlayer();

            int32_t Play() override;
            void Stop() override;
            oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream,
                    void *audioData,
                    int32_t framesCount) override;

            void SetSampleRate(float sampleRate) override;
            void SetAudioSource(std::shared_ptr<AudioSource> audioSource) override;

        private:
            std::shared_ptr<AudioSource> _source;
            std::shared_ptr<oboe::AudioStream> _stream;
            int _samplingRate;
    };
}
