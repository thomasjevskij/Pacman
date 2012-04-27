#ifndef GROUND_HPP
#define GROUND_HPP

#include "Level.hpp"

namespace View
{
	class Ground
	{
	public:
		Ground();

	private:
		struct Vertex
		{
			D3DXVECTOR3 Position;
			D3DXVECTOR3 Normal;
			D3DXVECTOR2	UV;
		};

		void CreateGround();
	};
}
#endif