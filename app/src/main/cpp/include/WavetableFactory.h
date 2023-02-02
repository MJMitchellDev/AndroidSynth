#pragma once
#include <vector>

namespace mjmitchelldev_androidsynth {
    enum class Wavetable;

    class WavetableFactory {
        public:
            std::vector<float> GetWaveTable(Wavetable wavetable);
            std::vector<float> SineWaveTable();
            std::vector<float> TriangleWaveTable();
            std::vector<float> SquareWaveTable();
            std::vector<float> SawWaveTable();

        private:
            std::vector<float> _sineWaveTable;
            std::vector<float> _triangleWaveTable;
            std::vector<float> _squareWaveTable;
            std::vector<float> _sawWaveTable;
    };
}  // namespace com.mjmitchelldev.androidsynth
