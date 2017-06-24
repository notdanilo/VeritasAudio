#include <Veritas/Audio/FileSource.h>

#include <cassert>

using namespace Veritas;
using namespace Audio;
using namespace Data;

AudioNode getNodeInfo(const String& name) {
    FILE *file = fopen((const char*) name.getBuffer().getData(), "rb");
    OggVorbis_File vf;
    assert(file);
    assert(ov_open_callbacks(file, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) >= 0); // Input does not appear to be an Ogg bitstream
    vorbis_info *vi = ov_info(&vf,-1);
    return AudioNode(vi->rate, AudioNode::FLOAT32, vi->channels, 1.0f);
}

FileSource::FileSource(const String &name)
    : AudioNode(getNodeInfo(name))
    , AudioSource(getFramerate(), getFormat(), getChannels(), getTimeSpan())
{
    FILE *file = fopen((const char*) name.getBuffer().getData(), "rb");
    ov_open_callbacks(file, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE);

    vorbis_info *vi = ov_info(&vf,-1);
    duration = ov_pcm_total(&vf,-1) / float32(getFramerate());
}

FileSource::~FileSource() {
    ov_clear(&vf);
}

void FileSource::read(uint8 *data, uint32 ammount) {
    int32 requestedFrames = ammount / getBytesPerFrame();
    while (requestedFrames) {
        float32 **pcm;
        int32 frames = ov_read_float(&vf, &pcm, requestedFrames, &current_section);
        if (frames < 0)  assert(frames != OV_EBADLINK); // Corrupt bitstream section!
        else if (frames == 0) { // eof
            float32* floats = (float32*) data;
            for (uint32 i = 0; i < requestedFrames; i++)
                for (uint32 c = 0; c < getChannels(); c++)
                    floats[i*getChannels() + c] = 0.0f;
            requestedFrames = 0;
        } else {
            requestedFrames -= frames;
            float32* floats = (float32*) data;
            for (uint32 i = 0; i < frames; i++)
                for (uint32 c = 0; c < getChannels(); c++)
                    floats[i*getChannels() + c] = pcm[c][i];
            data += frames * getBytesPerFrame();
        }
    }
}

const float32 FileSource::getDuration() const { return duration; }
