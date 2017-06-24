#pragma once

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/GPU/GPU.h>
#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Audio/Utils/Utils.h>


#include <chrono>

namespace Veritas {
    namespace Audio {
        class Oscilloscope : public AudioSink {
            public:
                Oscilloscope(GPU::FrameBuffer &framebuffer, uint32 rate, FORMAT format, float32 timespan = 1.0f);

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
