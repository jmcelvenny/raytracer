#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Ray.h>
#include <gssmraytracer/geometry/DifferentialGeometry.h>
#include <memory>

namespace gssmraytracer {
namespace utils {
class Light {
public:
	Light ();
	
	Light (utils::Color c, float intensity);

	virtual ~Light();

	Light(const Light& copy);

	const utils::Color color() const;

	const float intensity() const;

	virtual const math::Vector getLightVector(const geometry::DifferentialGeometry &dg) const;

private:
	class Impl;
	std::shared_ptr<Impl> mImpl;
};
}
}
#endif
