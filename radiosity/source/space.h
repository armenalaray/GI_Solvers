/* date = March 16th 2021 2:46 pm */

#ifndef SPACE_H
#define SPACE_H

/* 
Esta es mi interface, puede preguntar a sus quds si son colisionados por el ray y si si, les pregunta
el color por medio de los uv
 */

#include <vector>
#include <memory>

#include "displayable.h"
#include "quad.h"
#include "ray.h"

class DisplayableSpace : public Displayable
{
    public:
    DisplayableSpace():
    quads{}
    {}
    // NOTE(Alex): Displayable override
    Color<int> request_color(Ray r, float tMin, float tMax) override;
    private:
    std::vector<std::shared_ptr<Quad>> quads;
};


#endif //SPACE_H