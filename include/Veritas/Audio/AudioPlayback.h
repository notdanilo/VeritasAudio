#pragma once

#include <Veritas/Definitions/Definitions.h>

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/Audio/AudioSource.h>

namespace Veritas {
    namespace Audio {
        class AudioPlayback : public AudioSink {
            public:
                AudioPlayback(uint32 framerate, uint8 channels, FORMAT format);
                ~AudioPlayback();

                void read(uint8 *buffer, uint32 bytes);
            private:
                uint32 framerate;
                uint8 channels;
        };
    }
}
