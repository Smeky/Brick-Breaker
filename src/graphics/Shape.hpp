#pragma once

#include <IDrawable.hpp>
#include <Transformable.hpp>

namespace bb {

class Shape : public IDrawable, public Transformable {
public:
    Shape();

    virtual void draw() {}

protected:


private:


};

} // namespace bb
