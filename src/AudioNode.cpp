#include <Veritas/Audio/AudioNode.h>

using namespace Veritas;
using namespace Audio;

AudioNode::AudioNode(uint32 framerate, FORMAT format) : framerate(framerate), format(format) {}

uint32 AudioNode::getFramerate() const { return framerate; }
AudioNode::FORMAT AudioNode::getFormat() const { return format; }
