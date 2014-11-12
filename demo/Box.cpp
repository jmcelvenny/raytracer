#include "Box.h"

namespace gssmraytracer {
	namespace utils {
		class Box::Impl {
		public:
			geometry::Point bounds[2];
		};
		Box::Box(const geometry::Point &min, const geometry::Point &max) : mImpl(new Impl()){
	//		assert(min < max);
			mImpl->bounds[0] = min;
			mImpl->bounds[1] = max;
		}
		bool Box::intersect(const Ray &r, float t0, float t1) const {
			float tmin, tmax, tymin, tymax, tzmin, tzmax;
			if (r.dir().x() >=0) {
				tmin = (mImpl->bounds[0].x() - r.origin().x()) / r.dir().x();
				tmax = (mImpl->bounds[1].x() - r.origin().x()) / r.dir().x();
			} else {
				tmin = (mImpl->bounds[1].x() - r.origin().x()) / r.dir().x();
				tmax = (mImpl->bounds[0].x() - r.origin().x()) / r.dir().x();
			}
			if (r.dir().y() >=0) {
                                tymin = (mImpl->bounds[0].y() - r.origin().y()) / r.dir().y();
                                tymax = (mImpl->bounds[1].y() - r.origin().y()) / r.dir().y();
                        } else {
                                tymin = (mImpl->bounds[1].y() - r.origin().y()) / r.dir().y();
                                tymax = (mImpl->bounds[0].y() - r.origin().y()) / r.dir().y();
                        }
			if ((tmin > tymax) || (tymin > tmax)) {
				return false;
			}
			if (tymin > tmin)
 			   tmin = tymin;
			if (tymax < tmax)
 	 		   tmax = tymax;
			if (r.dir().z() >= 0) {
			   tzmin = (mImpl->bounds[0].z() - r.origin().z()) / r.dir().z();
			   tzmax = (mImpl->bounds[1].z() - r.origin().z()) / r.dir().z();
			} else {
			   tzmin = (mImpl->bounds[1].z() - r.origin().z()) / r.dir().z();
			   tzmax = (mImpl->bounds[0].z() - r.origin().z()) / r.dir().z();
			}
			if ( (tmin > tzmax) || (tzmin > tmax))
			   return false;
			if (tzmin > tmin)
			   tmin = tzmin;
			if (tzmax < tmax )
			   tmax = tzmax;
			return ( (tmin < t1) && (tmax > t0));
		}
	}
}
