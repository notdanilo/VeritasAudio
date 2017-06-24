#include <Veritas/Audio/MulNode.h>

using namespace Veritas;
using namespace Audio;

void MulNode::operate(float32 *a, float32 *b, uint32 ammount) {
    for (uint32 i = 0; i < ammount; i++)
        a[i] *= b[i];
}
