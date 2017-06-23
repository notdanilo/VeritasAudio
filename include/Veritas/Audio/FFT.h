#pragma once

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Audio/Utils/CircularBuffer.h>

namespace Veritas {
    namespace Audio {
        class FFT : public AudioSource, public AudioSink {
            public:
                FFT(uint32 framerate, FORMAT format, float32 timeSpan = 1.0f);

                void setTimeSpan(float32 timeSpan);

                void read(uint8* data, uint32 ammount);
            private:
                Utils::CircularBuffer inBuffer;
                Utils::CircularBuffer outBuffer;
        };
    }
}
