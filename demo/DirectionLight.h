#ifndef __DIRECTIONLIGHT_H__
#define __DIRECTIONLIGHT_H__

#include "Light.h"
#include <memory>

namespace gssmraytracer {
namespace utils {
class DirectionLight : public Light {
public:
	DirectionLight ();
	
	DirectionLight (utils::Color c, float intensity, math::Vector dir);

	virtual ~DirectionLight();

	DirectionLight(const DirectionLight& copy);

	const utils::Color color() const;

	const float intensity() const;
	
	const math::Vector direction() const;

	const math::Vector getLightVector(const geometry::DifferentialGeometry &dg) const;
	
private:
	class Impl;
	std::shared_ptr<Impl> mImpl;
};
}}
#endif
