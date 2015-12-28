#pragma once

#include <Shader.hpp>
#include <Matrix4.hpp>

namespace bb {

struct RenderStates {
    Shader* shader = nullptr;
    Matrix4 transform;
};

} // namespace bb
