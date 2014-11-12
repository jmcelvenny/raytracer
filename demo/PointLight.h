#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "Light.h"
#include <memory>

namespace gssmraytracer {
namespace utils {
class PointLight : public Light {
public:
	PointLight ();
	
	PointLight (utils::Color c, float intensity, geometry::Point& loc);

	virtual ~PointLight();

	PointLight(const PointLight& copy);

	const utils::Color color() const;

	const float intensity() const;
	
	const geometry::Point& location() const;
	
	const math::Vector getLightVector(const geometry::DifferentialGeometry &dg) const;

private:
	class Impl;
	std::shared_ptr<Impl> mImpl;
};
}}
#endif
