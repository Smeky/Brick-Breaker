#pragma once

#include <stdint-gcc.h>
#include <Vertex.hpp>

namespace bb {

class Renderer {
public:
    Renderer();

    static uint32_t createVAO( uint32_t size, const Vertex* vertices );

private:


};

} // namespace bb
