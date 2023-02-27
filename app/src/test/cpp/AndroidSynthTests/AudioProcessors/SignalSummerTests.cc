#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <IAudioSource.h>
#include <SignalSummer.h>

using ::testing::Return;

namespace mjmitchelldev_androidsynth {
    class MockAudioSource : public IAudioSource {
        public:
            MOCK_METHOD(float, GetSample, (), (override) );
            MOCK_METHOD(void, OnPlaybackStopped, (), (override) );
    };

    TEST(SignalSummerTests, SignalSummer_WithTwoSources_AddsWithEqualWeight) {
        auto audioSource = std::make_unique<MockAudioSource>();
        auto audioSource2 = std::make_unique<MockAudioSource>();

        EXPECT_CALL(*audioSource, GetSample())
            .WillRepeatedly(Return(1.0f));

        EXPECT_CALL(*audioSource2, GetSample())
            .WillRepeatedly(Return(1.5f));

        std::vector<std::unique_ptr<IAudioSource>> sources;
        sources.push_back(std::move(audioSource));
        sources.push_back(std::move(audioSource2));

        auto summer = std::make_unique<SignalSummer>(std::move(sources));
        auto sample = summer->GetSample();

        EXPECT_EQ(sample, 2.5f);
    }
}