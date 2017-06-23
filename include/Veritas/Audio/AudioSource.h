#pragma once

#include <Veritas/Audio/AudioNode.h>
#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        class AudioSource : public virtual AudioNode {
            public:
                AudioSource(uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f);
                virtual ~AudioSource() = default;

                virtual void read(uint8 *data, uint32 ammount) = 0;
        };
    }
}
