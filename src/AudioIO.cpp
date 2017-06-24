#include <Veritas/Audio/AudioIO.h>

using namespace Veritas;
using namespace Audio;

AudioIO::AudioIO(uint32 framerate, FORMAT format, uint8 channels, float32 timeSpan, uint32 sources)
    : AudioNode(framerate, format, channels, timeSpan)
    , AudioSource(framerate, format, channels, timeSpan)
    , AudioSink(framerate, format, channels, timeSpan, sources)
{}
