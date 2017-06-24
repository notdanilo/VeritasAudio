#pragma once

#include <Veritas/Audio/BinaryOpNode.h>

namespace Veritas {
    namespace Audio {
        class AddNode : public BinaryOpNode {
            public:
                AddNode(AudioSource& a, AudioSource& b);
                AddNode(AddNode&& move);
            private:
                void operate(float32 *a, float32 *b, uint32 ammount);
        };
    }
}
