#include <Veritas/Audio/Utils/CircularBuffer.h>
#include <Veritas/Math/Math.h>

#include <cstring>

using namespace Veritas;
using namespace Audio;
using namespace Utils;
using namespace Math;

CircularBuffer::CircularBuffer()
    : CircularBuffer(0)
{}

CircularBuffer::CircularBuffer(uint32 size)
    : buffer(size)
    , position(0)
    , occupied(0)
{}

CircularBuffer::Part::Part(uint8 *data, uint32 size)
    : data(data)
    , size(size)
{}

uint8* CircularBuffer::Part::getData() const { return data; }
uint32 CircularBuffer::Part::getSize() const { return size; }

uint32 CircularBuffer::getPosition() const { return position; }
uint32 CircularBuffer::getOccupied() const { return occupied; }

#include <cassert>
#include <iostream>

uint32 CircularBuffer::write(const uint8 *data, uint32 ammount) {
    if (ammount > getSize()) ammount = getSize();
    occupied += ammount;
    if (occupied > getSize()) occupied = getSize();

    uint32 remaining = ammount;
    if (ammount > getSize() - getPosition()) {
        ammount = getSize() - getPosition();
        remaining -= ammount;
    } else remaining = 0;

    memcpy(getData() + getPosition(), data, ammount);
    if (remaining) {
        memcpy(getData(), data + ammount, remaining);
        position = remaining;
    } else position += ammount;

    return ammount + remaining;
}

uint32 CircularBuffer::read(uint8 *data, uint32 ammount) {
    if (ammount > getOccupied()) ammount = getOccupied();

    uint32 remaining = ammount;
    if (ammount > getSize() - getReadPosition()) {
        ammount = getSize() - getReadPosition();
        remaining -= ammount;
    } else remaining = 0;

    memcpy(data, getData() + getReadPosition(), ammount);
    if (remaining) {
        memcpy(data + ammount, getData(), remaining);
    }

    occupied -= ammount + remaining;

    return ammount + remaining;
}

uint32 CircularBuffer::free(uint32 ammount) {
    if (ammount > getOccupied()) ammount = getOccupied();
    occupied -= ammount;
    return ammount;
}

uint32 CircularBuffer::getReadPosition() const {
    if (getPosition() >= getOccupied())
        return getPosition() - getOccupied();
    else
        return getSize() + getPosition() - getOccupied();
}

const CircularBuffer::Parts CircularBuffer::read(uint32 size) {
    if (size > getOccupied()) size = getOccupied();

    Parts parts;

    if (size <= getSize() - getReadPosition()) {
        parts.push_back(Part(getData() + getReadPosition(), size));
    } else {
        uint32 partialSize = getSize() - getReadPosition();
        uint32 remainingSize = size - partialSize;
        parts.push_back(Part(getData() + getReadPosition(), partialSize));
        parts.push_back(Part(getData() + 0, remainingSize));
    }

    occupied -= size;

    return parts;
}

CircularBuffer::Parts CircularBuffer::write(uint32 size) {
    size = min(size, getSize());

    Parts parts;

    if (size <= getSize() - getPosition()) {
        parts.push_back(Part(getData() + getPosition(), size));
    } else {
        uint32 partialSize = getSize() - getPosition();
        uint32 remainingSize = size - partialSize;
        parts.push_back(Part(getData() + getPosition(), partialSize));
        parts.push_back(Part(getData() + 0, remainingSize));
    }

    position = (position + size) % getSize();
    occupied = min(occupied + size, getSize());

    return parts;
}
