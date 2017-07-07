#include <Veritas/Audio/FFT.h>
#include <Veritas/Math/Math.h>
#include <complex>

#include <cstring>

using namespace Veritas;
using namespace Audio;

using vec2 = Math::vec2;
using Complex = std::complex<float32>;

FFT::FFT(uint32 framerate, FORMAT format, float32 timeSpan)
    : AudioNode(framerate, format, 1, timeSpan)
    , AudioSink(framerate, format, 1, timeSpan)
    , AudioSource(framerate, format, 1, timeSpan)
{
    setTimeSpan(getTimeSpan());
}

void FFT::setTimeSpan(float32 timeSpan) {
    AudioNode::setTimeSpan(timeSpan);
    inBuffer.setSize(getTimeSpan() * getFramerate() * getBytesPerFrame());
    outBuffer.setSize(inBuffer.getSize() * 2);
}

#include <valarray>
typedef std::valarray<Complex> CArray;

// Cooley–Tukey FFT (in-place)
void fft(CArray& x) // non-pot arrays has elements discarded
{
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0f, -2.0f * float32(PI) * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

void FFT::read(uint8 *data, uint32 ammount) {
    uint32 frames = ammount / sizeof(vec2);

    float32 *floats = (float32*) inBuffer.getData();
    Complex* complexes = (Complex*) outBuffer.getData();

    if (inBuffer.getOccupied() == 0) {
        inBuffer.write(inBuffer.getSize());
        getSource(0).read(inBuffer.getData(), inBuffer.getSize());
        outBuffer.write(outBuffer.getSize());

        CArray carray(frames);
        for (uint32 i = 0; i < frames; i++)
            carray[i] = Complex(floats[i], 0.0f);

        fft(carray);

        for (uint32 i = 0; i < frames; i++)
            complexes[i] = carray[i];
    }

    inBuffer.free(inBuffer.getSize());
    outBuffer.free(outBuffer.getSize());

    memcpy(data, outBuffer.getData(), outBuffer.getSize());
}
