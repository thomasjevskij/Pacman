#ifndef MORPH_ANIMATION_HPP
#define MORPH_ANIMATION_HPP

#include <vector>
#include "Global.hpp"
#include "Camera.hpp"

namespace Helper
{
	class MorphAnimation
	{
	public:


		void Update(float dt);
		void Draw(const Camera& camera, D3DXVECTOR3 position);
	private:
		float mTime;
	};
}

#endif