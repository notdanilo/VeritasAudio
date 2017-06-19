#include <Veritas/Audio/AudioNode.h>

using namespace Veritas;
using namespace Audio;

AudioNode::AudioNode(uint32 framerate, FORMAT format) : AudioNode(1.0f, framerate, format) {}
AudioNode::AudioNode(float32 timeSpan, uint32 framerate, FORMAT format)
    : framerate(framerate)
    , format(format)
    , timeSpan(timeSpan)
{}

uint32 AudioNode::getFramerate() const { return framerate; }
AudioNode::FORMAT AudioNode::getFormat() const { return format; }

void AudioNode::setTimeSpan(float32 timeSpan) { this->timeSpan = timeSpan; }
float32 AudioNode::getTimeSpan() const { return timeSpan; }

uint32 AudioNode::getBytesPerFrame() const { return format / 8; }
