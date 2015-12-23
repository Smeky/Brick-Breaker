#ifndef IDRAWABLE_H
#define IDRAWABLE_H

namespace bb {

class IDrawable {
public:
    virtual ~IDrawable() {};

    virtual void draw() const = 0;
};

} // namespace bb

#endif // IDRAWABLE_H
