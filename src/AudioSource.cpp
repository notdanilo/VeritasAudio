#include <Veritas/Audio/AudioSource.h>

using namespace Veritas;
using namespace Audio;

AudioSource::AudioSource(uint32 framerate, FORMAT format, uint8 channels, float32 timeSpan)
    : AudioNode(framerate, format, channels, timeSpan)
{}
