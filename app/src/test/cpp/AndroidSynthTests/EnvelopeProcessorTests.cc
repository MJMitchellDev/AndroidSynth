#include <gtest/gtest.h>

#include <AudioSource.h>
#include <EnvelopeProcessor.h>

// class MockAudioSource : public AudioSource {
//     public:
//         MOCK_METHOD(float, GetSample, (), (override) );
//         MOCK_METHOD(float, OnPlaybackStopped, (), (override) );
// };

// Demonstrate some basic assertions.
TEST(EnvelopeProcessorTests, testAttack) {
    // MockAudioSource audioSource;

    // EXPECT_CALL(audioSource, GetSample())
    //     .WillRepeatedly(Return(1.0f));

    // auto envelopeGenerator = std::make_unique<EnvelopeProcessor>(&audioSource, 4.0f);
    
    // //Set the attack to last 1 second, or 4 frames at a sample rate of 4
    // envelopeGenerator->SetAdsr(1.0f, 0.0f, 0.0f, 0.0f);

    // //expect a liner progression of volume;

    // auto sampleValue = envelopeGenerator->GetSample();

    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}