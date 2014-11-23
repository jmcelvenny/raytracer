#include "Box.h"
#include <gssmraytracer/geometry/Shape.h>
#include <gssmraytracer/math/Transform.h>
#include <memory>

namespace gssmraytracer {
  namespace geometry {
    class Plane : public Shape {
    public:
      Plane (const math::Transform &transform,
                          const float radius);
      Plane (const math::Transform &transform,
                          const float radius, float z0, float z1, float pm=360.0f);
      bool hit(const utils::Ray &ws_ray, float &tHit) const;
      bool hit(const utils::Ray &ws_ray, float &tHit,
               std::shared_ptr<DifferentialGeometry> &dg) const;


      virtual ~Plane();
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
