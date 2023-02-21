#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ButterworthLowpassFilter.h>

using ::testing::Return;

namespace mjmitchelldev_androidsynth {
    class MockAudioSource : public AudioSource {
        public:
            MOCK_METHOD(float, GetSample, (), (override) );
            MOCK_METHOD(void, OnPlaybackStopped, (), (override) );
    };

    TEST(FilterTests, ButterworthLowPass_ReturnsCorrectCoefficients) {
        auto audioSource = std::make_unique<MockAudioSource>();

        EXPECT_CALL(*audioSource, GetSample())
            .WillRepeatedly(Return(1.0f));

        auto filter = std::make_unique<ButterworthLowPassFilter>(std::move(audioSource), 100.0f);
        filter->updateFrequencyCutoff(20);
        auto coefficients = filter->GetCoefficients();

        //Expected values taken from https://www.meme.net.au/butterworth.html
        //should be accurate to 3dp

        auto scalingFactor = 4.840925170f;
        auto expectedB0 = 1.0f/scalingFactor;
        EXPECT_LT(std::abs(expectedB0 - coefficients->b0), 0.005);

        auto expectedB1 = 2.0f/scalingFactor;
        EXPECT_LT(std::abs(expectedB1 - coefficients->b1), 0.005);

        auto expectedB2 = 1.0f/scalingFactor;
        EXPECT_LT(std::abs(expectedB2 - coefficients->b2), 0.005);

        auto expectedA1 = -1.788854382f/scalingFactor;
        EXPECT_LT(std::abs(expectedA1 - coefficients->a1), 0.005);

        auto expectedA2 = 0.947929212f/scalingFactor;
        EXPECT_LT(std::abs(expectedA2 - coefficients->a2), 0.005);
    }

    TEST(FilterTests, ButterworthLowPass_AppliesBiquadFormulaCorrectly) {
        auto audioSource = std::make_unique<MockAudioSource>();

        EXPECT_CALL(*audioSource, GetSample())
            .WillRepeatedly(Return(1.0f));

        auto filter = std::make_unique<ButterworthLowPassFilter>(std::move(audioSource), 100.0f);
        filter->updateFrequencyCutoff(20);
        auto coefficients = filter->GetCoefficients();

        auto scalingFactor = 4.840925170f;
        auto expected1 = 1.0f/scalingFactor + 0.0f/scalingFactor + 0.0f/scalingFactor + (1.788854382f/scalingFactor)*0 - (0.947929212f/scalingFactor)*0;
        auto expected2 = 1.0f/scalingFactor + 2.0f/scalingFactor + 0.0f/scalingFactor + (1.788854382f/scalingFactor)*expected1 - (0.947929212f/scalingFactor)*0;
        auto expected3 = 1.0f/scalingFactor + 2.0f/scalingFactor + 1.0f/scalingFactor + (1.788854382f/scalingFactor)*expected2 - (0.947929212f/scalingFactor)*expected1;
        auto expected4 = 1.0f/scalingFactor + 2.0f/scalingFactor + 1.0f/scalingFactor + (1.788854382f/scalingFactor)*expected3 - (0.947929212f/scalingFactor)*expected2;
        EXPECT_LT(std::abs(filter->GetSample() - expected1), 0.005);
        EXPECT_LT(std::abs(filter->GetSample() - expected2), 0.005);
        EXPECT_LT(std::abs(filter->GetSample() - expected3), 0.005);
        EXPECT_LT(std::abs(filter->GetSample() - expected4), 0.005);
    }
}