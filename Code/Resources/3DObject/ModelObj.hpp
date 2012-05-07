#ifndef MODELOBJ_HPP
#define MODELOBJ_HPP

#include <string>
#include <map>

#include "Global.hpp"
#include "StaticModelData.hpp"
#include "Effect.hpp"
#include "Camera.hpp"

namespace Resources
{
	class ModelObj
	{
	public:
		ModelObj(ID3D10Device* device, const std::string& filename);
		~ModelObj() throw();

		// Bind the model's associated vertex buffer to an input slot
		void Bind(unsigned int slot = 0);

		// Draw the object. Must be bound to an input slot.
		void Draw(const D3DXVECTOR3& drawPosition, const Helper::Camera& camera);

		// Scale the object
		void SetScale(float newScale);
	private:
		ID3D10Device* mDevice;
		StaticModelData mData;
		Framework::Effect* mEffect;
		float mScale;

		ModelObj(const ModelObj&);
		ModelObj& operator=(const ModelObj&);

		bool Load(const std::string& filename);
		bool LoadMaterial(const std::string& filename);
		void UpdatePositionInMatrix(const D3DXVECTOR3& position);
	};
}
#endif