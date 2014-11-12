#include "Light.h"

namespace gssmraytracer {
namespace utils {

class Light::Impl {
public:
	utils::Color color;
	float intensity;
};
	Light::Light() :  mImpl(new Impl) {
		mImpl->color = Color(255,255,255,1);
		mImpl->intensity = .5;
	}

	Light::Light(utils::Color c, float i) : mImpl(new Impl) {
		mImpl->color = c;
		mImpl->intensity = i;
	}

	Light::~Light() {}

	Light::Light(const Light& copy) {
		mImpl->color = copy.color();
		mImpl->intensity = copy.intensity();
	}

	const utils::Color Light::color() const {
		return mImpl->color;
	}
	
	const float Light::intensity() const {
		return mImpl->intensity;
	}

	const math::Vector Light::getLightVector(const geometry::DifferentialGeometry &dg) const {
		return math::Vector(0,0,0);
	}
}}
