#pragma once

#include <Veritas/Audio/AudioIO.h>

namespace Veritas {
    namespace Audio {
        class BinaryOpNode : public AudioIO {
            public:
                template <class T, class U>
                BinaryOpNode(T&& a, U&& b)
                    : AudioNode(a.getFramerate(), a.getFormat(), a.getChannels(), a.getTimeSpan())
                    , AudioIO(a.getFramerate(), a.getFormat(), a.getChannels(), a.getTimeSpan(), 2)
                {
                    connect(std::forward<T>(a), 0);
                    connect(std::forward<U>(b), 1);
                }


                void read(uint8 *data, uint32 ammount);
            protected:
                virtual void operate(float32 *a, float32 *b, uint32 ammount) = 0;
        };
    }
}
