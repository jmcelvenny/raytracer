#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/math/Transform.h"
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {
    class Shape::Impl {
    public:
      math::Transform transform;
    };
    Shape::Shape(const math::Transform &transform) :
      mImpl(new Impl) {
        mImpl->transform = transform;
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



  }
}
