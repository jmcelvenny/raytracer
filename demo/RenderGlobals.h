#ifndef __RENDERGLOBALS_H__
#define __RENDERGLOBALS_H__

#include <memory>
#include <gssmraytracer/utils/Image.h>
namespace gssmraytracer {
  namespace utils {
    class RenderGlobals {
    public:
      static RenderGlobals& getInstance();
      void setImage(const Image& image);
      const Image& getImage();
    private:
      RenderGlobals(); // default constructor
      RenderGlobals(const RenderGlobals&); // copy constructor
      RenderGlobals& operator=(const RenderGlobals&); // assignment operator
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
#endif // __RENDERGLOBALS_H__
