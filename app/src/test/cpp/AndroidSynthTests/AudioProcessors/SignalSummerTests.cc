#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AudioSource.h>
#include <SignalSummer.h>

using ::testing::Return;

namespace mjmitchelldev_androidsynth {
    class MockAudioSource : public AudioSource {
        public:
            MOCK_METHOD(float, GetSample, (), (override) );
            MOCK_METHOD(void, OnPlaybackStopped, (), (override) );
    };

    TEST(SignalSummerTests, SignalSummer_WithTwoSources_AddsWithEqualWeight) {
        auto audioSource = std::make_shared<MockAudioSource>();
        auto audioSource2 = std::make_shared<MockAudioSource>();

        EXPECT_CALL(*audioSource, GetSample())
            .WillRepeatedly(Return(1.0f));

        EXPECT_CALL(*audioSource2, GetSample())
            .WillRepeatedly(Return(1.5f));

        std::vector<std::shared_ptr<AudioSource>> sources = {audioSource, audioSource2};

        auto summer = std::make_unique<SignalSummer>(sources);
        auto sample = summer->GetSample();

        EXPECT_EQ(sample, 2.5f);
    }
}