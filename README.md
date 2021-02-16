
# ss_raytracer
 A raytracer built in c++

# Input file specifications
This raytracer follows the specifications for the final project of CSE167x found here:  https://courses.edx.org/courses/course-v1:UCSanDiegoX+CSE167x+2T2018/information/ 

The input file should be a sequence of lines/commands according to the following rules.  The format for a command is: 
**Command** **Arg1** **Arg2** ... **ArgN**
Where command is the command identifier and each parameter is given separated by a single space. Below, the commands are listed with names to understand parameters.

## General commands
* **Blank line** The input file can have blank lines that should be ignored.
* **#** This is a line of comments. Ignore any line starting with a #.
* **size width height:** The size command must be the first command of the file, which controls the image size.
* **maxdepth depth**: The maximum depth (number of bounces) for a ray (default should be 5).
* **output filename**: The output file to which the image should be written.

## Camera
 * **camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fovy** Specifies the camera.  The world aspect ratio (distinct from the width and height that determine image aspect ratio) is always 1; a sphere at the center of a screen will look like a circle, not an ellipse, independent of the image aspect ratio.

## Geometry
* **sphere x y z radius** Defines a sphere with a given position and radius.
* **tri v1 v2 v3** Create a triangle out of the vertices involved (which have previously been specified with the vertex command). The vertices are assumed to be specified in counter-clockwise order.

## Transformations
* **translate x y z** A translation 3-vector.
* **rotate x y z angle** Rotate by angle (in degrees) about the given axis.
* **scale x y z** Scale by the corresponding amount in each axis (a non-uniform scaling).
* **pushTransform** Push the current modeling transform on the stack.
* **popTransform** Pop the current transform from the stack. The sequence of popTransform and pushTransform can be used if desired before every primitive to reset the transformation.

## Lights
* **directional x y z r g b** The direction to the light source, and the color.
* **point x y z r g b** The location of a point source and the colo.
* **attenuation const linear quadratic** Sets the constant, linear and quadratic attenuations (default 1,0,0). 
* **ambient r g b** The global ambient color to be added for each object (default .2,.2,.2).

## Materials
* **diffuse r g b** specifies the diffuse color of the surface.
* **specular r g b** specifies the specular color of the surface.
* **shininess s** specifies the shininess of the surface.
* **emission r g b** gives the emissive color of the surface.

# Example Images
![Nice little room](https://github.com/swindesr/ss_raytracer/blob/main/scenes/scene6.png)
![Lots of balls](https://github.com/swindesr/ss_raytracer/blob/main/scenes/scene5.png)

# Further Work
There is a lot of potential improvements and missing features in this raytracer. Here is a list of things I am interested in working on:
1. Anti-aliasing via multi-sampling
2. Multithreading to improve performance
3. More shapes: cube/quad/cylinder/disc/plane/etc.
4. Monte Carlo integration
5. Acceleration via space partitioning (think octrees)
6. Transparency
7. Double-sided primitives

Lots more, but those are some achievable options in my current skill range.
