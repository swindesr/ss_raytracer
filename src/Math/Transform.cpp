#include "Transform.h"
#include "variables.h"

Mat3 Transform::rotate(const float degrees, const Vec3& axis)
{
    float theta = degreesToRadians(degrees);
    float x = axis.x, y = axis.y, z = axis.z;
    Mat3 I(1.0);
    Mat3 aat = Mat3(x * x, x * y, x * z,
                    y * x, y * y, y * z, 
                    z * x, z * y, z * z);
    Mat3 a_star = Mat3(0.0,  -z,   y,
                         z, 0.0,  -x,
                        -y,   x, 0.0);
    Mat3 r = Mat3(cos(theta) * I + (1 - cos(theta)) * aat + sin(theta) * a_star);
    return r;
}

Mat4 Transform::scale(const float& sx, const float& sy, const float& sz)
{
    Mat4 scale(
          sx, 0.0f, 0.0f, 0.0f,
        0.0f,   sy, 0.0f, 0.0f,
        0.0f, 0.0f,   sz, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );

    return scale;
}

Mat4 Transform::translate(const float& tx, const float& ty, const float& tz)
{
    Mat4 translate(
        1.0f, 0.0f, 0.0f, tx,
        0.0f, 1.0f, 0.0f, ty,
        0.0f, 0.0f, 1.0f, tz,
        0.0f, 0.0f, 0.0f, 1.0f
        );

    return translate;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
