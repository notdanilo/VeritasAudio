#include <Veritas/Audio/AudioNode.h>

using namespace Veritas;
using namespace Audio;

AudioNode::AudioNode(uint32 framerate, FORMAT format, uint8 channels, float32 timeSpan)
    : framerate(framerate)
    , format(format)
    , channels(channels)
    , timeSpan(timeSpan)
{}

uint32 AudioNode::getFramerate() const { return framerate; }
AudioNode::FORMAT AudioNode::getFormat() const { return format; }

void AudioNode::setTimeSpan(float32 timeSpan) { this->timeSpan = timeSpan; }
float32 AudioNode::getTimeSpan() const { return timeSpan; }

uint32 AudioNode::getBytesPerFrame() const { return getChannels() * (format / 8); }

uint8 AudioNode::getChannels() const { return channels; }
