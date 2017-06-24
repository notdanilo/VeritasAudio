#pragma once

#include <Veritas/Audio/BinaryOpNode.h>

namespace Veritas {
    namespace Audio {
        class MulNode : public BinaryOpNode {
            public:
                template <class T>
                MulNode(T&& a, T&& b)
                    : AudioNode(a.getFramerate(), a.getFormat(), a.getChannels(), a.getTimeSpan())
                    , BinaryOpNode(std::forward<T>(a), std::forward<T>(b))
                {}
                MulNode(MulNode&& move);

            private:
                void operate(float32 *a, float32 *b, uint32 ammount);
        };
    }
}
