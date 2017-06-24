#include <Veritas/Audio/BinaryOpNode.h>

using namespace Veritas;
using namespace Audio;

void BinaryOpNode::read(uint8 *data0, uint32 ammount) {
    uint8 data1[ammount];
    getSource(0).read(data0, ammount);
    getSource(1).read(data1, ammount);
    float32 *a = (float32*) data0;
    float32 *b = (float32*) data1;
    operate(a, b, ammount / getSource(0).getBytesPerFrame() * getSource(0).getChannels());
}
