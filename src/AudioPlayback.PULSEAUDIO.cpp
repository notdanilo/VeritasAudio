#include <Veritas/Audio/AudioPlayback.h>
#include <Veritas/Audio/ValueNode.h>

#include <pulse/pulseaudio.h>

#include <iostream>

using namespace Veritas;
using namespace Audio;

static void context_state_cb(pa_context* context, void* mainloop) { pa_threaded_mainloop_signal((pa_threaded_mainloop*) mainloop, 0); }
static void stream_state_cb(pa_stream *s, void *mainloop) { pa_threaded_mainloop_signal((pa_threaded_mainloop*) mainloop, 0); }
static void stream_success_cb(pa_stream *stream, int success, void *userdata) { return; }
static void stream_underflow_cb(pa_stream *stream, void *userdata) { return ; }

void stream_callback(pa_stream *stream, size_t requestedBytes, void *userdata) {
    AudioPlayback *ao = (AudioPlayback*) userdata;

    uint8* buffer = NULL;

    while (requestedBytes) {
        size_t availableBytes = requestedBytes;
        pa_stream_begin_write(stream, (void**) &buffer, &availableBytes);
        requestedBytes -= availableBytes;

        ao->read(buffer, availableBytes);

        pa_stream_write(stream, buffer, availableBytes, NULL, 0LL, PA_SEEK_RELATIVE);
    }
}

AudioPlayback::AudioPlayback(float32 timeSpan, uint32 framerate, uint8 channels, FORMAT iformat)
    : AudioSink(framerate, iformat)
    , AudioNode(timeSpan, framerate, iformat)
    , channels(channels)
    , framerate(framerate)
{
    connect(ValueNode(0.0f));
    pa_sample_format_t format = PA_SAMPLE_INVALID;
    switch (iformat) {
        case UINT8: format = PA_SAMPLE_U8; break;
        case INT16LE: format = PA_SAMPLE_S16LE; break;
        case INT32LE: format = PA_SAMPLE_S32LE; break;
        case INT16BE: format = PA_SAMPLE_S16BE; break;
        case INT32BE: format = PA_SAMPLE_S32BE; break;
        case FLOAT32LE: format = PA_SAMPLE_FLOAT32LE; break;
        case FLOAT32BE: format = PA_SAMPLE_FLOAT32BE; break;
        case FLOAT32: format = PA_SAMPLE_FLOAT32; break;
    }

    // Get a mainloop and its context
    mainloop = pa_threaded_mainloop_new();
    pa_mainloop_api *mainloop_api = pa_threaded_mainloop_get_api(mainloop);
    context = pa_context_new(mainloop_api, "Playback");

    // Set a callback so we can wait for the context to be ready
    pa_context_set_state_callback(context, &context_state_cb, mainloop);

    // Lock the mainloop so that it does not run and crash before the context is ready
    pa_threaded_mainloop_lock(mainloop);

    // Start the mainloop
    assert(pa_threaded_mainloop_start(mainloop) == 0);
    assert(pa_context_connect(context, NULL, PA_CONTEXT_NOAUTOSPAWN, NULL) == 0);

    // Wait for the context to be ready
    for(;;) {
        pa_context_state_t context_state = pa_context_get_state(context);
        assert(PA_CONTEXT_IS_GOOD(context_state));
        if (context_state == PA_CONTEXT_READY) break;
        pa_threaded_mainloop_wait(mainloop);

    }

    // Create a playback stream
    sample_specifications.format = format;
    sample_specifications.rate = framerate;
    sample_specifications.channels = channels;

    pa_channel_map map;
    pa_channel_map_init_auto(&map, channels, PA_CHANNEL_MAP_DEFAULT);

    stream = pa_stream_new(context, "Sink", &sample_specifications, &map);
    pa_stream_set_state_callback(stream, stream_state_cb, mainloop);
    pa_stream_set_write_callback(stream, stream_callback, this);
    pa_stream_set_underflow_callback(stream, stream_underflow_cb, NULL);

    uint32 bytes = pa_usec_to_bytes(getTimeSpan() * 1000000, &sample_specifications);

    // recommended settings, i.e. server uses sensible values
    pa_buffer_attr buffer_attr;
    buffer_attr.maxlength = (uint32_t) -1;
    buffer_attr.prebuf = (uint32_t) -1;
    buffer_attr.minreq = (uint32_t) -1;
    buffer_attr.fragsize = (uint32_t) -1;
    buffer_attr.tlength = bytes;

    // Settings copied as per the chromium browser source
    pa_stream_flags_t stream_flags;
    stream_flags = (pa_stream_flags_t)(PA_STREAM_START_CORKED | PA_STREAM_INTERPOLATE_TIMING | PA_STREAM_NOT_MONOTONIC | PA_STREAM_AUTO_TIMING_UPDATE | PA_STREAM_ADJUST_LATENCY);

    // Connect stream to the default audio output sink
    assert(pa_stream_connect_playback(stream, NULL, &buffer_attr, stream_flags, NULL, NULL) == 0);

    // Wait for the stream to be ready
    for(;;) {
        pa_stream_state_t stream_state = pa_stream_get_state(stream);
        assert(PA_STREAM_IS_GOOD(stream_state));
        if (stream_state == PA_STREAM_READY) break;
        pa_threaded_mainloop_wait(mainloop);
    }

    pa_threaded_mainloop_unlock(mainloop);

    // Uncork the stream so it will start playing
    pa_stream_cork(stream, 0, stream_success_cb, mainloop);
}

AudioPlayback::~AudioPlayback() {
    pa_stream_cork(stream, 1, stream_success_cb, mainloop);
    pa_stream_disconnect(stream);

    pa_context_disconnect(context);

    pa_threaded_mainloop_stop(mainloop);
    pa_threaded_mainloop_free(mainloop);
}

void AudioPlayback::read(uint8 *buffer, uint32 bytes) {
    getSource().read(buffer, bytes);
}

void AudioPlayback::setTimeSpan(float32 timeSpan) {
    AudioNode::setTimeSpan(timeSpan);

    uint32 bytes = pa_usec_to_bytes(getTimeSpan() * 1000000, &sample_specifications);

    // recommended settings, i.e. server uses sensible values
    pa_buffer_attr buffer_attr;
    buffer_attr.maxlength = (uint32_t) -1;
    buffer_attr.prebuf = (uint32_t) -1;
    buffer_attr.minreq = (uint32_t) -1;
    buffer_attr.fragsize = (uint32_t) -1;
    buffer_attr.tlength = bytes;

    pa_stream_set_buffer_attr(stream, &buffer_attr, stream_success_cb, 0);
}
