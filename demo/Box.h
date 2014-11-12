#ifndef __BOX_H__
#define __BOX_H__

#include <gssmraytracer/math/Vector.h>
#include <gssmraytracer/geometry/Point.h>
#include <gssmraytracer/utils/Ray.h>
#include <memory>

namespace gssmraytracer {
namespace utils {
class Box {
	public:
		Box(const geometry::Point &min, const geometry::Point &max);
		bool intersect(const utils::Ray &r, float t0, float t1) const;
	private:
		class Impl;
		std::shared_ptr<Impl> mImpl;
};
}
}
#endif
