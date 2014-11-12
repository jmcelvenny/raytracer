#include "RenderGlobals.h"
#include <vector>
namespace gssmraytracer {
  namespace utils {
    RenderGlobals& RenderGlobals::getInstance() {
      static RenderGlobals instance;
      return instance;
    }
    class RenderGlobals::Impl {
    public:
      Impl() : image() {}
      Image image;

    };
    RenderGlobals::RenderGlobals() : mImpl(new Impl){}


    void RenderGlobals::setImage(const Image& image) {
      mImpl->image = image;
    }

    const Image& RenderGlobals::getImage() {
      return mImpl->image;
    }


    RenderGlobals& RenderGlobals::operator=(const RenderGlobals& other) {
      if (this != &other) {
        mImpl->image = other.mImpl->image;
      }
      return *this;
    }


  }
}
