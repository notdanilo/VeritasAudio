#include <Veritas/Audio/AudioSink.h>

using namespace Veritas;
using namespace Audio;

AudioSink::AudioSink(uint32 framerate, FORMAT format, uint32 sources)
    : AudioNode(framerate, format)
    , sources(sources)
{}

uint32 AudioSink::getSourcesQuantity() const { return sources.size(); }

void AudioSink::connect(AudioSource& source, uint32 index) { sources[index] = source; }

AudioSource& AudioSink::getSource(uint32 index) { return *sources[index]; }
