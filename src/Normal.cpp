#include "gssmraytracer/geometry/Normal.h"
#include <OpenEXR/ImathVec.h>

namespace gssmraytracer {
  namespace geometry {
    class Normal::Impl {
    public:
      Imath::Vec3<float> vec;

    };

    Normal::Normal(const math::Vector &vec) : mImpl(new Impl) {
      mImpl->vec.x = vec.x();
      mImpl->vec.y = vec.y();
      mImpl->vec.z = vec.z();
    }
    Normal::Normal(const float x, const float y, const float z): mImpl(new Impl) {
      mImpl->vec.x = x;
      mImpl->vec.y = y;
      mImpl->vec.z = z;
    }
    Normal::Normal(const Normal &normal) : mImpl(new Impl) {
      mImpl->vec = normal.mImpl->vec;
    }

    Normal& Normal::operator=(const Normal &normal)  {
      if (this != &normal) {
        mImpl->vec = normal.mImpl->vec;
      }
      return *this;
    }
    void Normal::normalize() { mImpl->vec.normalize();}

    const Normal Normal::normalized() const {
      Normal new_normal = *this;
      new_normal.normalize();
      return new_normal;

    }

    const float Normal::x() const { return mImpl->vec.x;}
    const float Normal::y() const { return mImpl->vec.y;}
    const float Normal::z() const { return mImpl->vec.z;}

    std::ostream& operator<<(std::ostream &os, const Normal &normal) {
      os << "(" << normal.x() << ", " << normal.y() << ", " << normal.z() << ")" << std::endl;
      return os;
    }

  }


}
