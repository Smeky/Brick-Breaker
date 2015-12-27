#pragma once

#include <stdint-gcc.h>

namespace bb {

class IDrawable {
public:
    IDrawable();
    virtual ~IDrawable() {};

    virtual void draw() const {}

    uint32_t getVAO() const;

protected:
    uint32_t m_VAO;

};

} // namespace bb
