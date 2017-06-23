#pragma once

#include <Veritas/Definitions/Definitions.h>

#include <Veritas/Audio/AudioSink.h>
#include <Veritas/Audio/AudioSource.h>

#include <Veritas/Data/String.h>

#include <pulse/pulseaudio.h>

namespace Veritas {
    namespace Audio {
        class AudioPlayback : public AudioSink {
            public:
                AudioPlayback(uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f);
                AudioPlayback(const Data::String& deviceName, uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f);
                ~AudioPlayback();

                void read(uint8 *buffer, uint32 bytes);

                void setTimeSpan(float32 timeSpan);
            private:
                AudioPlayback(const char* name, uint32 framerate, FORMAT format, uint8 channels, float32 timeSpan);
                pa_stream* stream;
                pa_threaded_mainloop* mainloop;
                pa_context* context;
                pa_sample_spec sample_specifications;
        };
    }
}
