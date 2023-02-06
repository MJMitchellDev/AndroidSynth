if (${ENABLE_CPP_TESTS} MATCHES "true")

    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
            AndroidSynthTestsLib
            ${TEST_SRC_DIR}/AudioProcessors/EnvelopeProcessorTests.cc
            ${TEST_SRC_DIR}/AudioProcessors/SignalSummerTests.cc
    )
    target_link_libraries(
            AndroidSynthTestsLib
            wavetablesynthesizer
            GTest::gtest_main
            gmock
    )

    include(GoogleTest)
    gtest_discover_tests(AndroidSynthTestsLib)

endif () # ENABLE_CPP_TESTS