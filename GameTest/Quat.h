#pragma once
//#include <glm/glm.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "Utilities.h"
#include "Mat4.h"
//#include "Matrix.h"
namespace util
{



	//complete
	struct Quat
	{
		float  x=0, y=0, z=0;

	protected:
		float w=0;

	public:
		Quat();
		Quat(float x, float y, float z);
		Quat(float w, float x, float y, float z);
		Quat(Vec3 rot);

		Vec3 getCoord();

		Quat normal();
		void normalize();

		Quat& rotation(float a_ang, float a_dirX, float a_dirY, float a_dirZ);
		Quat& rotation(float a_ang, Vec3 a_dir);

		Quat& rotation(Quat p, Quat q, Quat qc);

		void rotate(float a_ang, float a_dirX, float a_dirY, float a_dirZ);
		void rotate(float a_ang, Vec3 a_dir);

		static Mat4 quatRotationMat(float a_ang, float a_dirX, float a_dirY, float a_dirZ);
		static Mat4 quatRotationMat(float a_ang, const Vec3 a_dir);

		void print() const;

		float& operator[](int m_index)const;
		Quat operator*(Quat a_quat)	const;
		Quat operator+(Quat a_quat)const;
		void operator+=(Quat a_quat)const;
		Quat operator-(Quat a_quat)const;
		Quat operator-() const;
		void operator-=(Quat a_quat)const;

	};
}
