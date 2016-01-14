#pragma once

#include <Vector2.hpp>

#include <string>

namespace bb {

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile( const std::string& filename );

    void bind();

private:
    uint32_t m_handle;

    Vec2i m_size;
};

} // namespace bb
