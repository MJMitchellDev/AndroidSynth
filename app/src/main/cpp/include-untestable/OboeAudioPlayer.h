#pragma once

#include <oboe/Oboe.h>
#include "IAudioPlayer.h"

namespace mjmitchelldev_androidsynth {
    class IAudioSource;

    class OboeAudioPlayer : public oboe::AudioStreamDataCallback,
                            public IAudioPlayer {
        public:
            static constexpr auto channelCount = oboe::ChannelCount::Mono;

            OboeAudioPlayer(std::shared_ptr<IAudioSource> source,
                    int samplingRate);
            OboeAudioPlayer();
            ~OboeAudioPlayer();

            int32_t Play() override;
            void Stop() override;
            oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream,
                    void *audioData,
                    int32_t framesCount) override;

            void SetSampleRate(float sampleRate) override;
            void SetAudioSource(std::shared_ptr<IAudioSource> audioSource) override;

        private:
            std::shared_ptr<IAudioSource> _source;
            std::shared_ptr<oboe::AudioStream> _stream;
            int _samplingRate;
    };
}
