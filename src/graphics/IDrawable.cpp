#include "IDrawable.hpp"

namespace bb {

IDrawable::IDrawable()
: m_VAO( 0 )
{}

uint32_t IDrawable::getVAO() const {
    return m_VAO;
}

} // namespace bb
