#ifndef __RAY_H__
#define __RAY_H__
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/math/Vector.h"
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class Ray {
    public:
      /* \brief Initializes a ray with a point and direction vector
       *
       * The point (origin) and direction is initialized to (0,0,0)
       */
      Ray();

      //!brief Initialize a ray with a given point and direction
      Ray(const geometry::Point &origin, const math::Vector &direction);

      //! returns the origin
      const geometry::Point origin() const;

      //! returns the normalized direction
      const math::Vector dir() const;

      //! returns the minimum t range for the ray
      const double mint() const;

      //! sets the minimum t range for the ray
      void setMint(const double);

      //! returns the maximum t range for the ray
      const double maxt() const;

      //! sets the maximum t range for the ray
      void setMaxt(const double);

      //! returns the resulting point based on the provided t value
      const geometry::Point operator()(const float t) const;

      //! output operator for printing the ray information
      friend std::ostream& operator<<(std::ostream &os, const Ray &ray);

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
#endif // __RAY_H__
