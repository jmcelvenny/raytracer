#include "gssmraytracer/math/Vector.h"
#include "gssmraytracer/geometry/Normal.h"
#include <OpenEXR/ImathVec.h>
namespace gssmraytracer {
  namespace math {
    class Vector::Impl {
    public:
      Imath::Vec3<float> vec;
    };

    Vector::Vector() : mImpl(new Impl) {}

    Vector::Vector(const float x, const float y, const float z) : mImpl(new Impl) {
      mImpl->vec.x = x;
      mImpl->vec.y = y;
      mImpl->vec.z = z;
    }
    Vector::Vector(const Vector &vec) : mImpl(new Impl) {
      mImpl->vec.x = vec.x();
      mImpl->vec.y = vec.y();
      mImpl->vec.z = vec.z();
    }
    
    bool Vector::operator!=(const Vector &other) const {
      return (mImpl->vec.x == other.x()) && (mImpl->vec.y == other.y()) && (mImpl->vec.z == other.z()); 
    }

     Vector Vector::operator+(const Vector &v) const {
      Vector newVector;
      newVector.mImpl->vec = mImpl->vec + v.mImpl->vec;
      return newVector;
    }

    Vector& Vector::operator=(const Vector &other) {
      if (this != &other) {
        mImpl->vec = other.mImpl->vec;
      }
      return *this;
    }
    std::ostream& operator<<(std::ostream &os, const Vector &vec) {
      os << "(" << vec.mImpl->vec << ")" << std::endl;
      return os;
    }
    Vector& Vector::operator+=(const Vector &other) {
      if (this != &other) {
        mImpl->vec += other.mImpl->vec;
      }
      return *this;
    }
    Vector Vector::operator-(const Vector &v) const {
      Vector newVector;
      newVector.mImpl->vec = mImpl->vec - v.mImpl->vec;
      return newVector;
    }

    Vector& Vector::operator-=(const Vector &other) {
      if (this != &other) {
        mImpl->vec -= other.mImpl->vec;
      }
      return *this;
    }
    Vector Vector::operator*(const float s) const {
      return Vector(mImpl->vec.x * s, mImpl->vec.y * s, mImpl->vec.z * s);
    }
    Vector operator*(const float s, const Vector &vec) {
      return vec * s;
    }
    Vector& Vector::operator*=(const float s) {
      mImpl->vec *= s;
      return *this;

    }
    const float Vector::operator[](const float index) const {
      return mImpl->vec[index];
    }
    Vector Vector::cross(const Vector &other) const {
      Vector newVector;
      newVector.mImpl->vec = mImpl->vec.cross(other.mImpl->vec);
      return newVector;

    }
    const float Vector::dot(const Vector &other) const {
      return mImpl->vec.dot(other.mImpl->vec);
    }

    const float Vector::dot(const geometry::Normal &other) const {
      return dot(Vector(other.x(), other.y(), other.z()));
    }

    const float Vector::length() const {return mImpl->vec.length();}
    const Vector Vector::direction() const { Imath::Vec3<float> temp = mImpl->vec;
                                              return Vector(temp.x, temp.y, temp.z);}


    const float Vector::x() const { return mImpl->vec.x;}
    void Vector::x(const float xx) { mImpl->vec.x = xx;}
    const float Vector::y() const { return mImpl->vec.y;}
    void Vector::y(const float yy) { mImpl->vec.y = yy;}
    const float Vector::z() const { return mImpl->vec.z;}
    void Vector::z(const float zz) { mImpl->vec.z = zz;}

    void Vector::normalize() { mImpl->vec.normalize();}
    const Vector Vector::normalized() const {
      Vector temp;
      temp.mImpl->vec = mImpl->vec;
      temp.mImpl->vec.normalize();
      return temp;}
  }
}
