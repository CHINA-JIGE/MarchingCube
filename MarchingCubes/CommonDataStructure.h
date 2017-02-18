/*************************************************

		Common Data Structure definition

		all data structure that will be used as parameter type
		will be defined under ParamProtocol namespace

		Author :Jige
		Last Edit : 2017.1.12


*************************************************/


#include <cmath>
#include <vector>
#pragma once

namespace ParamProtocol
{

	const float CONST_PI = 3.1415926f;

	//二维向量
	struct VECTOR2
	{
		VECTOR2() { };
		VECTOR2(float X, float Y) { x = X; y = Y; };
		VECTOR2(const float column[2])
		{
			x = column[0];
			y = column[1];
		}

		float	Length()
		{
			return sqrt(x*x + y*y);
		};

		VECTOR2&	Normalize()
		{
			float len = Length();
			if (len != 0)
			{
				x /= len;
				y /= len;
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
			}
			return *this;
		}

		bool	operator==(const VECTOR2& vec)
		{
			if (vec.x == x&&vec.y == y)
				return true;
			else
				return false;
		}

		VECTOR2 operator+(const VECTOR2& vec)
		{
			return VECTOR2(x + vec.x, y + vec.y);
		}

		VECTOR2 operator-(const VECTOR2& vec)
		{
			return VECTOR2(x - vec.x, y - vec.y);
		}

		VECTOR2& operator+=(const VECTOR2& vec)
		{
			x += vec.x;
			y += vec.y;
			return *this;
		}

		VECTOR2& operator-=(const VECTOR2& vec)
		{
			x -= vec.x;
			y -= vec.y;
			return *this;
		}

		VECTOR2 operator*(const float scaleFactor)
		{
			return VECTOR2(scaleFactor*x, scaleFactor* y);
		}

		friend VECTOR2 operator*(float scaleFactor, const VECTOR2& vec)
		{
			return VECTOR2(scaleFactor*vec.x, scaleFactor* vec.y);
		}


		VECTOR2& operator*=(const float scaleFactor)
		{
			x *= scaleFactor;
			y *= scaleFactor;
			return *this;
		}

		float x;
		float y;
	};

	//三维向量
	struct VECTOR3
	{
		VECTOR3() { };
		VECTOR3(float X, float Y, float Z) { x = X; y = Y; z = Z; };
		VECTOR3(const float column[3])
		{
			x = column[0];
			y = column[1];
			z = column[2];
		}

		float	Length() const
		{
			return sqrtf(x*x + y*y + z*z);
		};

		VECTOR3&	Normalize()
		{
			float len = Length();
			if (len != 0)
			{
				x /= len;
				y /= len;
				z /= len;
			}
			else
			{
				x = y = z = 0.0f;
			}
			return *this;
		}


		bool	operator==(const VECTOR3& vec)
		{
			if (vec.x == x&&vec.y == y&&vec.z == z)
				return true;
			else
				return false;
		}

		VECTOR3 operator+(const VECTOR3& vec)
		{
			return VECTOR3(x + vec.x, y + vec.y, z + vec.z);
		}

		VECTOR3 operator-(const VECTOR3& vec)
		{
			return VECTOR3(x - vec.x, y - vec.y, z - vec.z);
		}

		friend VECTOR3 operator-(const VECTOR3& v1, const VECTOR3& v2)
		{
			return VECTOR3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
		};

		VECTOR3& operator+=(const VECTOR3& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
			return *this;
		}

		VECTOR3& operator-=(const VECTOR3& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			return *this;
		}

		VECTOR3 operator*(const float scaleFactor)
		{
			return VECTOR3(scaleFactor*x, scaleFactor* y, scaleFactor* z);
		}

		VECTOR3 operator*(const VECTOR3& vec)
		{
			return VECTOR3(vec.x*x, vec.y*y, vec.z*z);
		}

		//the scalar is put before the vector3
		friend VECTOR3 operator*(float scaleFactor, const VECTOR3& vec)
		{
			return VECTOR3(scaleFactor*vec.x, scaleFactor* vec.y, scaleFactor* vec.z);
		}

		VECTOR3& operator*=(const float scaleFactor)
		{
			x *= scaleFactor;
			y *= scaleFactor;
			z *= scaleFactor;
			return *this;
		}

		float x;
		float y;
		float z;
	};

	//四维向量
	struct VECTOR4
	{
		VECTOR4() { };
		VECTOR4(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; };
		VECTOR4(const float column[4])
		{
			x = column[0];
			y = column[1];
			z = column[2];
			w = column[3];
		}

		float	Length()
		{
			return sqrt(x*x + y*y + z*z + w*w);
		};

		VECTOR4&	Normalize()
		{
			float len = Length();
			if (len != 0.0f)
			{
				x /= len;
				y /= len;
				z /= len;
				w /= len;
			}
			else
			{
				x = y = z = w = 0.0f;
			}
			return *this;
		}

		bool	operator==(const VECTOR4& vec)
		{
			if (vec.x == x&&vec.y == y&&vec.z == z&&vec.w == w)
				return true;
			else
				return false;
		}

		VECTOR4 operator+(const VECTOR4& vec)
		{
			return VECTOR4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
		}

		VECTOR4 operator-(const VECTOR4& vec)
		{
			return VECTOR4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
		}

		VECTOR4& operator+=(const VECTOR4& vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
			return *this;
		}

		VECTOR4& operator-=(const VECTOR4& vec)
		{
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
			return *this;
		}

		VECTOR4 operator*(const float scaleFactor)
		{
			return VECTOR4(scaleFactor*x, scaleFactor* y, scaleFactor* z, scaleFactor* w);
		}

		friend VECTOR4 operator*(float scaleFactor, const VECTOR4& vec)
		{
			return VECTOR4(scaleFactor*vec.x, scaleFactor* vec.y, scaleFactor* vec.z, scaleFactor*vec.w);
		}

		VECTOR4& operator*=(const float scaleFactor)
		{
			x *= scaleFactor;
			y *= scaleFactor;
			z *= scaleFactor;
			w *= scaleFactor;
			return *this;
		}

		float x;
		float y;
		float z;
		float w;
	};

	//2D矩形
	struct RECT
	{
		RECT() { min = { 0,0 }; max = { 0,0}; }
		RECT(const VECTOR2& _min, const VECTOR2& _max)
			:min(_min), max(_max) {};

		VECTOR2 min;
		VECTOR2 max;
	};

	//折线，只记录下折线的所有顶点，于是第k,k+1个顶点可以构成一条线段
	//最后一个和第一个顶点构成一个线段
	typedef  std::vector<VECTOR3> LineStrip;

	//边缘组，就是闭合折线的集合，每一段LineStrip都只属于一个CT切层
	//一个LineStripGroup就对应着一个相对完整的部位
	typedef std::vector<LineStrip> LineStripGroup;

	//三维重建的输出
	//		就用这个 ！std::vector<VECTOR3> vertexList;
	/*struct MeshReconstructionOutput
	{
		std::vector<VECTOR3> vertexList;
		std::vector<int>		 indexList;
	};*/

}
