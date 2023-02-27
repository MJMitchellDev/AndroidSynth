//
// Created by lazza on 23/11/2022.
//

#include "EnvelopeProcessor.h"

#include <utility>

namespace mjmitchelldev_androidsynth {

    EnvelopeProcessor::EnvelopeProcessor(IAudioSource & soundGenerator, float sampleRate) {
        _soundGenerator = &soundGenerator;
        _sampleRate = sampleRate;
        _currentFrameInCycle = 0;
        _state = EnvelopeState::ATTACK;
    }

    float EnvelopeProcessor::GetSample() {
        float oscillatorValue = _soundGenerator->GetSample();
        processState();

        switch (_state) {
            case EnvelopeState::ATTACK:
                oscillatorValue = oscillatorValue * (_currentFrameInCycle / (_sampleRate * _attackTimeInSeconds));
                break;

            case EnvelopeState::DECAY:
                oscillatorValue = GetDecayValue(oscillatorValue);
                break;

            case EnvelopeState::SUSTAIN:
                oscillatorValue = oscillatorValue * _sustainGain;
                break;

            default:
                break;
        }

        _currentFrameInCycle += 1;
        return oscillatorValue;
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

    void EnvelopeProcessor::SetSustainGain(float sustainGain) {
        _sustainGain = sustainGain;
    }

    float EnvelopeProcessor::GetDecayValue(float sample) {
        auto decayDelta = _attackPeakGain - _sustainGain;
        auto decaySteps = _decayTimeInSeconds * _sampleRate;
        auto currentDecayCycleFrame = _currentFrameInCycle - (_sampleRate * _attackTimeInSeconds);
    
        auto decayGain = _attackPeakGain - (currentDecayCycleFrame * (decayDelta / decaySteps));
        return sample * decayGain;
    }

    void EnvelopeProcessor::processState() {
        //hard code .3s for attack and decay, 1s sustain and no release yet
        auto attackStartFrame = .0f;
        auto decayStartFrame = _sampleRate * _attackTimeInSeconds;
        auto sustainStartFrame = decayStartFrame + _sampleRate * _decayTimeInSeconds;
        auto releaseStartFrame = sustainStartFrame + _sampleRate;
        auto cycleEndFrame = releaseStartFrame;

        if (_currentFrameInCycle >= attackStartFrame && _currentFrameInCycle < decayStartFrame) {
            _state = EnvelopeState::ATTACK;
        } else if (_currentFrameInCycle >= decayStartFrame && _currentFrameInCycle < sustainStartFrame) {
            _state = EnvelopeState::DECAY;
        } else if (_currentFrameInCycle >= sustainStartFrame && _currentFrameInCycle < cycleEndFrame) {
            _state = EnvelopeState::SUSTAIN;
        } else if (_currentFrameInCycle >= cycleEndFrame) {
            _currentFrameInCycle = 0;
            _state = EnvelopeState::ATTACK;
        }
    }
}