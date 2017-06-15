#include <Veritas/Audio/AudioSource.h>

using namespace Veritas;
using namespace Audio;

AudioSource::AudioSource(uint32 framerate, FORMAT format) : AudioNode(framerate, format) {}
