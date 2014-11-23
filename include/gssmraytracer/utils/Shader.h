#ifndef __SHADER_H__
#define __SHADER_H__

#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace utils {
    class Shader {
    public:
      virtual Color shade(const geometry::DifferentialGeometry &dg, int bounce) = 0;
    };
  }
}
#endif //__SHADER_H__
