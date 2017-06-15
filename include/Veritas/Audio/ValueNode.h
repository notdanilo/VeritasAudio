#pragma once

#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        class ValueNode : public AudioSource {
            public:
                ValueNode(float32 value);
                ValueNode(const ValueNode& node);
                ValueNode(ValueNode&& node) = delete;
                ~ValueNode();

                ValueNode& operator=(const ValueNode& node) = delete;
                ValueNode& operator=(ValueNode&& node) = delete;

                void read(uint8 *buffer, uint32 bytes);
            private:
                void *value;
                uint32 bytes;
        };
    }
}
