#include "Box.h"
#include <gssmraytracer/geometry/Shape.h>
#include <gssmraytracer/math/Transform.h>
#include <memory>

namespace gssmraytracer {
  namespace geometry {
    class Triangle : public Shape {
    public:
      Triangle (const math::Transform &transform,
                          const Point &v1, const Point &v2, const Point &v3, const float ref);
      bool hit(const utils::Ray &ws_ray, float &tHit) const;
      bool hit(const utils::Ray &ws_ray, float &tHit,
               std::shared_ptr<DifferentialGeometry> &dg) const;

      const float reflectivity() const;
      virtual ~Triangle();
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
