#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/math/Vector.h>
#include <gssmraytracer/math/Transform.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/ProgressMeter.h>
#include <gssmraytracer/utils/CmdLineFind.h>
#include <gssmraytracer/geometry/Primitive.h>
#include <vector>
#include <memory>
#include <random>

#ifdef _OPENMP
  #include <omp.h>
#endif

#include "Sphere.h"
#include "LambertianShader.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "Light.h"


#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


#include <gssmraytracer/utils/Image.h>
#include "RenderGlobals.h"
#include <gssmraytracer/utils/Color.h>
#include <iostream>


using namespace gssmraytracer::utils;
using namespace gssmraytracer::geometry;
using namespace gssmraytracer::math;

void display_picture() {
  const Image image = RenderGlobals::getInstance().getImage();
  const float *pixmap = image.getPixelBuffer();
  glClearColor(0 , 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(image.getWidth(), image.getHeight(), GL_RGBA, GL_FLOAT, (void *)pixmap);
  glFlush();


}

void handle_key(unsigned char key, int x, int y) {
   switch(key){

        case 'q':               // q - quit
        case 'Q':
        case 27:                // esc - quit
            exit(0);

        default:                // not a valid key -- just ignore it
            return;
    }


}


int main(int argc, char* argv[]) {
    // Use the default constructor
    // Set up image
    CmdLineFind cmd(argc, argv);
    int width = cmd.find("-NX", 1280);
    int height = cmd.find("-NY", 720);
    std::string filename = cmd.find("-name", "image.exr");
    Image image(width, height);
    ProgressMeter pm(width*height, "raytracing");
    // Set up camera
    Camera camera(Point(-5,0,40),Vector(0,0,-1),Vector(0,1,0));
    camera.setAspectRatio((float)width/height);
    camera.setFOV(60.f);

    // Create transforms for spheres
    Transform transform1, transform2;



    // Set a world space position at the origin
    Vector position1(-4,3,1);
    transform1.translate(position1);

    // Set a world space position at 10,0,0
    Vector position2(10,10.0,-5);
    transform2.translate(position2);

    // Example of adding sphere to a vector of Shape*.  Can use to render multiple sphere
    // Based on depth
    Point p(0,0,10);
    std::shared_ptr<PointLight> light (new PointLight(Color(1, 0, .5, 1), 1.f, p));
    std::shared_ptr<Shader> shader(new LambertianShader(Color(0.0f,0.0f,1.0f,1)));
    std::shared_ptr<Shader> shader2(new LambertianShader(Color(1.0f, 0.0f, 0.0f, 1)));
    std::shared_ptr<Sphere> sphere1 (new Sphere(transform1, 5.0f, -10.0f, 10.0f, 360.0f, .25f));
    std::shared_ptr<Sphere> sphere2 (new Sphere(transform2, 5.0f, -10.0f, 10.0f, 360.0f, .55f));

    std::shared_ptr<Primitive> s1 (new Primitive(sphere1, shader));
    std::shared_ptr<Primitive> s2 (new Primitive(sphere2, shader2));

    Scene &scene = Scene::getInstance();
    scene.addLight(light);
    scene.addPrimitive(s1);
    scene.addPrimitive(s2);

    int samples=cmd.find("-samples", 4);
    /***********************Do Raycasting Here******************************/
    #pragma omp parallel for
    for (int r = 0; r < image.getHeight(); ++r) {
      for (int c = 0; c < image.getWidth(); ++c) {
	      pm.update();
        Color colors[samples];
        for (int s=0; s<samples; s++) {
          // Create a color
          Color color;
          float closest_thit = std::numeric_limits<float>::infinity();

          std::mt19937 mt(time(0));

          float dr = mt() / pow(2, 33);
          float dc = mt() / pow(2, 33);

          Ray ray(camera.eye(), camera.view((float)(c+dc)/image.getWidth(), (float)(r+dr)/image.getHeight()));

          float thit = std::numeric_limits<float>::infinity();
          std::shared_ptr<DifferentialGeometry> dg;
  	      std::shared_ptr<Primitive> primitive;

          if(scene.hit(ray, thit, dg, primitive)) {
            if (thit < closest_thit) {
              closest_thit = thit;
  	          color = primitive->shade(dg,0);
            }
          }
          colors[s]=color;
        }
        //calculate the average color
        float ar=0.0, ag=0.0, ab=0.0;
        for (int i = 0; i<samples; ++i) {
          ar+=colors[i].red;
          ag+=colors[i].green;
          ab+=colors[i].blue;
        }
        Color color((float)ar/samples, (float)ag/samples, (float)ab/samples, 1);
	      image.setPixel(r,c,color);
      }
    }

    /*******************End Doing Raycasting Here******************************/

    //Free the spheres
    //delete sphere1;
    //delete sphere2;
    image.write(filename.c_str());
    RenderGlobals::getInstance().setImage(image);

    // start up the glut utilities
    glutInit(&argc, argv);

    // create the graphics window, giving width, height, and title text
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);


    glutInitWindowSize(width, height);

    glutCreateWindow("Image");

    glutDisplayFunc(display_picture);

    glutKeyboardFunc(handle_key);

    glutMainLoop();


    return 0;

}
