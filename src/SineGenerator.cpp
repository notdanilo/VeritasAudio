#include <Veritas/Audio/SineGenerator.h>
#include <Veritas/Math/Math.h>

#include <Veritas/Audio/ValueNode.h>

using namespace Veritas;
using namespace Audio;
using namespace Math;

SineGenerator::SineGenerator(uint32 framerate, FORMAT format, float32 timespan)
    : AudioNode(framerate, format, 1, timespan)
    , AudioSource(framerate, format, 1, timespan)
    , AudioSink(framerate, format, 1, timespan)
    , time(0)
{
    connect(ValueNode(440.0));
}

void SineGenerator::read(uint8 *data, uint32 bytes) {
    float32 *floats = (float32*) data;
    uint32 frames = bytes / sizeof(float32);

    float32 frequency[frames];
    getSource().read((uint8*) &frequency, sizeof(frequency));

    float32 framerate = getFramerate();
    for (uint32 i = 0; i < frames; i++) {
        floats[i] = sin(frequency[i] * TAU * time / framerate);
        time++;
    }
}
