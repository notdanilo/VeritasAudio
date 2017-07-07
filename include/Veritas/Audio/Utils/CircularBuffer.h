#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace Audio {
        namespace Utils {
            class CircularBuffer {
                public:
                    CircularBuffer();
                    CircularBuffer(uint32 ammount);

                    void setSize(uint32 size);
                    uint32 getSize() const;

                    uint8* getData() const;

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
                    uint32 free(uint32 ammount);

                    uint32 getPosition() const;
                    uint32 getOccupied() const;

                    Parts write(uint32 ammount);
                    const Parts read(uint32 ammount);
                private:
                    std::vector<uint8> buffer;
                    uint32 position;
                    uint32 occupied;

                    uint32 getReadPosition() const;
            };
        }
    }
}
