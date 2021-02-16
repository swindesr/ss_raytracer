/******************************************************************************/
/* Sam Swindell                                                               */
/* January 25, 2021                                                           */
/* Raytracer                                                                  */
/******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <FreeImage.h>
#include <cwchar>
#include <windows.h>
#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Scene/Scene.h"
#include "Scene/Painter.h"
#include "variables.h"
#include "filereader.h"
#include <vector>
#include "Objects/HittableList.h"
#include "Objects/Triangle.h"
#include "Math/Mat4.h"

using namespace std;

void saveScreenshot(string fname, BYTE* pixels, Config config) {
    FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, config.width, config.height, config.width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);

    std::cout << "Rendering: " << fname << "\n";

    FreeImage_Save(FIF_PNG, img, ("../testScenes/" + fname).c_str(), 0);
    delete pixels;

    std::cout << "Done rendering." << std::endl;
}

int main(int argc, char* argv[]) {
    FreeImage_Initialise();

    Config config = readfile(argv[1]);

    // Array for color data, used by FreeImage
    BYTE* pixels = new BYTE[3 * config.width * config.height];

    // Setup major players and prepare scene for rendering
    RayTracer ray_tracer = RayTracer(config.objects, config.lights, config.max_ray_depth);
    Painter painter = Painter(pixels);
    Sampler sampler = Sampler(config.width, config.height);
    Scene scene(sampler, painter, config.camera, ray_tracer);
    
    // Where the magic happens :)
    scene.render();

    saveScreenshot(config.filename, pixels, config);

    FreeImage_DeInitialise();
    return 0;
}
