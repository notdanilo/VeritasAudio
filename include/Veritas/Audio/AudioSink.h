#pragma once

#include <Veritas/Audio/AudioNode.h>

namespace Veritas {
    namespace Audio {
        class AudioSink : public AudioNode {
        public:
            AudioSink(uint32 framerate, FORMAT format);
        };
    }
}
