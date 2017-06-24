#pragma once

#include <Veritas/Audio/BinaryOpNode.h>

namespace Veritas {
    namespace Audio {
        class DivNode : public BinaryOpNode {
            public:
                DivNode(AudioSource& a, AudioSource& b);
                DivNode(DivNode&& move);
            private:
                void operate(float32 *a, float32 *b, uint32 ammount);
        };
    }
}
