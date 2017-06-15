#pragma once

#include <Veritas/Audio/AudioNode.h>
#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        class AudioSource : public AudioNode {
            public:
                AudioSource(uint32 framerate, FORMAT format);
                virtual ~AudioSource() = default;

                virtual void read(uint8 *data, uint32 bytes) = 0;
        };
    }
}
