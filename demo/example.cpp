#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/math/Vector.h>
#include <gssmraytracer/math/Transform.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/CmdLineFind.h>
#include <gssmraytracer/geometry/Primitive.h>
#include <vector>
#include <memory>
#include <random>
#include <omp.h>

// Uncomment when you have the sphere implemented
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

    // Set up camera
    Camera camera(Point(-5,0,40),Vector(0,0,-1),Vector(0,1,0));
    camera.setAspectRatio((float)width/height);
    camera.setFOV(60.f);

    // Create transforms for spheres
    Transform transform1, transform2;



    // Set a world space position at the origin
    Vector position1(-1.0,0.0,0.0);
    transform1.translate(position1);

    // Set a world space position at 10,0,0
    Vector position2(11.,0.0,0.0);
    transform2.translate(position2);

    // Example of adding sphere to a vector of Shape*.  Can use to render multiple sphere
    // Based on depth
    Point p(0,10,0);
    std::shared_ptr<PointLight> light2 (new PointLight(Color(.6275, 1, .6667, 1), 1.f, p));
    //std::shared_ptr<DirectionLight> light3 (new DirectionLight(Color(.6275,1,.6667,1), 1.f, Vector(-4,-3,0)));
    //std::shared_ptr<DirectionLight> light (new DirectionLight(Color(.6275, 1, .6667,1), 1.f, Vector(4, 3, 0)));
    std::shared_ptr<Shader> shader(new LambertianShader(Color(.6275,1,.666667,1)));
    std::shared_ptr<Sphere> sphere1 (new Sphere(transform1, 5.0f, -10.0f, 10.0f, 360.0f));
    std::shared_ptr<Sphere> sphere2 (new Sphere(transform2, 5.0f, -10.0f, 10.0f, 360.0f));

    std::shared_ptr<Primitive> s1 (new Primitive(sphere1, shader));
    std::shared_ptr<Primitive> s2 (new Primitive(sphere2, shader));

    Scene &scene = Scene::getInstance();
    //scene.addLight(light);
    scene.addLight(light2);
    //scene.addLight(light3);
    scene.addPrimitive(s1);
    scene.addPrimitive(s2);


//    Sphere *sphere2 = new Sphere(transform2, 10.0f);

    /***********************Do Raycasting Here******************************/
    #pragma omp parallel for
    for (int r = 0; r < image.getHeight(); ++r) {
      for (int c = 0; c < image.getWidth(); ++c) {
        // Create a color
        Color color;

        // Uncomment when you have the sphere implemented


        // Used to determine which shape is in front
        float closest_thit = std::numeric_limits<float>::infinity();

	//SUPER DUPER SAMPLING
	// */
        Ray ray(camera.eye(), camera.view((float)(c/*+variance_x*/)/image.getWidth(), (float)(r/*+variance_y*/)/image.getHeight()));


  	// You can use a for loop to determine which shape is the closest with a hit test
          float thit = std::numeric_limits<float>::infinity();
          std::shared_ptr<DifferentialGeometry> dg;
  	      std::shared_ptr<Primitive> primitive;
  	  // If you hit the shape, compare its t value (thit) with the previously recorded one
  	  // If it is the closest, record the index value
          if(scene.hit(ray, thit, dg, primitive)) {
            if (thit < closest_thit) {
              closest_thit = thit;
  	          color = primitive->shade(dg);
            }
          }

    /*    //calculate the average color
        int ar=0, ag=0, ab=0;
        for (int i = 0; i<samples; ++i) {
          ar+=colors[i].red;
          ag+=colors[i].green;
          ab+=colors[i].blue;
        }
        float cr = ar/samples;
        float cg = ag/samples;
        float cb = ab/samples;
        image.setPixel(r, c, Color(cr, cg, cb, 1)); */
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
