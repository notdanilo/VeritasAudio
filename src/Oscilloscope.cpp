#include <Veritas/Audio/Oscilloscope.h>

#include <Veritas/Audio/ValueNode.h>

#include <chrono>

using Clock = std::chrono::high_resolution_clock;

using namespace Veritas;
using namespace Audio;
using namespace GPU;
using namespace Programs;
using namespace Audio;
using Audio::Utils::CircularBuffer;

Oscilloscope::Oscilloscope(FrameBuffer& framebuffer, uint32 rate, FORMAT format)
    : AudioNode(rate, format)
    , AudioSink(rate, format)
    , framebuffer(framebuffer)
    , fp("precision highp float;"
        "layout(location = 0) uniform vec4 icolor;"
        "out vec4 ocolor;"
        "void main(void) {"
           "ocolor = icolor;"
        "}")
    , vp("layout(location = 0) in vec2 position;"
        "void main(void) {"
           "gl_Position = vec4(position, 0.0, 1.0);"
        "}")
    , rp(vp, fp)
    , mode(REDRAW)
{
    connect(ValueNode(0.0f));

    setTimeSpan(getTimeSpan());

    t0 = Clock::now();
}

void Oscilloscope::setTimeSpan(float32 timeSpan) {
    AudioNode::setTimeSpan(timeSpan);
    buffer.setSize(getTimeSpan() * getFramerate() * getBytesPerFrame());
}

void Oscilloscope::setMode(MODE mode) { this->mode = mode; }
Oscilloscope::MODE Oscilloscope::getMode() const { return mode; }

void Oscilloscope::run() {
    Clock::time_point t1 = Clock::now();
    float32 dt = std::chrono::duration<float32>(t1 - t0).count();
    t0 = t1;

    if (dt > getTimeSpan()) dt = getTimeSpan();

    uint32 framesToRead = dt * getFramerate();
    uint32 bytesToRead = framesToRead * getBytesPerFrame();

    CircularBuffer::Parts parts = buffer.write(bytesToRead);
    for (auto& part : parts) getSource().read(part.getData(), part.getSize());

    switch (mode) {
        case REDRAW: {
            uint32 frames = buffer.getSize() / getBytesPerFrame();

            float32* y = (float32*) buffer.getData();
            vec2 pointsData[frames];
            for (uint32 i = 0; i < frames; i++)
                pointsData[i] = vec2(2.0f * i / float32(frames) - 1.0f, y[i]);

            cp.clear(framebuffer, vec4(0.0f, 0.0f, 0.0f, 1.0f));
            GPU::Buffer points(sizeof(pointsData), pointsData);
            rp.lines(framebuffer, frames - 1, false, { VertexBinding(0, points, 2), UniformBinding(0, fp, vec4(1.0)) });
        } break;
        case CONTINUOUS: {
            uint32 totalFrames = buffer.getSize() / getBytesPerFrame();

            vec2 pointsData[totalFrames];
            parts = buffer.write(buffer.getSize());
            uint32 i = 0;
            for (auto& part : parts) {
                float32* y = (float32*) part.getData();
                uint32 partialFrames = part.getSize() / getBytesPerFrame();
                for (uint32 j = 0; j < partialFrames; j++)
                    pointsData[i++] = vec2(2.0f * i / float32(totalFrames) - 1.0f, y[j]);
            }

            cp.clear(framebuffer, vec4(0.0f, 0.0f, 0.0f, 1.0f));
            GPU::Buffer points(sizeof(pointsData), pointsData);
            rp.lines(framebuffer, totalFrames - 1, false, { VertexBinding(0, points, 2), UniformBinding(0, fp, vec4(1.0)) });
        }
    }
}
