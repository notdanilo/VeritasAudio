#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Audio/Utils/CircularBuffer.h>

#include <pulse/pulseaudio.h>

#include <queue>
#include <mutex>

namespace Veritas {
    namespace Audio {
        class AudioCapture : public AudioSource {
            public:
                AudioCapture(float32 timeSpan, uint32 framerate, uint8 channels, FORMAT format);
                ~AudioCapture();

                void read(uint8* buffer, uint32 bytes);
                void setTimeSpan(float32 timeSpan);

                Audio::Utils::CircularBuffer buffer;
                std::mutex mtx;
            private:
                uint32 framerate;
                uint8 channels;
                pa_stream* stream;
                pa_threaded_mainloop* mainloop;
                pa_context* context;
                pa_sample_spec sample_specifications;
        };
    }
}
