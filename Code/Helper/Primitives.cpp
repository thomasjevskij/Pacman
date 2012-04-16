#include "Primitives.hpp"

namespace Helper
{
	D3DXMATRIX Frustum::CreatePerspectiveProjection() const
	{
		D3DXMATRIX result;
		D3DXMatrixPerspectiveFovLH(&result, FieldOfViewY, AspectRatio, NearDistance, FarDistance);

		return result;
	}
}