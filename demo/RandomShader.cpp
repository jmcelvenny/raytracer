#include "RandomShader.h"
#include <gssmraytracer/utils/Color.h>

using namespace gssmraytracer::geometry;
namespace gssmraytracer {
  namespace utils {
    class RandomShader::Impl {
    public:
      Color color;
    };

    RandomShader::RandomShader() : mImpl(new Impl) {}
	
    RandomShader::RandomShader(const RandomShader &other) : Shader(), mImpl(new Impl) {}
    RandomShader& RandomShader::operator=(const RandomShader &other) {
      return *this;
    }
    Color RandomShader::shade(const geometry::DifferentialGeometry &dg) {
	  if ((int)floor(dg.v*1000 )%100 >= 60) {
		return Color(255,255,255,1);
	  } else {
		return Color(255,0,0,1);
	  }
    }
  }
}
