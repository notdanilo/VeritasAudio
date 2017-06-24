#pragma once

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/Audio/AudioSource.h>

namespace Veritas {
    namespace Audio {
        class AudioIO : public AudioSource, public AudioSink {
            public:
                AudioIO(uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f, uint32 sources = 1);


        };
    }
}
