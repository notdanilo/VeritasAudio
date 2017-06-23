#include <Veritas/Audio/SpectrumAnalyzer.h>

#include <Veritas/Audio/ValueNode.h>

#include <chrono>

using Clock = std::chrono::high_resolution_clock;

using namespace Veritas;
using namespace Audio;
using namespace GPU;
using namespace Programs;
using namespace Audio;
using Audio::Utils::CircularBuffer;

SpectrumAnalyzer::SpectrumAnalyzer(FrameBuffer& framebuffer, uint32 rate, FORMAT format, float32 timeSpan)
    : AudioNode(rate, format, 2, timeSpan)
    , AudioSink(rate, format, 2, timeSpan)
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

void SpectrumAnalyzer::setTimeSpan(float32 timeSpan) {
    AudioNode::setTimeSpan(timeSpan);
    buffer.setSize(getTimeSpan() * getFramerate() * getBytesPerFrame());
}

void SpectrumAnalyzer::setMode(MODE mode) { this->mode = mode; }
SpectrumAnalyzer::MODE SpectrumAnalyzer::getMode() const { return mode; }

void SpectrumAnalyzer::run() {
    Clock::time_point t1 = Clock::now();
    float32 dt = std::chrono::duration<float32>(t1 - t0).count();

    // special case implementation: it will read everything once, there is no streaming
    if (dt >= getTimeSpan()) {
        dt = getTimeSpan();
        t0 = t1;

        uint32 framesToRead = dt * getFramerate();
        uint32 bytesToRead = framesToRead * getBytesPerFrame();

        CircularBuffer::Parts parts = buffer.write(bytesToRead);
        for (auto& part : parts) getSource().read(part.getData(), part.getSize());

        if (buffer.getOccupied() == buffer.getSize()) {
            uint32 frames = buffer.getSize() / getBytesPerFrame();

            vec2* y = (vec2*) buffer.getData();
            buffer.free(buffer.getOccupied());
            vec2 pointsData[frames];
            for (uint32 i = 0; i < frames; i++)
                pointsData[i] = vec2(2.0f * i / float32(frames) - 1.0f, length(y[i]) - 1.0f);

            cp.clear(framebuffer, vec4(0.0f, 0.0f, 0.0f, 1.0f));
            GPU::Buffer points(sizeof(pointsData), pointsData);
            rp.lines(framebuffer, frames - 1, false, { VertexBinding(0, points, 2), UniformBinding(0, fp, vec4(1.0)) });
        }

    }
}
