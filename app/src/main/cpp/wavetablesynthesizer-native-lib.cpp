#include <jni.h>
#include <memory>
#include "Log.h"
#include "WavetableSynthesizer.h"
#include "OboeAudioPlayer.h"

extern "C" {
JNIEXPORT jlong JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_create(
        JNIEnv *env,
        jobject obj) {
    auto synthesizer =
            std::make_unique<mjmitchelldev_androidsynth::WavetableSynthesizer>(
                    std::make_unique<mjmitchelldev_androidsynth::OboeAudioPlayer>()
                    );

    if (not synthesizer) {
        LOGD("Failed to create the synthesizer.");
        synthesizer.reset(nullptr);
    }

    return reinterpret_cast<jlong>(synthesizer.release());
}

JNIEXPORT void JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_delete(
        JNIEnv *env,
        jobject obj,
        jlong synthesizerHandle) {
    auto *synthesizer =
            reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
                    synthesizerHandle);

    if (not synthesizer) {
        LOGD("Attempt to destroy an unitialized synthesizer.");
        return;
    }

    delete synthesizer;
}

JNIEXPORT void JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_play(
        JNIEnv *env,
        jobject obj,
        jlong synthesizerHandle) {
    auto *synthesizer =
            reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
                    synthesizerHandle);

    if (synthesizer) {
        synthesizer->Play();
    } else {
        LOGD(
                "Synthesizer not created. Please, create the synthesizer first by "
                "calling create().");
    }
}

JNIEXPORT void JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_stop(
        JNIEnv *env,
        jobject obj,
        jlong synthesizerHandle) {
    auto *synthesizer =
            reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
                    synthesizerHandle);

    if (synthesizer) {
        synthesizer->Stop();
    } else {
        LOGD(
                "Synthesizer not created. Please, create the synthesizer first by "
                "calling create().");
    }
}

JNIEXPORT jboolean JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_isPlaying(
        JNIEnv *env,
        jobject obj,
        jlong synthesizerHandle) {
    auto *synthesizer =
            reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
                    synthesizerHandle);

    if (not synthesizer) {
        LOGD(
                "Synthesizer not created. Please, create the synthesizer first by "
                "calling create().");
        return false;
    }

    return synthesizer->IsPlaying();
}

JNIEXPORT void JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_setFrequency(
        JNIEnv *env,
        jobject obj,
        jlong synthesizerHandle,
        jfloat frequencyInHz) {
    auto *synthesizer =
            reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
                    synthesizerHandle);
    const auto nativeFrequency = static_cast<float>(frequencyInHz);

    if (synthesizer) {
        synthesizer->SetFrequency(nativeFrequency);
    } else {
        LOGD(
                "Synthesizer not created. Please, create the synthesizer first by "
                "calling create().");
    }
}

JNIEXPORT void JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_setFilterCutoffFrequency(
    JNIEnv *env, jobject obj, jlong synthesizerHandle, jfloat frequencyInHz) {
    auto *synthesizer = reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
        synthesizerHandle);
    const auto nativeFrequency = static_cast<float>(frequencyInHz);

    if (synthesizer) {
        synthesizer->SetFilterCutoffFrequency(nativeFrequency);
    } else {
        LOGD(
            "Synthesizer not created. Please, create the synthesizer first by "
            "calling create().");
    }
}

JNIEXPORT void JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_setVolume(
        JNIEnv *env,
        jobject obj,
        jlong synthesizerHandle,
        jfloat volumeInDb) {
    auto *synthesizer =
            reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
                    synthesizerHandle);
    const auto nativeVolume = static_cast<float>(volumeInDb);

    if (synthesizer) {
        synthesizer->SetVolume(nativeVolume);
    } else {
        LOGD(
                "Synthesizer not created. Please, create the synthesizer first by "
                "calling create().");
    }
}

JNIEXPORT void JNICALL
Java_com_mjmitchelldev_androidsynth_NativeWavetableSynthesizer_setWavetable(
        JNIEnv *env,
        jobject obj,
        jlong synthesizerHandle,
        jint wavetable) {
    auto *synthesizer =
            reinterpret_cast<mjmitchelldev_androidsynth::WavetableSynthesizer *>(
                    synthesizerHandle);
    const auto nativeWavetable = static_cast<mjmitchelldev_androidsynth::Wavetable>(wavetable);

    if (synthesizer) {
        synthesizer->SetWavetable(nativeWavetable);
    } else {
        LOGD(
                "Synthesizer not created. Please, create the synthesizer first by "
                "calling create().");
    }
}
}
