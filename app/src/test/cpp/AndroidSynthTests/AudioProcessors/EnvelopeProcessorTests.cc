#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AudioSource.h>
#include <EnvelopeProcessor.h>

using ::testing::Return;

namespace mjmitchelldev_androidsynth {
    class MockAudioSource : public AudioSource {
        public:
            MOCK_METHOD(float, GetSample, (), (override) );
            MOCK_METHOD(void, OnPlaybackStopped, (), (override) );
    };

    TEST(EnvelopeProcessorTests, EnvelopeProcessor_WhenAttacking_AttacksLinearly) {
        auto audioSource = std::make_shared<MockAudioSource>();

        EXPECT_CALL(*audioSource, GetSample())
            .WillRepeatedly(Return(1.0f));

        auto envelopeGenerator = std::make_unique<EnvelopeProcessor>(audioSource, 4.0f);
        
        //Set the attack to last 1 second, or 4 frames at a sample rate of 4
        envelopeGenerator->SetAdsr(1.0f, 1.0f, 0.0f, 0.0f);

        //expect a liner progression of volume;

        auto sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.0f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.25f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.5f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.75f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 1.0f);
    }

    TEST(EnvelopeProcessorTests, EnvelopeProcessor_WhenDecaying_DecaysLinearly) {
        auto audioSource = std::make_shared<MockAudioSource>();

        EXPECT_CALL(*audioSource, GetSample())
            .WillRepeatedly(Return(1.0f));

        auto envelopeGenerator = std::make_unique<EnvelopeProcessor>(audioSource, 4.0f);
        
        //Set the attack to last 1 second, or 4 frames at a sample rate of 4
        envelopeGenerator->SetAdsr(0.0f, 1.0f, 1.0f, 0.0f);
        envelopeGenerator->SetSustainGain(0.0f);

        //expect a liner decay of volume;
        auto sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 1.0f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.75f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.5f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.25f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 0.0f);
    }

    TEST(EnvelopeProcessorTests, EnvelopeProcessor_WhenSustaining_KeepsValueGainConsistent) {
        auto audioSource = std::make_shared<MockAudioSource>();

        EXPECT_CALL(*audioSource, GetSample())
            .WillRepeatedly(Return(1.0f));

        auto envelopeGenerator = std::make_unique<EnvelopeProcessor>(audioSource, 4.0f);
        
        //Set the attack to last 1 second, or 4 frames at a sample rate of 4
        envelopeGenerator->SetAdsr(0.0f, 0.0f, 1.0f, 0.0f);
        envelopeGenerator->SetSustainGain(1.0f);

        //expect a liner decay of volume;
        auto sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 1.0f);

        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 1.0f);

        envelopeGenerator->SetSustainGain(1.5f);
        sampleValue = envelopeGenerator->GetSample();
        EXPECT_EQ(sampleValue, 1.5f);
    }
}