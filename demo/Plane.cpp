#include "Plane.h"
#include <gssmraytracer/geometry/Point.h>
#include <gssmraytracer/math/Transform.h>

namespace gssmraytracer {
  namespace geometry {
    class Plane::Impl {
    public:
      math::Vector normal;
      geometry::Point location;
      float reflectivity;
    };

    Plane::Plane() : Shape(math::Transform(), 0.f), mImpl(new Impl){
      mImpl->normal = math::Vector();
      mImpl->location = geometry::Point();
    }

    Plane::Plane(const math::Vector &loc, const math::Vector &n, float ref) : Shape(math::Transform(), ref), mImpl(new Impl) {
      mImpl->normal = n.normalized();
      mImpl->location = geometry::Point(loc);
      mImpl->reflectivity = ref;
    }

    bool Plane::hit(const utils::Ray &ws_ray, float &tHit) const {
      math::Transform tf = Shape::worldToObjectSpace();
      utils::Ray os_ray = tf(ws_ray);

      tHit = (0 - os_ray.origin().x()*mImpl->normal.x() - os_ray.origin().z()*mImpl->normal.y()
                - os_ray.origin().z()*mImpl->normal.z()) / mImpl->normal.dot(ws_ray.dir());
      if(tHit > (float)ws_ray.mint() && tHit < (float)ws_ray.maxt())
        return true;
      return false;
    }

    bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
      math::Transform tf = Shape::worldToObjectSpace();
      utils::Ray os_ray = tf(ws_ray);

      if(mImpl->normal.dot(os_ray.dir()))
        return false;
      tHit = (0 - os_ray.origin().x()*mImpl->normal.x() - os_ray.origin().z()*mImpl->normal.y()
                - os_ray.origin().z()*mImpl->normal.z()) / mImpl->normal.dot(os_ray.dir());
      if(tHit > (float)ws_ray.mint() && tHit < (float)ws_ray.maxt()) {
        dg->nn = geometry::Normal(mImpl->normal);
        dg->p = ws_ray(tHit);
        dg->dir = ws_ray.dir();
        return true;
      }
      return false;
    }

    Plane& Plane::operator=(const Plane& other) {
      if (this != &other) {
        mImpl->normal = other.mImpl->normal;
        mImpl->location = other.mImpl->location;
        mImpl->reflectivity = other.mImpl->reflectivity;
      }
      return *this;
    }

    const float Plane::reflectivity() const {
      return mImpl->reflectivity;
    }
  }
}
