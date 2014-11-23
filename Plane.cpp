#include <gssmraytracer/utils/Ray.h>
#include <gssmraytracer/math/Transform.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/gssmraytracer.h>
#include "Plane.h"
#include <algorithm>
#include <iostream>

using namespace gssmraytracer::math;
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {

    class Plane::Impl {
    public:
    Plane::~Plane() {}

    bool Plane::hit(const utils::Ray &ws_ray, float &thit) const {

      float phi;
      Point phit;

      // Transform the ray into object space
      math::Transform tf = worldToObjectSpace();
      Ray os_ray = tf(ws_ray);

      //BOX
      Box box(Point(-mImpl->radius, -mImpl->radius, -mImpl->radius), Point(mImpl->radius, mImpl->radius, mImpl->radius));

      if (!box.intersect(os_ray,os_ray.mint(),os_ray.maxt()) ) {
    return false;
      }
      // Do ray-Plane intersection in object space
      // Compute quadratic Plane coefficients

      float A = os_ray.dir().x() * os_ray.dir().x() +
                os_ray.dir().y() * os_ray.dir().y() +
                os_ray.dir().z() * os_ray.dir().z();
      float B = 2.0 * (os_ray.dir().x() * os_ray.origin().x() +
                     os_ray.dir().y() * os_ray.origin().y() +
                     os_ray.dir().z() * os_ray.origin().z());
      float C = os_ray.origin().x() * os_ray.origin().x() +
                os_ray.origin().y() * os_ray.origin().y() +
                os_ray.origin().z() * os_ray.origin().z() -
                mImpl->radius * mImpl->radius;


      // Solve quadratic equation for t values
      float t0, t1;
      if (!mImpl->Quadratic(A,B,C, &t0, &t1)) return false;
      // compute intersection distance along ray
      if (t0 > os_ray.maxt() || t1 < os_ray.mint())
        return false;

      thit = t0;
      if (t0 < os_ray.mint()) {
        thit = t1;
        if (thit > os_ray.maxt()) return false;
      }


      // Compute Plane hit position and phi
      phit = os_ray(thit);

      if (phit.x() == 0.f && phit.y() == 0.f) phit.x(1e-5f * mImpl->radius);

      phi = atan2f(phit.y(), phit.x());

      if (phi < 0.) phi += 2.f*M_PI;

      // Test against clipping parameters
      if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
        (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
         phi > mImpl->phiMax) {
           if (thit == t1) return false;
           thit = t1;

           if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
             (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
             phi > mImpl->phiMax)
             return false;
         }


      return true;

    }
    bool Plane::hit(const Ray &ws_ray, float &thit,
                      std::shared_ptr<DifferentialGeometry> &dg) const {
      float phi;
      Point phit;

      // Transform the ray into object space
      Transform transform = worldToObjectSpace();
      Ray os_ray = transform(ws_ray);

      Box box(Point(-mImpl->radius, -mImpl->radius, -mImpl->radius), Point(mImpl->radius, mImpl->radius, mImpl->radius));

      if (!box.intersect(os_ray,os_ray.mint(),os_ray.maxt()) ) {
    return false;
      }

      // Do ray-Plane intersection in object space
      // Compute quadratic Plane coefficients

      float A = os_ray.dir().x() * os_ray.dir().x() +
                os_ray.dir().y() * os_ray.dir().y() +
                os_ray.dir().z() * os_ray.dir().z();
      float B = 2.0 * (os_ray.dir().x() * os_ray.origin().x() +
                     os_ray.dir().y() * os_ray.origin().y() +
                     os_ray.dir().z() * os_ray.origin().z());
      float C = os_ray.origin().x() * os_ray.origin().x() +
                os_ray.origin().y() * os_ray.origin().y() +
                os_ray.origin().z() * os_ray.origin().z() -
                mImpl->radius * mImpl->radius;


      // Solve quadratic equation for t values
      float t0, t1;
      if (!mImpl->Quadratic(A,B,C, &t0, &t1)) return false;
      // compute intersection distance along ray
      if (t0 > os_ray.maxt() || t1 < os_ray.mint())
        return false;

      thit = t0;
      if (t0 < os_ray.mint()) {
        thit = t1;
        if (thit > os_ray.maxt()) return false;
      }


      // Compute Plane hit position and phi
      phit = os_ray(thit);

      if (phit.x() == 0.f && phit.y() == 0.f) phit.x(1e-5f * mImpl->radius);

      phi = atan2f(phit.y(), phit.x());

      if (phi < 0.) phi += 2.f*M_PI;

      // Test against clipping parameters
      if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
        (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
         phi > mImpl->phiMax) {
           if (thit == t1) return false;
           thit = t1;

           if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
             (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
             phi > mImpl->phiMax)
             return false;
         }

         // find parametric representation of Plane
         float u = phi/mImpl->phiMax;

         float theta = acosf(Clamp(phit.z()/mImpl->radius, -1.f, 1.f));

         float v = (theta - mImpl->thetaMin) / (mImpl->thetaMax - mImpl->thetaMin);
         float zradius = sqrt(phit.x() * phit.x() + phit.y() * phit.y());
         float invzradius = 1.f / zradius;
         float cosphi = phit.x() * invzradius;
         float sinphi = phit.y() * invzradius;
         Vector dpdu(-mImpl->phiMax * phit.y(), mImpl->phiMax * phit.x(), 0);
         Vector dpdv = (mImpl->thetaMax - mImpl->thetaMin) *
                Vector(phit.z() * cosphi, phit.z() * sinphi,
                      -mImpl->radius * sinf(theta));

        Vector d2Pduu = -mImpl->phiMax * mImpl->phiMax * Vector(phit.x(), phit.y(), 0.0f);
        Vector d2Pduv = (mImpl->thetaMax - mImpl->thetaMin) * phit.z() * mImpl->phiMax * Vector(-sinphi, cosphi, 0.0f);
        Vector d2Pdvv = -(mImpl->thetaMax - mImpl->thetaMin) * (mImpl->thetaMax - mImpl->thetaMin) * Vector(phit.x(), phit.y(), phit.z());

        float E = dpdu.dot(dpdu);
        float F = dpdu.dot(dpdv);
        float G = dpdv.dot(dpdv);
        Vector N = dpdu.cross(dpdv).normalized();
        float e = N.dot(d2Pduu);
        float f = N.dot(d2Pduv);
        float g = N.dot(d2Pdvv);

        float invEGF2 = 1.f/(E * G - F * F);
        Normal dndu = Normal((f * F - e * G) * invEGF2 * dpdu +
                            (e * F - f * E) * invEGF2 * dpdv);
        Normal dndv = Normal((g * F - f * G) * invEGF2 * dpdu +
                            (f*F - g * E) * invEGF2 * dpdv);




      // if the ray intersects the Plane return true
      std::shared_ptr<DifferentialGeometry> dg_temp(new DifferentialGeometry(mImpl->o2w(os_ray(thit-.007)),
                                mImpl->o2w(dpdu),
                                mImpl->o2w(dpdv),
                                mImpl->o2w(dndu),
                                mImpl->o2w(dndv),
                                u, v, this));
      dg = dg_temp;

       return true;

    }

  }
}
