#pragma once

#include <Veritas/Definitions/Definitions.h>

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/Audio/AudioSource.h>

#include <pulse/pulseaudio.h>

namespace Veritas {
    namespace Audio {
        class AudioPlayback : public AudioSink {
            public:
                AudioPlayback(float32 timeSpan, uint32 framerate, uint8 channels, FORMAT format);
                ~AudioPlayback();

                void read(uint8 *buffer, uint32 bytes);

                void setTimeSpan(float32 timeSpan);
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
