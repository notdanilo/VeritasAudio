#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        class AudioNode {
            public:
                enum FORMAT { /*UINT8 = 8, INT16 = 16, INT32 = 32, */ FLOAT32 = 32 };
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
