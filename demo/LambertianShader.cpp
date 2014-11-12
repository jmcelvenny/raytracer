/*****************************************************
LambertianShader.cpp
October 27, 2014
Kacey Coley
Description:
This shader uses the lambertian shading model to determine the surface color.
The lambertian shading model is essentially a matte surface.
However, this shader is missing a proper light class in the implementation.
The lighting information has been hardcoded in.  You should implement a light
class and replace the hardcoded information with your team's implementation.

*****************************************************/
#include "LambertianShader.h"
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Scene.h>
#include "Light.h"

using namespace gssmraytracer::geometry;
namespace gssmraytracer {
  namespace utils {
    class LambertianShader::Impl {
    public:
      Color color;
    };

    LambertianShader::LambertianShader(const Color &color) : mImpl(new Impl) {
      mImpl->color = color;
    }
    LambertianShader::LambertianShader(const LambertianShader &other) :
                                            Shader(),
                                            mImpl(new Impl) {
      mImpl->color = other.mImpl->color;
    }

    LambertianShader& LambertianShader::operator=(const LambertianShader &other) {
      if (this != &other) {
        mImpl->color = other.mImpl->color;
      }
      return *this;
    }
    Color LambertianShader::shade(const geometry::DifferentialGeometry &dg) {

      // initialize the return color for the shader to black
      Color shadeColor(0,0,0,1);

      /************************************************************************/

      // no light falloff based on distance (defaulted to no falloff)
      float distanceVal_no_falloff = 1.0f;

      // linear light falloff based on distance
//     float distanceVal_linear = (light_vec.length());

      // quadratic light falloff based on distance
//      float distanceVal_quadratic = (light_vec.length() * light_vec.length());

      // ambient lighting - faking global illumination with constant
      // low color value
      shadeColor.red = mImpl->color.red * 0.1f;
      shadeColor.green = mImpl->color.green * 0.1f;
      shadeColor.blue = mImpl->color.blue * 0.1f;

      std::vector<std::shared_ptr<Light > > lights;
      lights = Scene::getInstance().lights();
      /************************************************************************/
      for (int i=0; i<lights.size(); i++) {
	      float intensity = lights[i]->intensity();
	      math::Vector light_vec = lights[i]->getLightVector(dg);
	      Ray light_ray(dg.p, light_vec.normalized());

	      // This implementation uses the singleton of the scene to see if we
	      // hit any objects.  Note that we do not need to pass in the Scene as
	      // an argument since a singleton is in the global namespace,
	      // essentially, a global class where there is only one instance)
	      if (!Scene::getInstance().hit(light_ray)) { // if no objects in the way, do lighting
		// this computes the cosine of the angle between the light vector
		// and the geometry normal
    //reflectiveness
   // if (lights[i].)
		float shadeAngle = light_vec.normalized().dot(dg.nn);
		  // if the angle is greater than 0, do the lambertian shading
		  if (shadeAngle > 0) {
		    // add the diffuse (matte) lighting to the ambient lighting based on
		    // the intensity and the falloff factor based on the distance
		    float factor = shadeAngle*intensity/distanceVal_no_falloff;
		    shadeColor.red += mImpl->color.red*factor;
		    shadeColor.green += mImpl->color.green*factor;
		    shadeColor.blue += mImpl->color.blue*factor;
		  }
	      }

      }
       return shadeColor;
    }
  }
}
