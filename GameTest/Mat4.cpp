#include "stdafx.h"
#include "Mat4.h"

namespace util
{

	Mat4::Mat4(float val)
	{
		int x = 0, y = 0;
		//create identity
		while(x < 4)
			data[y++][x++] = val;

	}

	Mat4::Mat4(float val[4 * 4])
	{
		for(int y = 0; y < 4; ++y)
			for(int x = 0; x < 4; ++x)
				data[y][x] = val[y * 4 + x];
	}

	Mat4 Mat4::translate(Mat4 mat, Vec3 vec)
	{
		return translate(mat, Vec4{vec.x, vec.y, vec.z, 1});
	}

	Mat4 Mat4::translate(Mat4 mat, Vec4 vec)
	{
		Mat4 other = Mat4(1);
		other.data[0][3] = vec[0];
		other.data[1][3] = vec[1];
		other.data[2][3] = vec[2];
		other.data[3][3] = vec[3];

		return mat * other;
	}

	Mat4 Mat4::scale(Mat4 mat, Vec3 vec)
	{
		return scale(mat, Vec4{vec.x, vec.y, vec.z, 1});
	}

	Mat4 Mat4::scale(Mat4 mat, Vec4 vec)
	{
		Mat4 other = Mat4(1);
		other.data[0][0] = vec[0];
		other.data[1][1] = vec[1];
		other.data[2][2] = vec[2];
		other.data[3][3] = vec[3];
		return mat * other;
	}

	Mat4 Mat4::operator*(Mat4 other)const
	{
		Mat4 result = Mat4();
		for(int y = 0; y < 4; ++y)
			for(int x = 0; x < 4; ++x)
				//get dot product
				for(int c = 0; c < 4; ++c)
					result.data[y][x] += data[y][c] * other.data[c][x];//calculation

		return result;
	}

	Vec4 Mat4::operator*(Vec4 other)const
	{
		Vec4 result = Vec4();
		for(int c = 0; c < 4; ++c)
			result[c] += data[0][c] * other[c];

		return result;
	}

	Mat4 Mat4::operator*(float scaler)const
	{

		return *this * Mat4(scaler);
	}

	void Mat4::operator*=(Mat4 other)
	{
		*this = *this * other;
	}

	void Mat4::operator*=(float scaler)
	{
		*this = *this * Mat4(scaler);
	}
}
