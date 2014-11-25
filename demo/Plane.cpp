#include "Plane.h"
#include "gssmraytracer/math/Transform.h"

using namespace gssmraytracer::geometry;

class Plane::Impl {
public:
  math::Vector norm;
  math::Vector q1;
  math::Vector q2;
  geometry::Point pt;
  float reflectivity;
};

Plane::Plane() : Shape(math::Transform(), 0.f), mImpl(new Impl){
  mImpl->norm = math::Vector();
  mImpl->pt = geometry::Point();
  mImpl->reflectivity = 0.f;
}

Plane::Plane(const math::Transform &pos, const math::Vector &v1, const math::Vector &v2, float ref) :
                    Shape(pos,ref), mImpl(new Impl)  {
  mImpl->q1 = v1.normalized();
  mImpl->q2 = (v2.normalized() - (v1.dot(v2)/v1.dot(v1))*v1).normalized();
  mImpl->norm = (mImpl->q1.cross(mImpl->q2)).normalized();
  mImpl->reflectivity = ref;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit) const {
  math::Transform t = Shape::worldToObjectSpace();
  utils::Ray os_ray = t(ws_ray);
  tHit = (0 - os_ray.origin().x()*mImpl->norm.x() - os_ray.origin().z()*mImpl->norm.y()
            - os_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(ws_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt())
    return true;
  return false;
}

bool Plane::hit(const utils::Ray &ws_ray, float &tHit, std::shared_ptr<geometry::DifferentialGeometry> &dg) const {
  math::Transform t = Shape::worldToObjectSpace();
  utils::Ray os_ray = t(ws_ray);
  if(fabs(mImpl->norm.dot(os_ray.dir())) == 0.f)
    return false;
  tHit = -1*(os_ray.origin().x()*mImpl->norm.x() + os_ray.origin().z()*mImpl->norm.y()
            + os_ray.origin().z()*mImpl->norm.z()) / mImpl->norm.dot(os_ray.dir());
  if(tHit > ws_ray.mint() && tHit < ws_ray.maxt()) {
    Point hit_pt = ws_ray(tHit);
    float q12 = mImpl->q1.dot(mImpl->q1);
    float q22 = mImpl->q2.dot(mImpl->q2);
    math::Vector vec(0-hit_pt.x(), 0-hit_pt.y(), 0-hit_pt.z());
    float v_dot_q1 = vec.dot(mImpl->q1);
    float v_dot_q2 = vec.dot(mImpl->q2);
    float uu = q12 * v_dot_q2;
    float vv = q22 * v_dot_q1;

    std::shared_ptr<DifferentialGeometry> dg_temp(new DifferentialGeometry(hit_pt, mImpl->q1, mImpl->q2, Normal(math::Vector()), Normal(math::Vector()), uu, vv, this, os_ray));
    dg_temp->dir = ws_ray.dir();
    dg = dg_temp;
    return true;
  }
  return false;
}
