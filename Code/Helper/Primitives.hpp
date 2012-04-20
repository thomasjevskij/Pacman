#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "Global.hpp"

namespace Helper
{
	/**
		Some helper functions for the primitives in the WinAPI and/or DirectX library
	*/
	inline unsigned int GetRectWidth(const RECT& r)
	{
		return r.right - r.left;
	}

	inline unsigned int GetRectHeight(const RECT& r)
	{
		return r.bottom - r.top;
	}



	/**
		Define a point in 2D space
	*/
	template <typename T>
	struct Point2
	{
		T X;
		T Y;

		Point2();
		Point2(T x, T y);

		bool operator==(const Point2<T>& rhs) const;
		bool operator!=(const Point2<T>& rhs) const;
	};

	typedef Point2<int> Point2i;
	typedef Point2<float> Point2f;



	/**
		Define a point in 3D space
	*/
	template <typename T>
	struct Point3
	{
		T X;
		T Y;
		T Z;

		Point3();
		Point3(T x, T y, T z);

		bool operator==(const Point3<T>& rhs) const;
		bool operator!=(const Point3<T>& rhs) const;
	};

	typedef Point3<int> Point3i;
	typedef Point3<float> Point3f;



	/**
		Define an axis aligned bounding box, in 2D space
	*/
	template <typename T>
	struct AABB2
	{
		Point2<T> Corners[2];

		AABB2();
		AABB2(T x, T y, T width, T height);
		AABB2(const Point2<T>& p1, const Point2<T>& p2);

		T GetLeft() const;
		T GetBottom() const;
		T GetWidth() const;
		T GetHeight() const;
	};

	typedef AABB2<int> AABB2i;
	typedef AABB2<float> AABB2f;



	/**
		Define an axis aligned bounding box, in 3D space
	*/
	template <typename T>
	struct AABB3
	{
		Point3<T> Corners[2];

		AABB3();
		AABB3(T x, T y, T z, T width, T height, T depth);
		AABB3(const Point3<T>& p1, const Point3<T>& p2);

		T GetLeftPlane() const;
		T GetBottomPlane() const;
		T GetFrontPlane() const;

		T GetWidth() const;
		T GetDepth() const;
		T GetHeight() const;
	};

	typedef AABB3<int> AABB3i;
	typedef AABB3<float> AABB3f;




	/**
		Defines a frustum
	*/
	struct Frustum
	{
		Frustum() : NearDistance(0.0f), FarDistance(0.0f), FieldOfViewY(0.0f), AspectRatio(0.0f) {}

		float NearDistance;
		float FarDistance;
		float FieldOfViewY;
		float AspectRatio;

		/**
			Create a perspective projection matrix from the
			frustum.
		*/
		D3DXMATRIX CreatePerspectiveProjection() const;
	};



	/**
		IMPLEMENTATION
	*/

	template <typename T>
	Point2<T>::Point2() : X(0), Y(0) {}

	template <typename T>
	Point2<T>::Point2(T x, T y)
	{
		X = x;
		Y = y;
	}

	template <typename T>
	bool Point2<T>::operator==(const Point2<T>& rhs) const
	{
		return (X == rhs.X && Y == rhs.Y);
	}

	template <typename T>
	bool Point2<T>::operator!=(const Point2<T>& rhs) const
	{
		return !(*this == rhs);
	}



	template <typename T>
	Point3<T>::Point3() : X(0), Y(0), Z(0) {}

	template <typename T>
	Point3<T>::Point3(T x, T y, T z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	template <typename T>
	bool Point3<T>::operator==(const Point3<T>& rhs) const
	{
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z);
	}

	template <typename T>
	bool Point3<T>::operator!=(const Point3<T>& rhs) const
	{
		return !(*this == rhs);
	}




	template <typename T>
	AABB2<T>::AABB2() {}

	template <typename T>
	AABB2<T>::AABB2(T x, T y, T width, T height)
	{
		Corners[0] = Point2<T>(x, y);
		Corners[1] = Point2<T>(x + width, y + height);
	}

	template <typename T>
	AABB2<T>::AABB2(const Point2<T>& p1, const Point2<T>& p2)
	{
		Corners[0] = p1;
		Corners[1] = p2;
	}



	template <typename T>
	T AABB2<T>::GetLeft() const
	{
		return std::min(Corners[0].x, Corners[1].x);
	}

	template <typename T>
	T AABB2<T>::GetBottom() const
	{
		return std::min(Corners[0].y, Corners[1].y);
	}

	template <typename T>
	T AABB2<T>::GetWidth() const
	{
		return std::abs(Corners[0].x - Corners[1].x);
	}

	template <typename T>
	T AABB2<T>::GetHeight() const
	{
		return std::abs(Corners[0].y - Corners[1].y);
	}





	template <typename T>
	AABB3<T>::AABB3() {}

	template <typename T>
	AABB3<T>::AABB3(T x, T y, T z, T width, T depth, T height)
	{
		Corners[0] = Point3<T>(x, y, z);
		Corners[1] = Point3<T>(x + width, y + height, z + depth);
	}

	template <typename T>
	AABB3<T>::AABB3(const Point3<T>& p1, const Point3<T>& p2)
	{
		Corners[0] = p1;
		Corners[1] = p2;
	}


	template <typename T>
	T AABB3<T>::GetLeftPlane() const
	{
		return std::min(Corners[0].x, Corners[1].x);
	}

	template <typename T>
	T AABB3<T>::GetBottomPlane() const
	{
		return std::min(Corners[0].y, Corners[1].y);
	}

	template <typename T>
	T AABB3<T>::GetFrontPlane() const
	{
		return std::min(Corners[0].z, Corners[1].z);
	}


	template <typename T>
	T AABB3<T>::GetWidth() const
	{
		return std::abs(Corners[0].x - Corners[1].x);
	}

	template <typename T>
	T AABB3<T>::GetDepth() const
	{
		return std::abs(Corners[0].z - Corners[1].z);
	}

	template <typename T>
	T AABB3<T>::GetHeight() const
	{
		return std::abs(Corners[0].y - Corners[1].y);
	}
}

#endif