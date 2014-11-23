#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/math/Transform.h"
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {
    class Shape::Impl {
    public:
      math::Transform transform;
      float reflectivity;
    };
    Shape::Shape(const math::Transform &transform, float r) :
      mImpl(new Impl) {
        mImpl->transform = transform;
        mImpl->reflectivity = r;
    }


    Shape::Shape(const Shape& shape) : mImpl(new Impl) {
      mImpl->transform = shape.mImpl->transform;
    }
    Shape::~Shape() {

    }

    const math::Transform Shape::worldToObjectSpace() const{


      return mImpl->transform;

    }
    const math::Transform Shape::objectToWorldSpace() const{

      return mImpl->transform.inverse();

    }

    const float Shape::reflectivity() const {
      return mImpl->reflectivity;
    }


  }
}
