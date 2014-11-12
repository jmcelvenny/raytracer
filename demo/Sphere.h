#include "Box.h"
#include <gssmraytracer/geometry/Shape.h>
#include <gssmraytracer/math/Transform.h>
#include <memory>

namespace gssmraytracer {
  namespace geometry {
    class Sphere : public Shape {
    public:
      Sphere (const math::Transform &transform,
                          const float radius);
      Sphere (const math::Transform &transform,
                          const float radius, float z0, float z1, float pm=360.0f);
      bool hit(const utils::Ray &ws_ray, float &tHit) const;
      bool hit(const utils::Ray &ws_ray, float &tHit,
               std::shared_ptr<DifferentialGeometry> &dg) const;


      virtual ~Sphere();
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
