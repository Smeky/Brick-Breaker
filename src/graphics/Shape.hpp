#pragma once

#include <IRenderable.hpp>
#include <Transformable.hpp>

namespace bb {

class Shape : public IRenderable, public Transformable {
public:
    Shape();

    virtual void render( Renderer& renderer, RenderStates states ) const {}

protected:


private:


};

} // namespace bb
