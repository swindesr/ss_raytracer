#pragma once
#include "filereader.h"
#include <fstream>
#include <stack>
#include "Objects/Sphere.h"
#include "Math/Transform.h"
#include "Objects/Triangle.h"

// Load vals into input array and handle bad values
bool readvals(std::stringstream& s, const int numvals, float* values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            std::cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

Config readfile(const char* filename)
{
    Config config;
    std::string str, cmd;
    std::ifstream in;

    std::stack <Mat4> transform_stack;
    transform_stack.push(Mat4(1.0));

    in.open(filename);
    if (in.is_open()) {
        getline(in, str);
        while (in) {
            // Ignore comments / blanks
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
                std::stringstream s(str);
                s >> cmd;
                int i;

                // Array to process command argumnets
                float values[10]; 
                bool is_valid_input; 

                // Output image dimensions
                if (cmd == "size") {
                    is_valid_input = readvals(s, 2, values);
                    if (is_valid_input) {
                        config.width = (int)values[0];
                        config.height = (int)values[1];
                    }
                }

                // Output file name
                else if (cmd == "output") {
                    s >> config.filename;
                }

                // Ray max depth
                else if (cmd == "maxdepth") {
                    is_valid_input = readvals(s, 1, values);
                    if (is_valid_input) {
                        config.max_ray_depth = (int)values[0];
                    }
                }

                // Camera 
                else if (cmd == "camera") {
                    is_valid_input = readvals(s, 10, values);
                    if (is_valid_input) {
                        Vec3 eye(values[0], values[1], values[2]);
                        Vec3 at(values[3], values[4], values[5]);
                        Vec3 up(values[6], values[7], values[8]);
                        float fovy = values[9];
                        float aspect = static_cast<float>(config.width) / static_cast<float>(config.height);

                        config.camera = Camera(eye, at, up, fovy, aspect);
                    }
                }

                // Lights
                else if (cmd == "directional" || cmd == "point") {
                    is_valid_input = readvals(s, 6, values);
                    if (is_valid_input) {
                        Vec3 pos(values[0], values[1], values[2]);
                        Color col(values[3], values[4], values[5]);
                        char type = cmd.at(0);

                        Light l(pos, col, type);
                        l.attenuation = config.attenuation;

                        config.lights.push_back(l);
                    }
                }

                // Light attenuation
                else if (cmd == "attenuation") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        config.attenuation.constant = values[0];
                        config.attenuation.linear = values[1];
                        config.attenuation.quad = values[2];
                    }
                }

                // Ambient lighting (unique per object)
                else if (cmd == "ambient") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        config.mat.ambient = Color(values[0], values[1], values[2]);
                    }
                }

                // Material diffuse property
                else if (cmd == "diffuse") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        for (i = 0; i < 4; i++) {
                            config.mat.diffuse = Color(values[0], values[1], values[2]);
                        }
                    }
                }

                // Material specular property
                else if (cmd == "specular") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        for (i = 0; i < 4; i++) {
                            config.mat.specular = Color(values[0], values[1], values[2]);
                        }
                    }
                }

                // Material emissive property
                else if (cmd == "emission") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        config.mat.emission = Color(values[0], values[1], values[2]);
                    }
                }

                // Material shininess property
                else if (cmd == "shininess") {
                    is_valid_input = readvals(s, 1, values);
                    if (is_valid_input) {
                        config.mat.shininess = values[0];
                    }
                }

                // Don't need, but spec includes it
                else if (cmd == "maxverts") {
                    // Nothing
                }

                // Vertex for defining objects
                else if (cmd == "vertex") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        Vec3 v(values[0], values[1], values[2]);
                        config.vertices.push_back(v);
                    }
                }

                // Triangle object
                else if (cmd == "tri") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        Vec3 a = config.vertices[(int)values[0]];
                        Vec3 b = config.vertices[(int)values[1]];
                        Vec3 c = config.vertices[(int)values[2]];

                        auto t = make_shared<Triangle>(a, b, c, Material(config.mat));
                        t->transform = transform_stack.top();
                        t->inverse_transform = transform_stack.top().inverse();
                        t->normal_transform = Mat3(transform_stack.top()).inverse().transpose();

                        config.objects.add(t);
                    }
                }

                // Sphere object
                else if (cmd == "sphere") {
                    is_valid_input = readvals(s, 4, values);
                    if (is_valid_input) {
                        Vec3 pos(values[0], values[1], values[2]);

                        auto s = make_shared<Sphere>(values[3], pos, Material(config.mat));
                        s->transform = transform_stack.top();
                        s->inverse_transform = transform_stack.top().inverse();
                        s->normal_transform = Mat3(transform_stack.top()).inverse().transpose();

                        config.objects.add(s);
                    }
                }

                // Translate transform
                else if (cmd == "translate") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        Mat4 m = Transform::translate(values[0], values[1], values[2]);
                        Mat4& t = transform_stack.top();
                        t = t * m;
                    }
                }

                // Scale transform 
                else if (cmd == "scale") {
                    is_valid_input = readvals(s, 3, values);
                    if (is_valid_input) {
                        Mat4 m = Transform::scale(values[0], values[1], values[2]);
                        Mat4& t = transform_stack.top();
                        t = t * m;
                    }
                }

                // Rotate transform
                else if (cmd == "rotate") {
                    is_valid_input = readvals(s, 4, values);
                    if (is_valid_input) {
                        Vec3 axis(values[0], values[1], values[2]);
                        Mat3 r = Transform::rotate(values[3], axis.normalize());
                        Mat4 m(r);
                        Mat4& t = transform_stack.top();
                        t = t * m;
                    }
                }

                // Push transform onto stack
                else if (cmd == "pushTransform") {
                    transform_stack.push(transform_stack.top());
                }

                // Pop transform from stack
                else if (cmd == "popTransform") {
                    if (transform_stack.size() <= 1) {
                        std::cerr << "Stack has no elements.  Cannot Pop\n";
                    }
                    else {
                        transform_stack.pop();
                    }
                }

                // Error
                else {
                    std::cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }
    }
    else {
        std::cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }

    return config;
}
