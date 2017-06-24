#include <Veritas/Audio/DivNode.h>

using namespace Veritas;
using namespace Audio;

DivNode::DivNode(AudioSource &a, AudioSource &b)
    : AudioNode(a.getFramerate(), a.getFormat(), a.getChannels(), 1.0f)
    , BinaryOpNode(a, b)
{}

void DivNode::operate(float32* a, float32* b, uint32 ammount) {
    for (uint32 i = 0; i < ammount; i++)
        a[i] /= b[i];
}
