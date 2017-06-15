#include <Veritas/Audio/SineGenerator.h>
#include <Veritas/Math/Math.h>

#include <Veritas/Audio/ValueNode.h>

using namespace Veritas;
using namespace Audio;
using namespace Math;

SineGenerator::SineGenerator(uint32 framerate, FORMAT format)
    : AudioSource(framerate, format)
    , time(0)
{
    frequencySource = new ValueNode(440.0f);
}

#include <iostream>
#include <cassert>

void SineGenerator::read(uint8 *data, uint32 bytes) {
    float32 *floats = (float32*) data;
    uint32 frames = bytes / sizeof(float32);

    float32 frequency[frames];
    frequencySource->read((uint8*) &frequency, sizeof(frequency));

    float32 framerate = getFramerate();
    float32 fraction = 1.0f / framerate;
    for (uint32 i = 0; i < frames; i++) {
        floats[i] = sin(frequency[i] * TAU * time / framerate);
        time++;
    }
}

void SineGenerator::frequency(AudioSource &frequency) {
    this->frequencySource = &frequency;
}
