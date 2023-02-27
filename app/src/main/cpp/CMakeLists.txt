
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)
project("androidsynth")

if (${ENABLE_CPP_TESTS} MATCHES "true")
        set(CMAKE_CXX_STANDARD 20)
endif ()

set(source_files
        WavetableSynthesizer.cpp
        AudioProcessors/Oscillators/WavetableOscillator.cpp
        WavetableFactory.cpp

        AudioProcessors/SignalSummer.cpp
        AudioProcessors/EnvelopeProcessor.cpp
        AudioProcessors/Filters/BiquadFilter.cpp
        AudioProcessors/Filters/ButterworthLowPassFilter.cpp
        Sequencers/ChannelSequencer.cpp
        Sequencers/ChannelDistributingNoteSequencer.cpp
        Events/NoteEvent.cpp
        OscillatorFactory.cpp
        SequencableObject/FilteredSquareWaveInstrument.cpp)

set(include_folders
        include
        include/Interfaces)

if (NOT (${ENABLE_CPP_TESTS} MATCHES "true"))
        set (source_files ${source_files}
                #Place libraries not testable on a local machine here, i.e. android specific
                #files
                OboeAudioPlayer.cpp
                wavetablesynthesizer-native-lib.cpp
                )

        set (include_folders ${include_folders}
                include-untestable)
endif()

add_library(androidsynth SHARED ${source_files})

include_directories(${include_folders})

find_library(cmath cmath)

if (${ENABLE_CPP_TESTS} MATCHES "true")
        set(TEST_SRC_DIR ../../test/cpp/AndroidSynthTests) # Variable will be used in test script.
        include(../../test/cpp/CMakeLists.txt)
else()
        find_library(log-lib log)

        find_package(oboe REQUIRED CONFIG)

        target_link_libraries(
                androidsynth
                oboe::oboe
                ${log-lib})
endif()

