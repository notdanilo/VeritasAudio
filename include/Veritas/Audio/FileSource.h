#pragma once

#include <Veritas/Audio/AudioSource.h>
#include <Veritas/Data/String.h>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

namespace Veritas {
    namespace Audio {
        class FileSource : public AudioSource {
            public:
                FileSource(const Data::String& name);
                ~FileSource();

                const float32 getDuration() const;

                void read(uint8 *data, uint32 ammount);
            private:
                float32 duration;
                int current_section;
                OggVorbis_File vf;
        };
    }
}
