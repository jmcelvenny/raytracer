#include "PointLight.h"

namespace gssmraytracer {
namespace utils {

class PointLight::Impl {
public:
	utils::Color color;
	float intensity;
	geometry::Point location;
};
	PointLight::PointLight() :  mImpl(new Impl) {
		mImpl->color = Color(255,255,255,1);
		mImpl->intensity = .5;
		mImpl->location = geometry::Point(0,10,0);
	}

	PointLight::PointLight(utils::Color c, float i, geometry::Point& loc) : mImpl(new Impl) {
		mImpl->color = c;
		mImpl->intensity = i;
		mImpl->location = loc;
	}

	PointLight::~PointLight() {}

	PointLight::PointLight(const PointLight& copy) {
		mImpl->color = copy.color();
		mImpl->intensity = copy.intensity();
		mImpl->location = copy.location();
	}

	const utils::Color PointLight::color() const {
		return mImpl->color;
	}
	
	const float PointLight::intensity() const {
		return mImpl->intensity;
	}

	const geometry::Point& PointLight::location() const {
		return mImpl->location;
	}

	const math::Vector PointLight::getLightVector(const geometry::DifferentialGeometry &dg) const {
		return math::Vector(mImpl->location.x() - dg.p.x(), mImpl->location.y() - dg.p.y(), mImpl->location.z() - dg.p.z());
	}

}}
