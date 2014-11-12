#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <memory>
#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/math/Transform.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace geometry {


    class Shape {
    public:
      //! Initializes all derived Shapes with a Transform and a Shader
      Shape(const math::Transform &transform);

      //! Copy Constructor
      Shape(const Shape&);

      //! Destructor
      virtual ~Shape();

      /*! \brief Virtual function for hit
       *
       *
       * Hit accepts a world space ray and returns true if it hits the shape and
       * tHit to the hit distance from the ray's origin.  Returns false otherwise.
       * All derived shapes must implement hit.
       */
      virtual bool hit(const utils::Ray &ws_ray, float &tHit) const = 0;


      virtual bool hit(const utils::Ray &ws_ray, float &tHit,
           std::shared_ptr<DifferentialGeometry> &dg) const = 0;

      /* \brief virtual function for hit with DifferentialGeometry
       *
       * Does what the hit above describes plus also returns a smart pointer
       * to a DifferentialGeometry object
       */

      //! converts ray from world to object space
      const math::Transform worldToObjectSpace() const;

      //! converts ray from object to world space
      const math::Transform objectToWorldSpace() const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };

  }
}

#endif // __SHAPE_H__
