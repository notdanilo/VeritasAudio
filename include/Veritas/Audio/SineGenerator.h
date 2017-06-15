#pragma once

#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Audio/AudioSink.h>

namespace Veritas {
    namespace Audio {
        class SineGenerator : public AudioSource, public AudioSink {
            public:
                SineGenerator(uint32 framerate, FORMAT format);

                void read(uint8 *data, uint32 bytes);
            private:
                uint32 framerate;
                uint32 time;
        };
    }
}
