#ifndef __PLANE_H__
#define __PLANE_H__

#include <gssmraytracer/geometry/Shape.h>
#include <gssmraytracer/utils/Ray.h>
#include <gssmraytracer/math/Vector.h>
#include <memory>

namespace gssmraytracer {
  namespace geometry {
    class Plane : public Shape {
    public:
      Plane();
      Plane(const math::Vector &loc, const math::Vector &norm, float ref);
      bool hit(const utils::Ray &ws_ray,
       float &tHit) const;
      bool hit(const utils::Ray &ws_ray,
       float &tHit, std::shared_ptr<DifferentialGeometry> &dg) const;
       const float reflectivity() const;
       Plane& operator=(const Plane&);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}

#endif
