#pragma once

#include <Veritas/Audio/AudioNode.h>
#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Audio/Utils/Holder.h>

namespace Veritas {
    namespace Audio {
        class AudioSink : public virtual AudioNode {
            public:
                AudioSink(uint32 framerate, FORMAT format, uint8 channels = 1, float32 timeSpan = 1.0f, uint32 sources = 1);
                virtual ~AudioSink() = default;

                uint32 getSourcesQuantity() const;

                void connect(AudioSource& source, uint32 index = 0);
                template <class T>
                void connect(const T&& source, uint32 index = 0) { sources[index] = std::move(source); }

                AudioSource& getSource(uint32 index = 0);
            private:
                std::vector<Utils::Holder<AudioSource>> sources;
        };
    }
}
