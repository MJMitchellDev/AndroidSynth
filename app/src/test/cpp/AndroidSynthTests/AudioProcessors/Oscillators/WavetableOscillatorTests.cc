#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <WavetableOscillator.h>

using ::testing::Return;

namespace mjmitchelldev_androidsynth {

    TEST(WavetableOscillatorTests, WavetableOscillator_AtFrequencyOne_ReturnsWavetableSequentially) {
        //sampling at 4 frames a second means that a frequency of 1Hz will return each
        //element sequentially of a 4 length table with no need for interpolation
        const auto wavetableLength = 4;
        const auto sampleRate = 4.0f;

        const std::vector<float> wavetable = {0.1f, 0.2f, 0.3f, 0.4f};

        auto oscillator = std::make_unique<WavetableOscillator>(wavetable, sampleRate);
        oscillator->SetFrequency(1.0f);
        oscillator->SetAmplitude(1.0f);

        EXPECT_EQ(oscillator->GetSample(), 0.1f);
        EXPECT_EQ(oscillator->GetSample(), 0.2f);
        EXPECT_EQ(oscillator->GetSample(), 0.3f);
        EXPECT_EQ(oscillator->GetSample(), 0.4f);
    }

    TEST(WavetableOscillatorTests, WavetableOscillator_AtFrequencyThree_ReturnsWavetableSequentially) {
        //sampling at 4 frames a second means that a frequency of 1Hz will return each
        //element sequentially of a 4 length table with no need for interpolation
        const auto wavetableLength = 4;
        const auto sampleRate = 4.0f;

        const std::vector<float> wavetable = {0.1f, 0.2f, 0.3f, 0.4f};

        auto oscillator = std::make_unique<WavetableOscillator>(wavetable, sampleRate);
        oscillator->SetFrequency(3.0f);
        oscillator->SetAmplitude(1.0f);

        EXPECT_EQ(oscillator->GetSample(), 0.1f);
        EXPECT_EQ(oscillator->GetSample(), 0.4f);
        EXPECT_EQ(oscillator->GetSample(), 0.3f);
        EXPECT_EQ(oscillator->GetSample(), 0.2f);
    }

    TEST(WavetableOscillatorTests, WavetableOscillator_WhenNotFactorOfSampleRate_ReturnsInterpolatedValue) {
        //sampling at 4 frames a second means that a frequency of 1Hz will return each
        //element sequentially of a 4 length table with no need for interpolation
        const auto wavetableLength = 4;
        const auto sampleRate = 4.0f;

        const std::vector<float> wavetable = {0.1f, 0.3f, 0.5f, 0.7f};

        auto oscillator = std::make_unique<WavetableOscillator>(wavetable, sampleRate);
        oscillator->SetFrequency(0.5f);
        oscillator->SetAmplitude(1.0f);

        EXPECT_EQ(oscillator->GetSample(), 0.1f);
        EXPECT_EQ(oscillator->GetSample(), 0.2f);
        EXPECT_EQ(oscillator->GetSample(), 0.3f);
        EXPECT_EQ(oscillator->GetSample(), 0.4f);
        EXPECT_EQ(oscillator->GetSample(), 0.5f);
        EXPECT_EQ(oscillator->GetSample(), 0.6f);
        EXPECT_EQ(oscillator->GetSample(), 0.7f);
        //because our test table doesnt cycle cleanly, the last one will be half way between
        //0.7 at the end of the table and 0.1 at the start - 0.4.
        EXPECT_EQ(oscillator->GetSample(), 0.4f);
        //Then back to the start
        EXPECT_EQ(oscillator->GetSample(), 0.1f);
    }

    TEST(WavetableOscillatorTests, WavetableOscillator_AtAmplitudeHalf_ReturnsWavetableSequentiallyHalved) {
        //sampling at 4 frames a second means that a frequency of 1Hz will return each
        //element sequentially of a 4 length table with no need for interpolation
        const auto wavetableLength = 4;
        const auto sampleRate = 4.0f;

        const std::vector<float> wavetable = {0.1f, 0.2f, 0.3f, 0.4f};

        auto oscillator = std::make_unique<WavetableOscillator>(wavetable, sampleRate);
        oscillator->SetFrequency(1.0f);
        oscillator->SetAmplitude(0.5f);

        EXPECT_EQ(oscillator->GetSample(), 0.05f);
        EXPECT_EQ(oscillator->GetSample(), 0.1f);
        EXPECT_EQ(oscillator->GetSample(), 0.15f);
        EXPECT_EQ(oscillator->GetSample(), 0.2f);
    }
}