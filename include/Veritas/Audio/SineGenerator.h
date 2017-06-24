#pragma once

#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Audio/AudioSink.h>

namespace Veritas {
    namespace Audio {
        class SineGenerator : public AudioSource, public AudioSink {
            public:
                SineGenerator(uint32 framerate, FORMAT format, float32 timespan = 1.0f);

                void read(uint8 *data, uint32 bytes);
            private:
                uint32 framerate;
                uint32 time;
        };
    }
}
