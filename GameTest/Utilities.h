#pragma once
//#define clamp(val, min, max) (val > max ? max : val < min ? min : val)
//#include <GL/glew.h>
//#include <glm/common.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <memory>
#include <cassert>

namespace util
{
#define reclass(a_class,a_val) (*(a_class*)&(a_val))
	typedef const char* cstring;
	typedef unsigned int   uint;
	typedef unsigned long  ulong;
	typedef unsigned short ushort;
	typedef unsigned char  uchar;
	typedef unsigned char  ubyte;

	//removes any '\\' and replaces them with '/' (also removes redundancies). 
	static cstring cDir(char* dir)
	{
		char* tmp;
		if(strlen(dir) > 0)
			while(bool(tmp = strchr(dir, '\\')))
			{
				tmp[0] = '/';
			}

		if(strlen(dir) > 1)
			while(bool(tmp = strstr(dir, "//")))
			{
				memmove_s(tmp, strlen(tmp), tmp + 1, strlen(tmp + 1));
				dir[strlen(dir) - 1] = 0;
			}

		return dir;
	}

	static std::string tolower(char* dir)
	{
		std::string tmp;
		for(unsigned i = 0; i < strlen(dir); i++)
		{
			tmp += (char)std::tolower(*(dir + i));
		}
		return tmp;
	}

	/// <summary>
	/// Creates a Bezier curve
	/// </summary>
	/// <typeparam name="T">cool</typeparam>
	/// <param name="p0: ">Start point</param>
	/// <param name="t0: ">Control Start</param>
	/// <param name="t1: ">Control End</param>
	/// <param name="p1: ">End point</param>
	/// <param name="t: ">Scaler</param>
	/// <returns></returns>
	template <typename T>
	static inline T bezier(const T& p0, const T& t0, const T& t1, const T& p1, const float t)
	{
		return
			t * t * t * (-p0 + 3.0f * t0 - 3.0f * t1 + p1) +
			t * t * (3.0f * p0 - 6.0f * t0 + 3.0f * t1) +
			t * (-3.0f * p0 + 3.0f * t0) +
			p0;
	}

	/// <summary>
	/// Creates a catmull curve
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="p0: ">Start point</param>
	/// <param name="p1: ">End Point</param>
	/// <param name="p2: ">Control Start</param>
	/// <param name="p3: ">Control End</param>
	/// <param name="t: ">Scaler</param>
	/// <returns></returns>
	template <typename T>
	static inline T catmull(T p0, T p1, T p2, T p3, float t)
	{
		return 0.5f *
			t * t * t * (-p0 + p1 * 3.0f + p2 * -3.0f + p3) +
			t * t * (p0 * 2.0f + p1 * -5.0f + p2 * 4.0f - p3) +
			t * (-p0 + p2) +
			(2.0f * p1);

		//return p0;
	}

	template<typename T>
	static inline T lerp(const T& v0, const T& v1, const float& t)
	{
		return (T)((1.0f - t) * v0 + (t)*v1);
	}

	template<typename T>
	static inline T clamp(T mini, T maxi, T val) { return std::max(mini, std::min(maxi, val)); }

	//?
	static inline int vectorWrap(int num, int mod) { return (num + mod) % mod; }


	template<class T = float>
	struct Coord2D
	{

		union
		{
			struct { T x, y; };
			struct { T u, v; };
			struct { T w, h; };
			struct { T width, height; };
		};

		Coord2D() = default;
		Coord2D(T a_x, T a_y)
		{
			x = a_x, y = a_y;
		}

		T length()
		{
			return sqrtf(x * x + y * y);
		}
		static T distance(Coord2D v1, Coord2D v2)
		{
			Coord2D v3 = v2 - v1;
			return sqrtf(v3.x * v3.x + v3.y * v3.y);
		}

		T distanceSquare()
		{
			return (x * x + y * y);
		}

		Coord2D normal()
		{
			return *this / length();
		}

		T& operator[] (int index)
		{
			assert(index < 2 && index >= 0);//cant be accessing unknown memory

			return *(((T*)this) + index);
		}

		Coord2D operator+(Coord2D coord)
		{
			return {x + coord.x, y + coord.y};
		}
		Coord2D operator+(T coord)
		{
			return {x + coord, y + coord};
		}

		template<class Y>
		Coord2D operator+(Coord2D<Y> coord)
		{
			return {x + (T)coord.x, y + (T)coord.y};
		}
		template<class Y>
		Coord2D operator+(Y coord)
		{
			return {x + (T)coord, y + (T)coord};
		}

		Coord2D operator-(Coord2D coord)
		{
			return {x - coord.x, y - coord.y};
		}
		Coord2D operator-(T coord)
		{
			return {x - coord, y - coord};
		}

		template<class Y>
		Coord2D operator-(Coord2D<Y> coord)
		{
			return {x - (T)coord.x, y - (T)coord.y};
		}
		template<class Y>
		Coord2D operator-(Y coord)
		{
			return {x - (T)coord, y - (T)coord};
		}

		Coord2D operator/(Coord2D coord)
		{
			return {x / coord.x, y / coord.y};
		}
		Coord2D operator/(T coord)
		{
			return {x / coord, y / coord};
		}
		void operator-=(Coord2D coord)
		{
			x -= coord.x;
			y -= coord.y;
		}
		void operator+=(Coord2D coord)
		{
			x += coord.x;
			y += coord.y;
		}
		void operator/=(Coord2D coord)
		{
			x /= coord.x, y /= coord.y;
		}
		void operator/=(T coord)
		{
			x /= coord, y /= coord;
		}


		bool operator==(Coord2D<T> coord)const
		{
			return
				x == coord.x &&
				y == coord.y;
		}

		bool operator!=(Coord2D<T> coord)const
		{
			return !(*this == coord);
		}

		//based on distance
		bool operator>(Coord2D<T> coord)
		{
			return this->distanceSquare() > coord.distanceSquare();
		}
		//based on distance
		bool operator<=(Coord2D<T> coord)const
		{
			return !(*this > coord);
		}
		//based on distance
		bool operator<(Coord2D<T> coord)
		{
			return distanceSquare() < coord.distanceSquare();
		}
		//based on distance
		bool operator>=(Coord2D<T> coord)const
		{
			return !(*this < coord);
		}
	};



	template<class T = float>
	struct Coord3D
	{
		union
		{
			struct { T x, y, z; };
			struct { T w, h, d; };
			struct { T r, g, b; };
			struct { T width, height, depth; };
		};


		Coord3D() :x(0), y(0), z(0) {};

		Coord3D(Coord2D<T> coord)
		{
			x = coord.x;
			y = coord.y;
			z = 0;
		}
		template<class P = float>
		Coord3D(const Coord2D<P> coord)
		{
			x = (T)coord.x;
			y = (T)coord.y;
			z = (T)0;
		}

		void operator=(Coord2D<T> coord)
		{
			x = coord.x;
			y = coord.y;
		}

		Coord3D(Coord2D<T> coord, T last)
		{
			x = coord.x;
			y = coord.y;
			z = last;
		}

		Coord3D(T scale)
		{
			this->x = scale;
			this->y = scale;
			this->z = scale;
		}

		Coord3D(T m_x, T m_y, T m_z)
		{
			this->x = m_x;
			this->y = m_y;
			this->z = m_z;
		}

		Coord3D(T m_x, T m_y)
		{
			this->x = m_x;
			this->y = m_y;
			this->z = 0;
		}


		static T distance(Coord3D<T> v1, Coord3D<T> v2)
		{
			v1 -= v2;
			return v1.length();
		}

		T length()
		{
			return (T)sqrtf(x * x + y * y + z * z);
		}

		T distanceSquare()
		{
			return (x * x + y * y + z * z);
		}

		static T dotProduct(Coord3D<T> a, Coord3D<T> b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		static Coord3D<T> crossProduct(Coord3D<T> a, Coord3D<T> b)
		{
			return
			{
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			};
		}
		Coord3D<T> crossProduct(Coord3D<T> b)
		{
			return
			{
				y * b.z - z * b.y,
				z * b.x - x * b.z,
				x * b.y - y * b.x
			};
		}

		friend static Coord3D<T> abs(Coord3D<T> val)
		{
			return {sqrtf(val.x * val.x), sqrtf(val.y * val.y), sqrtf(val.z * val.z)};
		}


		Coord3D<T> normal()
		{
			return *this / length();
		}


		void set(Coord2D<T> coord)
		{
			x = coord.x;
			y = coord.y;
		}

		void set(T m_x, T m_y, T m_z)
		{
			this->x = m_x;
			this->y = m_y;
			this->z = m_z;
		}

		void set(T m_x, T m_y)
		{
			this->x = m_x;
			this->y = m_y;
		}

		void normalize()
		{
			T norm = sqrtf(x * x + y * y + z * z);
			x /= norm;
			y /= norm;
			z /= norm;
		}

		T& operator[] (int index)
		{
			assert(index < 3 && index >= 0);//cant be accessing unknown memory

			return *(((T*)this) + index);
		}

		Coord3D<T> operator+(Coord3D<T> coord)const
		{
			return {T(x + coord.x), T(y + coord.y), T(z + coord.z)};
		}

		Coord3D<T> operator-(Coord3D<T> coord)const
		{
			return {T(x - coord.x), T(y - coord.y), T(z - coord.z)};
		}

		friend Coord3D<T> operator-(T val, const Coord3D<T> coord)
		{
			return {T(val - coord.x), T(val - coord.y), T(val - coord.z)};
		}

		friend Coord3D<T> operator*(T scaler, const Coord3D<T> coord)
		{
			return {scaler * coord.x, scaler * coord.y, scaler * coord.z};
		}

		Coord3D<T> operator*(Coord3D<T> coord)const
		{
			return {x * coord.x, y * coord.y, z * coord.z};
		}

		Coord3D<T> operator*(T coord)const
		{
			return {x * coord, y * coord, z * coord};
		}

		Coord3D<T> operator/(Coord3D<T> coord)const
		{
			return {x / coord.x, y / coord.y, z / coord.z};
		}

		Coord3D<T> operator/(T coord)const
		{
			return {x / coord, y / coord, z / coord};
		}
		Coord3D<T> operator%(Coord3D<T> coord)const
		{
			return	{
				(T)coord.x ? std::fmodf(x, coord.x) : 0,
				(T)coord.y ? std::fmodf(y, coord.y) : 0,
				(T)coord.z ? std::fmodf(z, coord.z) : 0
			};
		}

		Coord3D<T> operator%(T coord)const
		{
			return {
				(T)coord ? std::fmodf(x, coord) : 0,
				(T)coord ? std::fmodf(y, coord) : 0,
				(T)coord ? std::fmodf(z, coord) : 0
			};
		}

		Coord3D<T> operator-()const
		{

			return *this * -1;
		}

		void operator-=(Coord3D<T> coord)
		{
			x -= coord.x;
			y -= coord.y;
			z -= coord.z;
		}

		void operator+=(Coord3D<T> coord)
		{
			x += coord.x;
			y += coord.y;
			z += coord.z;
		}

		void operator*=(Coord3D<T> coord)
		{
			x *= coord.x;
			y *= coord.y;
			z *= coord.z;
		}

		void operator*=(T val)
		{
			x *= val;
			y *= val;
			z *= val;
		}

		void operator/=(T val)
		{
			x /= val;
			y /= val;
			z /= val;
		}


		bool operator==(Coord3D<T> coord)const
		{
			return
				x == coord.x &&
				y == coord.y &&
				z == coord.z;
		}

		bool operator!=(Coord3D<T> coord)const
		{
			return !(*this == coord);
		}

		//based on distance
		bool operator>(Coord3D<T> coord)
		{
			return this->distanceSquare() > coord.distanceSquare();
		}
		//based on distance
		bool operator<=(Coord3D<T> coord)const
		{
			return !(*this > coord);
		}
		//based on distance
		bool operator<(Coord3D<T> coord)
		{
			return distanceSquare() < coord.distanceSquare();
		}
		//based on distance
		bool operator>=(Coord3D<T> coord)const
		{
			return !(*this < coord);
		}

		cstring toString()
		{
			static char toStr[60]{};
			sprintf_s(toStr, "(%f, %f, %f)", x, y, z);
			return toStr;
		}
	private:

	};

	template<class T = float>
	struct Coord4D
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T width, height, depth, scale; };
		};


		Coord4D() :x(0), y(0), z(0), w(0) {};

		Coord4D(Coord2D<T> coord)
		{
			x = coord.x;
			y = coord.y;
			z = 0;
			w = 0;
		}

		template<class P = float>
		Coord4D(const Coord3D<P> coord)
		{
			x = (T)coord.x;
			y = (T)coord.y;
			z = (T)coord.z;
			w = (T)0;
		}

		Coord4D(Coord3D<T> coord, T last)
		{
			x = coord.x;
			y = coord.y;
			z = coord.z;
			w = last;
		}

		Coord4D(T scale)
		{
			this->x = scale;
			this->y = scale;
			this->z = scale;
			this->w = scale;
		}
		Coord4D(T a_x, T a_y, T a_z, T a_w)
		{


			this->x = a_x;
			this->y = a_y;
			this->z = a_z;
			this->w = a_w;

		}
		Coord4D(T a_x, T a_y, T a_z)
		{
			this->x = a_x;
			this->y = a_y;
			this->z = a_z;
			w = 0;
		}
		Coord4D(T a_x, T a_y)
		{
			this->x = a_x;
			this->y = a_y;
			this->z = 0;
			w = 0;
		}

		static T distance(Coord4D<T> v1, Coord4D<T> v2)
		{
			v1 -= v2;
			return v1.length();
		}

		T length()
		{
			return (T)sqrtf(distanceSquare());
		}

		T distanceSquare()
		{
			return (x * x + y * y + z * z + w * w);
		}

		static T dotProduct(Coord4D<T> a, Coord4D<T> b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		static Coord4D<T> crossProduct(Coord4D<T> a, Coord4D<T> b)
		{
			return
			{
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			};
		}
		Coord4D<T> crossProduct(Coord4D<T> b)
		{
			return crossProduct(*this, b);
		}


		friend static Coord4D<T> abs(Coord4D<T> val)
		{
			return {sqrtf(val.x * val.x), sqrtf(val.y * val.y), sqrtf(val.z * val.z), sqrtf(val.w * val.w)};
		}


		Coord4D<T> normal()
		{
			return *this / length();
		}


		void set(Coord2D<T> coord)
		{
			x = coord.x;
			y = coord.y;
		}

		void set(T a_x, T a_y, T a_z, T a_w)
		{
			this->x = a_x;
			this->y = a_y;
			this->z = a_z;
			this->w = a_w;
		}
		void set(T a_x, T a_y, T a_z)
		{
			this->x = a_x;
			this->y = a_y;
			this->z = a_z;
		}

		void set(T a_x, T a_y)
		{
			this->x = a_x;
			this->y = a_y;
		}

		void normalize()
		{
			T norm = sqrtf(x * x + y * y + z * z);
			x /= norm;
			y /= norm;
			z /= norm;
		}

		T& operator[] (int index)
		{
			assert(index < 4 && index >= 0);//cant be accessing unknown memory

			return *(((T*)this) + index);
		}

		Coord4D<T> operator+(Coord4D<T> coord)const
		{
			return {T(x + coord.x), T(y + coord.y), T(z + coord.z), T(w + coord.w)};
		}

		Coord4D<T> operator-(Coord4D<T> coord)const
		{
			return {T(x - coord.x), T(y - coord.y), T(z - coord.z), T(w - coord.w)};
		}

		friend Coord4D<T> operator-(T val, const Coord4D<T> coord)
		{
			return {T(val - coord.x), T(val - coord.y), T(val - coord.z), T(val - coord.w)};
		}

		friend Coord4D<T> operator*(T scaler, const Coord4D<T> coord)
		{
			return {scaler * coord.x, scaler * coord.y, scaler * coord.z, scaler * coord.w};
		}

		Coord4D<T> operator*(Coord4D<T> coord)const
		{
			return {x * coord.x, y * coord.y, z * coord.z, w * coord.w};
		}

		Coord4D<T> operator*(T coord)const
		{
			return {x * coord, y * coord, z * coord, w * coord};
		}

		Coord4D<T> operator/(Coord4D<T> coord)const
		{
			return {x / coord.x, y / coord.y, z / coord.z, w / coord.w};
		}

		Coord4D<T> operator/(T coord)const
		{
			return {x / coord, y / coord, z / coord, w / coord};
		}
		Coord4D<T> operator%(Coord4D<T> coord)const
		{
			return	{
				(T)coord.x ? std::fmodf(x, coord.x) : 0,
				(T)coord.y ? std::fmodf(y, coord.y) : 0,
				(T)coord.z ? std::fmodf(z, coord.z) : 0,
				(T)coord.w ? std::fmodf(w, coord.w) : 0
			};
		}

		Coord4D<T> operator%(T coord)const
		{
			return {
				(T)coord ? std::fmodf(x, coord) : 0,
				(T)coord ? std::fmodf(y, coord) : 0,
				(T)coord ? std::fmodf(z, coord) : 0
				(T)coord ? std::fmodf(w, coord) : 0
			};
		}

		Coord4D<T> operator-()const
		{

			return *this * -1;
		}

		void operator-=(Coord4D<T> coord)
		{
			x -= coord.x;
			y -= coord.y;
			z -= coord.z;
			w -= coord.w;
		}

		void operator+=(Coord4D<T> coord)
		{
			x += coord.x;
			y += coord.y;
			z += coord.z;
			w += coord.w;
		}

		void operator*=(Coord4D<T> coord)
		{
			x *= coord.x;
			y *= coord.y;
			z *= coord.z;
			w *= coord.w;
		}

		void operator*=(T val)
		{
			x *= val;
			y *= val;
			z *= val;
			w *= val;
		}

		void operator/=(T val)
		{
			x /= val;
			y /= val;
			z /= val;
			w /= val;
		}


		bool operator==(Coord4D<T> coord)const
		{
			return
				x == coord.x &&
				y == coord.y &&
				z == coord.z &&
				w == coord.w;
		}

		bool operator!=(Coord4D<T> coord)const
		{
			return !(*this == coord);
		}

		//based on distance
		bool operator>(Coord4D<T> coord)
		{
			return this->distanceSquare() > coord.distanceSquare();
		}
		//based on distance
		bool operator<=(Coord4D<T> coord)const
		{
			return !(*this > coord);
		}
		//based on distance
		bool operator<(Coord4D<T> coord)
		{
			return distanceSquare() < coord.distanceSquare();
		}
		//based on distance
		bool operator>=(Coord4D<T> coord)const
		{
			return !(*this < coord);
		}

		cstring toString()
		{
			static char toStr[80]{};
			sprintf_s(toStr, "(%f, %f, %f, %f)", x, y, z, w);
			return toStr;
		}
	private:

	};


	typedef Coord4D<> Vec4;
	typedef Coord3D<> Vec3;
	typedef Coord2D<> Vec2;
	typedef Coord3D<int> Vec3i;
	typedef Coord2D<int> Vec2i;
	typedef Coord3D<uint> Vec3ui;
	typedef Coord2D<uint> Vec2ui;

	struct ColourRGBA
	{

		union
		{
			struct { uint id; };
			struct { ubyte r, g, b, a; };
		};

		//1/255 = 0.0039215686274509803921568627451
	#define BYTE_TO_FLOAT_MULTI 0.0039215686274509803921568627451

		ColourRGBA() :r((ubyte)255), g((ubyte)255), b((ubyte)255), a((ubyte)255)
		{}

		ColourRGBA(ubyte a_r, ubyte a_g, ubyte a_b, ubyte a_a = (ubyte)255) :r(a_r), g(a_g), b(a_b), a(a_a)
		{}
		//glm::vec4 toVec4()
		//{
		//	return glm::vec4(r * BYTE_TO_FLOAT_MULTI, g * BYTE_TO_FLOAT_MULTI, b * BYTE_TO_FLOAT_MULTI, a * BYTE_TO_FLOAT_MULTI);
		//}

		void set(ColourRGBA rgba)
		{
			set(
				rgba.r,
				rgba.g,
				rgba.b,
				rgba.a);
		}

		void set(ubyte a_r, ubyte a_g, ubyte a_b)
		{
			this[0][0] = a_r;
			this[0][1] = a_g;
			this[0][2] = a_b;
		}

		void set(ubyte a_r, ubyte a_g, ubyte a_b, ubyte a_a)
		{
			this[0][0] = a_r;
			this[0][1] = a_g;
			this[0][2] = a_b;
			this[0][3] = a_a;
		}

		void set(float a_r, float a_g, float a_b)
		{
			this[0][0] = ubyte(a_r * 255);
			this[0][1] = ubyte(a_g * 255);
			this[0][2] = ubyte(a_b * 255);
		}

		void set(float a_r, float a_g, float a_b, float a_a)
		{
			this[0][0] = ubyte(a_r * 255);
			this[0][1] = ubyte(a_g * 255);
			this[0][2] = ubyte(a_b * 255);
			this[0][3] = ubyte(a_a * 255);
		}

		//glm::vec4 getf4()
		//{
		//	glm::vec4 colour{
		// float(r * BYTE_TO_FLOAT_MULTI),
		// float(g * BYTE_TO_FLOAT_MULTI),
		// float(b * BYTE_TO_FLOAT_MULTI),
		// float(a * BYTE_TO_FLOAT_MULTI) };
		//	return colour;
		//}

		ColourRGBA operator+(ColourRGBA rgba)
		{
			return ColourRGBA{
				ubyte(r + rgba[0]),
				ubyte(g + rgba[1]),
				ubyte(b + rgba[2]),
				ubyte(a + rgba[3])};
		}

		ColourRGBA operator*(float rgba)
		{
			return ColourRGBA{
				ubyte(r * rgba),
				ubyte(g * rgba),
				ubyte(b * rgba),
				ubyte(a * rgba)};
		}

		ColourRGBA operator/(float rgba)
		{
			return ColourRGBA{
				ubyte(r / rgba),
				ubyte(g / rgba),
				ubyte(b / rgba),
				ubyte(a / rgba)};
		}

		friend ColourRGBA operator*(float rgba, ColourRGBA colour)
		{
			return ColourRGBA{
				ubyte(colour[0] * rgba),
				ubyte(colour[1] * rgba),
				ubyte(colour[2] * rgba),
				ubyte(colour[3] * rgba)};
		}
		friend ColourRGBA operator/(float rgba, ColourRGBA colour)
		{
			return ColourRGBA{
				ubyte(colour[0] / rgba),
				ubyte(colour[1] / rgba),
				ubyte(colour[2] / rgba),
				ubyte(colour[3] / rgba)};
		}
		ColourRGBA operator*(ColourRGBA rgba)
		{
			return ColourRGBA{
				ubyte(r * rgba.r / 255.f),
				ubyte(g * rgba.g / 255.f),
				ubyte(b * rgba.b / 255.f),
				ubyte(a * rgba.a / 255.f)};
		}

		ColourRGBA operator/(ColourRGBA rgba)
		{
			return ColourRGBA{
				ubyte(r / (float)rgba.r / 255.f),
				ubyte(g / (float)rgba.g / 255.f),
				ubyte(b / (float)rgba.b / 255.f),
				ubyte(a / (float)rgba.a / 255.f)};
		}

		void operator*=(ColourRGBA rgba)
		{
			*this = *this * rgba;
		}

		void operator/=(ColourRGBA rgba)
		{
			*this = *this / rgba;
		}

		ubyte& operator[](int index)
		{
			ubyte* error = nullptr;
			switch(index)
			{
			case 0:
				return static_cast<ubyte&>(r);
			case 1:
				return static_cast<ubyte&>(g);
			case 2:
				return static_cast<ubyte&>(b);
			case 3:
				return static_cast<ubyte&>(a);
			}
			return *error;
		}
	};

	struct UV
	{
		float u = 0, v = 0;

		void set(float a_u, float a_v)
		{
			this->u = a_u;
			this->v = a_v;
		}

		float& operator[](int m_index)
		{
			switch(m_index)
			{
			case 0:
				return static_cast<float&>(u);
			case 1:
				return static_cast<float&>(v);
			}
			float* error = nullptr;
			return *error;
		}

		bool operator==(UV uv)
		{
			return u == uv.u && v == uv.v;
		}

		void operator/=(float scale)
		{
			u /= scale;
			v /= scale;
		}
	};

	struct Vertex2D
	{
		Coord2D<> coord;
		ColourRGBA	colour;
		UV uv;

		void setCoord2D(float x, float y)
		{
			coord.x = x;
			coord.y = y;
		}
		//uses the 0-255 representation instead of 0-1
		void setColour(ubyte r, ubyte g, ubyte b, ubyte a = 255)
		{
			colour.r = r;
			colour.g = g;
			colour.b = b;
			colour.a = a;
		}
		//sets uv
		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}

		void print()
		{
			printf("Coord2D: (%f, %f)\n", coord.x, coord.y);
			printf("Colour : (%d, %d, %d, %d)\n", colour.r, colour.g, colour.b, colour.a);
			printf("UV     : (%f, %f)\n\n", uv.u, uv.v);
		}
	};

	struct Vertex3D
	{
		Coord3D<float> coord, norm;
		UV uv;
		ColourRGBA	colour;

		void setCoord(float x, float y, float z)
		{
			coord.x = x;
			coord.y = y;
			coord.z = z;
		}
		//uses the 0-255 representation instead of 0-1
		void setColour(ubyte r, ubyte g, ubyte b, ubyte a = 255)
		{
			colour.r = r;
			colour.g = g;
			colour.b = b;
			colour.a = a;
		}
		//sets uv
		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}

		void setNorm(float x, float y, float z)
		{
			norm.x = x;
			norm.y = y;
			norm.z = z;
		}

		bool operator==(Vertex3D vert)
		{
			return coord == vert.coord && norm == vert.norm && uv == vert.uv;
		}

		void print()
		{
			printf("Coord3D: (%f, %f, %f)\n", coord.x, coord.y, coord.z);
			printf("Colour : (%d, %d, %d, %d)\n", colour.r, colour.g, colour.b, colour.a);
			printf("UV     : (%f, %f)\n\n", uv.u, uv.v);
		}
	};

	struct Indicie
	{

		unsigned coord = 0;
		unsigned uv = 0;
		unsigned norm = 0;

		unsigned& operator[](int m_index)
		{
			switch(m_index)
			{
			case 0:
				return static_cast<unsigned&>(coord);
			case 1:
				return static_cast<unsigned&>(uv);
			case 2:
				return static_cast<unsigned&>(norm);
			}
			unsigned* error = nullptr;
			return *error;
		}

		friend bool operator<(const Indicie& in1, const Indicie& in2)
		{
			return in1.coord < in2.coord;
		}

		bool operator==(Indicie in)
		{
			for(short i = 0; i < 3; ++i)
				if((*this)[i] != in[i])
					return false;
			return true;

			//return (*this)[0] != in[0];
		}

		void correct()
		{
			coord -= 1;
			norm -= 1;
			uv -= 1;
		}
	};



}