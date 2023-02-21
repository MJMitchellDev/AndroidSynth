#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ChannelSequencer.h>
#include <NoteEvent.h>
#include <MusicConsts.h>

using ::testing::Return;
using ::testing::Mock;

namespace mjmitchelldev_androidsynth {
    class MockInstrument : public ISequencedInstrument {
        public:     
            MOCK_METHOD(void, SetNote, (Note note), (override));
            MOCK_METHOD(void, ReleaseNote, (Note note), (override));
            MOCK_METHOD(void, StartPlaying, (), (override));
            MOCK_METHOD(void, StopPlaying, (), (override));
    };

    TEST(SequencerTests, ChannelSequencer_ProcessesEventImmediately) {
        auto instrument = std::make_unique<MockInstrument>();
        auto event = std::make_unique<NoteEvent>(1, Note_On, 0, C4);

        EXPECT_CALL(*instrument, SetNote(C4))
            .Times(1);

        //4 frames a second converts to 250ms between frames
        auto sequencer = std::make_unique<ChannelSequencer>(std::move(instrument), 4.0f);
        sequencer->QueueEvent(std::move(event));
        sequencer->TickFrame();
        sequencer->TickFrame();
        sequencer->TickFrame();
    }

    TEST(SequencerTests, ChannelSequencer_ProcessesTwoEvents) {
        auto instrument = std::make_unique<MockInstrument>();
        auto event = std::make_unique<NoteEvent>(1, Note_On, 0, C4);
        auto secondEvent = std::make_unique<NoteEvent>(1, Note_Off, 750, C4);

        EXPECT_CALL(*instrument, SetNote(C4))
            .Times(1);
        EXPECT_CALL(*instrument, ReleaseNote(C4))
            .Times(1);

        //4 frames a second converts to 250ms between frames
        auto sequencer = std::make_unique<ChannelSequencer>(std::move(instrument), 4.0f);
        sequencer->QueueEvent(std::move(event));
        sequencer->QueueEvent(std::move(secondEvent));
        sequencer->TickFrame();
        sequencer->TickFrame();
        sequencer->TickFrame();
    }

    TEST(SequencerTests, ChannelSequencer_ProcessesTwoEventsFromList) {
        auto instrument = std::make_unique<MockInstrument>();

        EXPECT_CALL(*instrument, SetNote(C4))
            .Times(1);
        EXPECT_CALL(*instrument, ReleaseNote(C4))
            .Times(1);
        EXPECT_CALL(*instrument, SetNote(C3))
            .Times(0);

        std::vector<std::unique_ptr<NoteEvent>> eventList; 
        eventList.push_back(std::make_unique<NoteEvent>(1, Note_On, 0, C4));
        eventList.push_back(std::make_unique<NoteEvent>(1, Note_Off, 750, C4));
        eventList.push_back(std::make_unique<NoteEvent>(1, Note_On, 750, C3));

        //4 frames a second converts to 250ms between frames
        auto sequencer = std::make_unique<ChannelSequencer>(std::move(instrument), 4.0f);
        sequencer->QueueEvents(std::move(eventList));
        sequencer->TickFrame();
        sequencer->TickFrame();
        sequencer->TickFrame();
    }
}