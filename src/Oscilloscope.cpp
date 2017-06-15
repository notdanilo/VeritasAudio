#include <Veritas/Audio/Oscilloscope.h>

#include <Veritas/Audio/ValueNode.h>

using namespace Veritas;
using namespace Audio;
using namespace GPU;
using namespace Programs;

Oscilloscope::Oscilloscope(FrameBuffer& framebuffer, uint32 rate, FORMAT format)
    : AudioSink(rate, format)
    , framebuffer(framebuffer)
    , fp("precision highp float;"
        "layout(location = 0) uniform vec4 icolor;"
        "out vec4 ocolor;"
        "void main(void) {"
           "ocolor = icolor;"
        "}")
    , vp("layout(location = 0) in vec2 position;"
        "layout(location = 0) uniform vec2 resolution;"
        "void main(void) {"
           "gl_Position = vec4(position / resolution * 2.0 - 1.0, 0.0, 1.0);"
        "}")
    , rp(vp, fp)
{
    connect(ValueNode(0.0f));
}

void Oscilloscope::run() {
    cp.clear(framebuffer, vec4(0.0f, 0.0f, 0.0f, 1.0f));

    float32 y[44100];
    getSource().read((uint8*) &y, sizeof(y));

    vec2 resolution = vec2(framebuffer.getWidth(), framebuffer.getHeight());
    vec2 offset = vec2(0.0f, resolution.y / 2.0f);
    vec2 factor = vec2(1.0f, resolution.y / 2.0f);

    vec2 pointsData[framebuffer.getWidth()];
    for (uint32 i = 0; i < framebuffer.getWidth(); i++) {
        uint32 index = sizeof(y) / sizeof(float32) * (i / float32(framebuffer.getWidth()));
        pointsData[i] = vec2(i, y[index]) * factor + offset;
    }

    Buffer points(sizeof(pointsData), pointsData);
    vec4 color = vec4(1.0);
    rp.lines(framebuffer, framebuffer.getWidth() - 1, false, { VertexBinding(0, points, 2), UniformBinding(0, vp, resolution), UniformBinding(0, fp, color) });
}
