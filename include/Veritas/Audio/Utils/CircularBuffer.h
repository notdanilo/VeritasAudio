#pragma once

#include <Veritas/Data/Buffer.h>

namespace Veritas {
    namespace Audio {
        namespace Utils {
            class CircularBuffer : public Data::Buffer {
                public:
                    CircularBuffer();
                    CircularBuffer(uint32 ammount);

                    class Part {
                        public:
                            Part(uint8* data, uint32 size);

                            uint8* getData() const;
                            uint32 getSize() const;
                        private:
                            uint8* data;
                            uint32 size;
                    };
                    typedef std::vector<Part> Parts;

                    uint32 write(const uint8* data, uint32 ammount);
                    uint32 read(uint8* data, uint32 ammount);

                    uint32 getPosition() const;
                    uint32 getOccupied() const;

                    Parts write(uint32 ammount);
                    const Parts read(uint32 ammount);
                private:
                    uint32 position;
                    uint32 occupied;

                    uint32 getReadPosition() const;
            };
        }
    }
}
