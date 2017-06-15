#include <Veritas/Audio/AudioSink.h>

using namespace Veritas;
using namespace Audio;

AudioSink::AudioSink(uint32 framerate, FORMAT format) : AudioNode(framerate, format) {}
