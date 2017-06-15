#pragma once

#include <Veritas/Audio/AudioSource.h>

namespace Veritas {
    namespace Audio {
        class SineGenerator : public AudioSource {
            public:
                SineGenerator(uint32 framerate, FORMAT format);

                void frequency(AudioSource& source);

                void read(uint8 *data, uint32 bytes);
            private:
                AudioSource* frequencySource;
                uint32 framerate;
                uint32 time;
        };
    }
}
