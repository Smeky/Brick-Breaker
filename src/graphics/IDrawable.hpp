#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable {
public:
    virtual ~IDrawable() {};

    virtual void draw() const = 0;
};

#endif // IDRAWABLE_H
