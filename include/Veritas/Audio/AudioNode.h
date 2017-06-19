#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        class AudioNode {
            public:
                enum FORMAT { UINT8 = 8, INT16LE = 16, INT16BE = 17, INT32LE = 32, INT32BE = 33, FLOAT32LE = 34, FLOAT32BE = 35, FLOAT32 = 36 };
                AudioNode(uint32 framerate, FORMAT format);
                AudioNode(float32 timeSpan, uint32 framerate, FORMAT format);

                virtual void setTimeSpan(float32 timeSpan);
                float32 getTimeSpan() const;

                uint32 getBytesPerFrame() const;

                uint32 getFramerate() const;
                FORMAT getFormat() const;
            private:
                uint32 framerate;
                FORMAT format;
                float32 timeSpan;
        };
    }
}
