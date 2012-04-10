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
		T x;
		T y;

		Point2();
		Point2(T x, T y);
	};

	typedef Point2<int> Point2i;
	typedef Point2<float> Point2f;



	/**
		Define a point in 3D space
	*/
	template <typename T>
	struct Point3
	{
		T x;
		T y;
		T z;

		Point3();
		Point3(T x, T y, T z);
	};

	typedef Point3<int> Point3i;
	typedef Point3<float> Point3f;



	/**
		Define an axis aligned bounding box, in 2D space
	*/
	template <typename T>
	struct AABB2
	{
		Point2<T> mCorners[2];

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
		Point3<T> mCorners[2];

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
		Frustum() : mNearDistance(0.0f), mFarDistance(0.0f), mFieldOfViewY(0.0f), mAspectRatio(0.0f) {}

		float mNearDistance;
		float mFarDistance;
		float mFieldOfViewY;
		float mAspectRatio;

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
	Point2<T>::Point2() : x(0), y(0) {}

	template <typename T>
	Point2<T>::Point2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}



	template <typename T>
	Point3<T>::Point3() : x(0), y(0), z(0) {}

	template <typename T>
	Point3<T>::Point3(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}





	template <typename T>
	AABB2<T>::AABB2() {}

	template <typename T>
	AABB2<T>::AABB2(T x, T y, T width, T height)
	{
		mCorners[0] = Point2<T>(x, y);
		mCorners[1] = Point2<T>(x + width, y + height);
	}

	template <typename T>
	AABB2<T>::AABB2(const Point2<T>& p1, const Point2<T>& p2)
	{
		mCorners[0] = p1;
		mCorners[1] = p2;
	}



	template <typename T>
	T AABB2<T>::GetLeft() const
	{
		return std::min(mCorners[0].x, mCorners[1].x);
	}

	template <typename T>
	T AABB2<T>::GetBottom() const
	{
		return std::min(mCorners[0].y, mCorners[1].y);
	}

	template <typename T>
	T AABB2<T>::GetWidth() const
	{
		return std::abs(mCorners[0].x - mCorners[1].x);
	}

	template <typename T>
	T AABB2<T>::GetHeight() const
	{
		return std::abs(mCorners[0].y - mCorners[1].y);
	}





	template <typename T>
	AABB3<T>::AABB3() {}

	template <typename T>
	AABB3<T>::AABB3(T x, T y, T z, T width, T depth, T height)
	{
		mCorners[0] = Point3<T>(x, y, z);
		mCorners[1] = Point3<T>(x + width, y + height, z + depth);
	}

	template <typename T>
	AABB3<T>::AABB3(const Point3<T>& p1, const Point3<T>& p2)
	{
		mCorners[0] = p1;
		mCorners[1] = p2;
	}


	template <typename T>
	T AABB3<T>::GetLeftPlane() const
	{
		return std::min(mCorners[0].x, mCorners[1].x);
	}

	template <typename T>
	T AABB3<T>::GetBottomPlane() const
	{
		return std::min(mCorners[0].y, mCorners[1].y);
	}

	template <typename T>
	T AABB3<T>::GetFrontPlane() const
	{
		return std::min(mCorners[0].z, mCorners[1].z);
	}


	template <typename T>
	T AABB3<T>::GetWidth() const
	{
		return std::abs(mCorners[0].x - mCorners[1].x);
	}

	template <typename T>
	T AABB3<T>::GetDepth() const
	{
		return std::abs(mCorners[0].z - mCorners[1].z);
	}

	template <typename T>
	T AABB3<T>::GetHeight() const
	{
		return std::abs(mCorners[0].y - mCorners[1].y);
	}

}

#endif