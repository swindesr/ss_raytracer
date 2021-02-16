#include "Mat4.h"

Mat4::Mat4(float aa, float ab, float ac, float ad, 
		   float ba, float bb, float bc, float bd, 
		   float ca, float cb, float cc, float cd, 
		   float da, float db, float dc, float dd)
{
	x[0] = aa;
	x[1] = ab;
	x[2] = ac;
	x[3] = ad;
	y[0] = ba;
	y[1] = bb;
	y[2] = bc;
	y[3] = bd;
	z[0] = ca;
	z[1] = cb;
	z[2] = cc;
	z[3] = cd;
	w[0] = da;
	w[1] = db;
	w[2] = dc;
	w[3] = dd;
}

Mat4::Mat4(float n)
{
	x[0] = n;
	x[1] = 0;
	x[2] = 0;
	x[3] = 0;
	y[0] = 0;
	y[1] = n;
	y[2] = 0;
	y[3] = 0;
	z[0] = 0;
	z[1] = 0;
	z[2] = n;
	z[3] = 0;
	w[0] = 0;
	w[1] = 0;
	w[2] = 0;
	w[3] = n;
}

Mat4::Mat4(const Mat3& m)
{
	x[0] = m.x[0];
	x[1] = m.x[1];
	x[2] = m.x[2];
	x[3] = 0;
	y[0] =  m.y[0];
	y[1] =  m.y[1];
	y[2] =  m.y[2];
	y[3] = 0;
	z[0] = m.z[0];
	z[1] = m.z[1];
	z[2] = m.z[2];
	z[3] = 0;
	w[0] = 0;
	w[1] = 0;
	w[2] = 0;
	w[3] = 1.0f;
}

Mat4::Mat4()
{
	x[0] = 0;
	x[1] = 0;
	x[2] = 0;
	x[3] = 0;
	y[0] = 0;
	y[1] = 0;
	y[2] = 0;
	y[3] = 0;
	z[0] = 0;
	z[1] = 0;
	z[2] = 0;
	z[3] = 0;
	w[0] = 0;
	w[1] = 0;
	w[2] = 0;
	w[3] = 0;
}

Mat4 Mat4::operator*(const Mat4& other) const
{
	float a[4][4];
	float b[4][4];
	float res[4][4];
	
	for (int i = 0; i < 4; i++) {
		a[0][i] = x[i];
		a[1][i] = y[i];
		a[2][i] = z[i];
		a[3][i] = w[i];
		b[0][i] = other.x[i];
		b[1][i] = other.y[i];
		b[2][i] = other.z[i];
		b[3][i] = other.w[i];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	return Mat4(res[0][0], res[0][1], res[0][2], res[0][3],
				res[1][0], res[1][1], res[1][2], res[1][3],
				res[2][0], res[2][1], res[2][2], res[2][3],
				res[3][0], res[3][1], res[3][2], res[3][3]);
}

Mat4 Mat4::transpose() const
{
	return Mat4(x[0], y[0], z[0], w[0],
				x[1], y[1], z[1], w[1],
				x[2], y[2], z[2], w[2],
				x[3], y[3], z[3], w[3]);
}

Mat4 Mat4::inverse() const
{
	float A2323 = z[2] * w[3] - z[3] * w[2];
	float A1323 = z[1] * w[3] - z[3] * w[1];
	float A1223 = z[1] * w[2] - z[2] * w[1];
	float A0323 = z[0] * w[3] - z[3] * w[0];
	float A0223 = z[0] * w[2] - z[2] * w[0];
	float A0123 = z[0] * w[1] - z[1] * w[0];
	float A2313 = y[2] * w[3] - y[3] * w[2];
	float A1313 = y[1] * w[3] - y[3] * w[1];
	float A1213 = y[1] * w[2] - y[2] * w[1];
	float A2312 = y[2] * z[3] - y[3] * z[2];
	float A1312 = y[1] * z[3] - y[3] * z[1];
	float A1212 = y[1] * z[2] - y[2] * z[1];
	float A0313 = y[0] * w[3] - y[3] * w[0];
	float A0213 = y[0] * w[2] - y[2] * w[0];
	float A0312 = y[0] * z[3] - y[3] * z[0];
	float A0212 = y[0] * z[2] - y[2] * z[0];
	float A0113 = y[0] * w[1] - y[1] * w[0];
	float A0112 = y[0] * z[1] - y[1] * z[0];

	float det = x[0] * (y[1] * A2323 - y[2] * A1323 + y[3] * A1223)
		- x[1] * (y[0] * A2323 - y[2] * A0323 + y[3] * A0223)
		+ x[2] * (y[0] * A1323 - y[1] * A0323 + y[3] * A0123)
		- x[3] * (y[0] * A1223 - y[1] * A0223 + y[2] * A0123);
	det = 1 / det;

	return Mat4(
	   det * (y[1] * A2323 - y[2] * A1323 + y[3] * A1223),
	   det * -(x[1] * A2323 - x[2] * A1323 + x[3] * A1223),
	   det * (x[1] * A2313 - x[2] * A1313 + x[3] * A1213),
	   det * -(x[1] * A2312 - x[2] * A1312 + x[3] * A1212),
	   det * -(y[0] * A2323 - y[2] * A0323 + y[3] * A0223),
	   det * (x[0] * A2323 - x[2] * A0323 + x[3] * A0223),
	   det * -(x[0] * A2313 - x[2] * A0313 + x[3] * A0213),
	   det * (x[0] * A2312 - x[2] * A0312 + x[3] * A0212),
	   det * (y[0] * A1323 - y[1] * A0323 + y[3] * A0123),
	   det * -(x[0] * A1323 - x[1] * A0323 + x[3] * A0123),
	   det * (x[0] * A1313 - x[1] * A0313 + x[3] * A0113),
	   det * -(x[0] * A1312 - x[1] * A0312 + x[3] * A0112),
	   det * -(y[0] * A1223 - y[1] * A0223 + y[2] * A0123),
	   det * (x[0] * A1223 - x[1] * A0223 + x[2] * A0123),
	   det * -(x[0] * A1213 - x[1] * A0213 + x[2] * A0113),
	   det * (x[0] * A1212 - x[1] * A0212 + x[2] * A0112));
}
