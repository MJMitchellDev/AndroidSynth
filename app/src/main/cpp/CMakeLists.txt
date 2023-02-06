
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)
project("androidsynth")

if (${ENABLE_CPP_TESTS} MATCHES "true")
        # GoogleTest requires at least C++14
        set(CMAKE_CXX_STANDARD 20)
endif ()

# Declares and names the project.

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

if (${ENABLE_CPP_TESTS} MATCHES "true")
        add_library(
                # Sets the name of the library.
                androidsynth

                # Sets the library as a shared library.
                SHARED

                # Provides a relative path to your source file(s).
                WavetableSynthesizer.cpp
                AudioProcessors/Oscillators/WavetableOscillator.cpp
                WavetableFactory.cpp

                AudioProcessors/SignalSummer.cpp
                AudioProcessors/EnvelopeProcessor.cpp
                AudioProcessors/Filters/BiquadFilter.cpp
                AudioProcessors/Filters/ButterworthLowPassFilter.cpp
                Sequencer.cpp
        )

        include_directories(
                include
        )
else()
        add_library(
                # Sets the name of the library.
                androidsynth

                # Sets the library as a shared library.
                SHARED

                # Provides a relative path to your source file(s).
                WavetableSynthesizer.cpp
                AudioProcessors/Oscillators/WavetableOscillator.cpp
                WavetableFactory.cpp

                AudioProcessors/SignalSummer.cpp
                AudioProcessors/EnvelopeProcessor.cpp
                AudioProcessors/Filters/BiquadFilter.cpp
                AudioProcessors/Filters/ButterworthLowPassFilter.cpp
                Sequencer.cpp

                #Place libraries not testable on a local machine here, i.e. android specific
                #files
                OboeAudioPlayer.cpp
                wavetablesynthesizer-native-lib.cpp
        )

        include_directories(
                include
                include-untestable
        )

endif()


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

#if (NOT ${ENABLE_CPP_TESTS} MATCHES "true")
#
#endif()

find_library(cmath cmath)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

if (${ENABLE_CPP_TESTS} MATCHES "true")
        set(TEST_SRC_DIR ../../test/cpp/AndroidSynthTests) # Variable will be used in test script.
        include(../../test/cpp/CMakeLists.txt)
else()
        find_library( # Sets the name of the path variable.
                log-lib

                #Specifies the name of the NDK library that
                #you want CMake to locate.
                log
                )

        find_package(oboe REQUIRED CONFIG)

        target_link_libraries( # Specifies the target library.
                        androidsynth
                        # Links the target library to the log library
                        # included in the NDK.
                        ${log-lib}
                        oboe::oboe
                )
endif()

