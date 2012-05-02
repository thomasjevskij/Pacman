#include "Pass.hpp"

namespace Framework
{
	Pass::Pass(ID3D10EffectPass* pass) :
		mPass(pass), 
		mCalculatedLayout(NULL), 
		mShouldLayoutBeRecalculated(true)
	{
		D3D10_PASS_DESC description;
		mPass->GetDesc(&description);

		mName = description.Name;
	}

	Pass::~Pass() throw()
	{
		SafeRelease(mCalculatedLayout);
	}

	void Pass::SetInputLayout(const InputLayoutVector& inputLayout)
	{
		mInputLayout = inputLayout;
		mShouldLayoutBeRecalculated = true;
	}

	bool Pass::Apply(ID3D10Device* device)
	{
		if (mShouldLayoutBeRecalculated)
		{
			device->IASetInputLayout(NULL);
			if (!RecalculateLayout(device))
				return false;
		}
	
		device->IASetInputLayout(mCalculatedLayout);
		return SUCCEEDED(mPass->Apply(0));
	}

	bool Pass::RecalculateLayout(ID3D10Device* device)
	{
		SafeRelease(mCalculatedLayout);

		D3D10_INPUT_ELEMENT_DESC* vertexDescription = new D3D10_INPUT_ELEMENT_DESC[mInputLayout.size()];
	
		for (unsigned int i = 0; i < mInputLayout.size(); ++i)
		{
			vertexDescription[i].SemanticName = mInputLayout[i].mName.c_str();
			vertexDescription[i].SemanticIndex = mInputLayout[i].mSemanticIndex;
			vertexDescription[i].Format = mInputLayout[i].mFormat;

			vertexDescription[i].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
			vertexDescription[i].InputSlot = 0;
			vertexDescription[i].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
			vertexDescription[i].InstanceDataStepRate = 0;
		}

	
		D3D10_PASS_DESC passDescription;
		mPass->GetDesc(&passDescription);

		HRESULT result = device->CreateInputLayout(vertexDescription,
													static_cast<unsigned int>(mInputLayout.size()),
													passDescription.pIAInputSignature,
													passDescription.IAInputSignatureSize,
													&mCalculatedLayout);
		SafeDelete(vertexDescription);

		if (SUCCEEDED(result))
			mShouldLayoutBeRecalculated = false;

		return SUCCEEDED(result);
	}
}
