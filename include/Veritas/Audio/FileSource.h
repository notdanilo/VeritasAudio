#pragma once

#include <Veritas/Audio/AudioSource.h>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <cstdio>

namespace Veritas {
    namespace Audio {
        class FileSource : public AudioSource {
            public:
                FileSource(const std::string& name);
                ~FileSource();

                const float32 getDuration() const;

                void read(uint8 *data, uint32 ammount);
            private:
                float32 duration;
                int current_section;
                FILE* file;
                OggVorbis_File vf;
        };
    }
}
