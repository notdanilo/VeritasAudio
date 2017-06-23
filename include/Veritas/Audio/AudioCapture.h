#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Audio/Utils/CircularBuffer.h>
#include <Veritas/Data/String.h>

#include <pulse/pulseaudio.h>

#include <queue>
#include <mutex>

namespace Veritas {
    namespace Audio {
        class AudioCapture : public AudioSource {
            public:
                AudioCapture(uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f);
                AudioCapture(const Data::String& deviceName, uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f);
                ~AudioCapture();

                AudioCapture(const AudioCapture& copy) = delete;
                AudioCapture(AudioCapture&& move) = delete;
                void operator=(const AudioCapture& copy) = delete;
                void operator=(AudioCapture&& move) = delete;

                void read(uint8* buffer, uint32 bytes);
                void setTimeSpan(float32 timeSpan);

                Audio::Utils::CircularBuffer buffer;
                std::mutex mtx;
            private:
                AudioCapture(const char* name, uint32 framerate, FORMAT format, uint8 channels, float32 timeSpan);
                pa_stream* stream;
                pa_threaded_mainloop* mainloop;
                pa_context* context;
                pa_sample_spec sample_specifications;
        };
    }
}
