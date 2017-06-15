#pragma once

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/GPU/GPU.h>
#include <Veritas/Audio/AudioSource.h>

namespace Veritas {
    namespace Audio {
        class Oscilloscope : public AudioSink {
            public:
                Oscilloscope(GPU::FrameBuffer &framebuffer, uint32 rate, FORMAT format);

                void connect(AudioSource& source);

                void run();
            private:
                AudioSource* source;

                GPU::Programs::ClearProgram cp;
                GPU::Programs::FragmentProgram fp;
                GPU::Programs::VertexProgram vp;
                GPU::Programs::RasterProgram rp;
                GPU::FrameBuffer& framebuffer;
        };
    }
}
