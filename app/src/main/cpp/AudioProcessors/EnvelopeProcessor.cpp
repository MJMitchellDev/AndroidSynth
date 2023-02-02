//
// Created by lazza on 23/11/2022.
//

#include "EnvelopeProcessor.h"

#include <utility>

namespace mjmitchelldev_androidsynth {

    EnvelopeProcessor::EnvelopeProcessor(std::shared_ptr<AudioSource> soundGenerator, float sampleRate) {
        _soundGenerator = std::move(soundGenerator);
        _sampleRate = sampleRate;
        _currentFrame = 0;
        _state = EnvelopeState::ATTACK;
    }

    float EnvelopeProcessor::GetSample() {
        float oscillatorValue = _soundGenerator->GetSample();
        processState();

        switch (_state) {
            case EnvelopeState::ATTACK:
                return oscillatorValue * (_currentFrame / _sampleRate * _attackTimeInSeconds);

            case EnvelopeState::DECAY:
                return oscillatorValue * (1 - (1.0f - _sustainGain) * ((_sampleRate - _currentFrame) / _sampleRate * _decayTimeInSeconds));

            case EnvelopeState::SUSTAIN:
                return oscillatorValue * _sustainGain;

            default:
                return oscillatorValue;
        }
    }

    void EnvelopeProcessor::processState() {
        //hard code .3s for attack and decay, 1s sustain and no release yet
        auto attackStartFrame = .0f;
        auto decayStartFrame = _sampleRate * _attackTimeInSeconds;
        auto sustainStartFrame = decayStartFrame + _sampleRate * _decayTimeInSeconds;
        auto releaseStartFrame = sustainStartFrame + _sampleRate;
        auto cycleEndFrame = releaseStartFrame;

        if (_currentFrame < decayStartFrame) {
            _state = EnvelopeState::ATTACK;
        } else if (_currentFrame < sustainStartFrame) {
            _state = EnvelopeState::DECAY;
        } else if (_currentFrame < cycleEndFrame) {
            _state = EnvelopeState::SUSTAIN;
        } else if (_currentFrame >= cycleEndFrame) {
            _currentFrame = 0;
            _state = EnvelopeState::ATTACK;
        }

        _currentFrame += 1;
    }

    void EnvelopeProcessor::OnPlaybackStopped() {
        _state = EnvelopeState::ATTACK;
        _soundGenerator->OnPlaybackStopped();
    }

    void EnvelopeProcessor::SetAdsr(float attack, float decay, float sustain, float release) {
        _attackTimeInSeconds = attack;
        _decayTimeInSeconds = decay;
        _sustainTimeInSeconds = sustain;
        _releaseTimeInSeconds = release;
    }
}