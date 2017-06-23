#pragma once

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/GPU/GPU.h>
#include <Veritas/Audio/Utils/CircularBuffer.h>
#include <chrono>

namespace Veritas {
    namespace Audio {
        class SpectrumAnalyzer : public AudioSink {
            public:
                SpectrumAnalyzer(GPU::FrameBuffer &framebuffer, uint32 rate, FORMAT format, float32 timeSpan = 1.0f);

                void setTimeSpan(float32 timeSpan);

                enum MODE { CONTINUOUS, REDRAW, REDRAW_TRIGGER_UP, REDRAW_TRIGGER_DOWN };
                void setMode(MODE mode);
                MODE getMode() const;

                void run();
            private:
                MODE mode;
                GPU::Programs::ClearProgram cp;
                GPU::Programs::FragmentProgram fp;
                GPU::Programs::VertexProgram vp;
                GPU::Programs::RasterProgram rp;
                GPU::FrameBuffer& framebuffer;

                Audio::Utils::CircularBuffer buffer;

                std::chrono::high_resolution_clock::time_point t0;
        };
    }
}
