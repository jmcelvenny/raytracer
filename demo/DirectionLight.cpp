#include "DirectionLight.h"

namespace gssmraytracer {
namespace utils {

class DirectionLight::Impl {
public:
	utils::Color color;
	float intensity;
	math::Vector direction;
};
	DirectionLight::DirectionLight() :  mImpl(new Impl) {
		mImpl->color = Color(255,255,255,1);
		mImpl->intensity = .5;
		mImpl->direction = math::Vector(0,-1,0);
	}

	DirectionLight::DirectionLight(utils::Color c, float i, math::Vector dir) : mImpl(new Impl) {
		mImpl->color = c;
		mImpl->intensity = i;
		mImpl->direction = dir;
	}

	DirectionLight::~DirectionLight() {}

	DirectionLight::DirectionLight(const DirectionLight& copy) {
		mImpl->color = copy.color();
		mImpl->intensity = copy.intensity();
		mImpl->direction = copy.direction();
	}

	const utils::Color DirectionLight::color() const {
		return mImpl->color;
	}
	
	const float DirectionLight::intensity() const {
		return mImpl->intensity;
	}

	const math::Vector DirectionLight::direction() const {
		return mImpl->direction;
	}

	const math::Vector DirectionLight::getLightVector(const geometry::DifferentialGeometry &dg) const {
		return math::Vector(mImpl->direction * -1);
	}

}}
