#pragma once

#include <IDrawable.hpp>

namespace bb {

class Shape : public IDrawable {
public:
    Shape();

    virtual void draw() {}

protected:


private:


};

} // namespace bb
