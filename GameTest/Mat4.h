#pragma once
#include "Utilities.h"

namespace util
{

	class Mat4
	{
	public:
		/// <summary>
		/// create an identity matrix
		/// </summary>
		/// <param name=""></param>
		Mat4(float = 0);
		Mat4(float[4*4]);

		static Mat4 translate(Mat4, Vec3);
		static Mat4 translate(Mat4, Vec4);
		static Mat4 scale(Mat4, Vec3);
		static Mat4 scale(Mat4, Vec4);

		//Operators
		Mat4 operator*(Mat4)const;
		Vec4 operator*(Vec4)const;
		Mat4 operator*(float scaler)const;

		void operator*=(Mat4);
		void operator*=(float scaler);

	private:
		float data[4][4];
	};

}
