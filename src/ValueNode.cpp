#include <Veritas/Audio/ValueNode.h>

#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace Veritas;
using namespace Audio;

ValueNode::ValueNode(float32 value)
    : AudioSource(1, FLOAT32)
    , bytes(sizeof(value))
{
    this->value = malloc(bytes);
    memcpy(this->value, &value, bytes);
}

ValueNode::~ValueNode() {
    free(value);
}

void ValueNode::read(uint8 *buffer, uint32 bytes) {
    uint32 written;
    for (written = 0; written < bytes; written += this->bytes)
        memcpy(&buffer[written], value, this->bytes);
    assert(written == bytes);
}
