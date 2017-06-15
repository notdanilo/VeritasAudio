#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        class AudioNode {
            public:
                enum FORMAT { UINT8, INT16LE, INT16BE, INT32LE, INT32BE, FLOAT32LE, FLOAT32BE, FLOAT32 };
                AudioNode(uint32 framerate, FORMAT format);

                uint32 getFramerate() const;
                FORMAT getFormat() const;
            private:
                uint32 framerate;
                FORMAT format;
        };
    }
}
