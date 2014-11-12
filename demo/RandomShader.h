#include <gssmraytracer/utils/Shader.h>
#include <gssmraytracer/utils/Color.h>
#include <memory>
namespace gssmraytracer {
	namespace utils {
		class RandomShader: public Shader {
		public:
			RandomShader();
			RandomShader(const RandomShader &);
			RandomShader& operator=(const RandomShader &);
			Color shade(const geometry::DifferentialGeometry &dg);
		private:
			class Impl;
			std::shared_ptr<Impl> mImpl;
		};
	}
}
