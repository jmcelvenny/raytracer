#include "gssmraytracer/utils/Camera.h"
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/geometry/Shape.h"

using namespace gssmraytracer::geometry;

namespace gssmraytracer {
namespace utils {

  class Camera::Impl {
  public:
    geometry::Point eye;
    math::Vector view;
    math::Vector up;
    math::Vector axis_view;
    math::Vector axis_up;
    math::Vector axis_right;
    float aspect_ratio;
    float htanfov;
    float vtanfov;
    float fov;
    float near;
    float far;

  };

Camera::Camera() : mImpl(new Impl) {
    setEyeViewUp(geometry::Point(0,0,0),
                 math::Vector(0,0,1),
                 math::Vector(0,1,0));
    setAspectRatio(16.0/9.0);
    setFOV(60.0);
}

Camera::Camera(const geometry::Point &eye,
               const math::Vector &view,
               const math::Vector &up
              ) : mImpl(new Impl) {
                setEyeViewUp(eye,
                             view,
                             up);
                setAspectRatio(16.0/9.0);
                setFOV(60.0);

}

void Camera::setEyeViewUp(const geometry::Point &eye,
                          const math::Vector &view,
                          const math::Vector &up) {
    mImpl->eye = eye;
    mImpl->axis_view = view.normalized();
    mImpl->axis_up = (up - (mImpl->axis_view * up.dot(mImpl->axis_view))).normalized();
    mImpl->axis_right = (mImpl->axis_view.cross(mImpl->axis_up)).normalized();
}

void Camera::setFOV(const float fov) {
  mImpl->fov = fov;
  mImpl->htanfov = tan(mImpl->fov * 0.5 * M_PI/180.0);
  mImpl->vtanfov = mImpl->htanfov/mImpl->aspect_ratio;
}
const geometry::Point Camera::eye() const {
  return mImpl->eye;
}
const math::Vector Camera::view(const float x, const float y) const {
  float xx = (2.0 * x - 1.0) * mImpl->htanfov;
  float yy = (2.0 * y - 1.0) * mImpl->vtanfov;

  return (math::Vector((mImpl->axis_up * yy) +
          (mImpl->axis_right * xx) +
          mImpl->axis_view).normalized());
}

void Camera::setAspectRatio(const float aspect_ratio) {
  mImpl->aspect_ratio = aspect_ratio;
  mImpl->vtanfov = mImpl->htanfov/mImpl->aspect_ratio;
}

Camera::~Camera() {

}

}
}
