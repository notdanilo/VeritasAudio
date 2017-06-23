#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        class AudioNode {
            public:
                enum FORMAT { UINT8 = 8, INT16LE = 16, INT16BE = 17, INT32LE = 32, INT32BE = 33, FLOAT32LE = 34, FLOAT32BE = 35, FLOAT32 = 36 };
                AudioNode(uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f);

                virtual void setTimeSpan(float32 timeSpan);
                float32 getTimeSpan() const;

                uint32 getBytesPerFrame() const;

                uint8 getChannels() const;

                uint32 getFramerate() const;
                FORMAT getFormat() const;
            private:
                uint8 channels;
                uint32 framerate;
                FORMAT format;
                float32 timeSpan;
        };
    }
}
