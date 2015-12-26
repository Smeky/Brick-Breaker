#pragma once

#include <Transformable.hpp>
#include <IDrawable.hpp>
#include <stdint-gcc.h>

namespace bb {

class Sprite : public IDrawable, public Transformable {
public:
    Sprite();

    void draw() const;

    void static createSpriteVAO();

private:
    static uint32_t s_spriteVAO;

};

} // namespace bb
