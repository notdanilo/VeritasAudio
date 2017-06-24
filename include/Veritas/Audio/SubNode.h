#pragma once

#include <Veritas/Audio/BinaryOpNode.h>

namespace Veritas {
    namespace Audio {
        class SubNode : public BinaryOpNode {
            public:
                SubNode(AudioSource& a, AudioSource& b);
                SubNode(SubNode&& move);
            private:
                void operate(float32 *a, float32 *b, uint32 ammount);
        };
    }
}
