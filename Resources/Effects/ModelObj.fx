struct VS_INPUT
{
	float3		position	: POSITION;
	float3		normal		: NORMAL;
	float2		uv			: UV;
};

struct PS_INPUT
{
	float4		position	: SV_POSITION;
	float3		positionW	: POSITION;
	float3		normalW		: NORMAL;
	float2		uv			: UV;
};

RasterizerState NoCulling
{
	CullMode = None;
	//FillMode = Wireframe;
};

SamplerState linearSampler {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS_EQUAL;
};

cbuffer cbEveryFrame
{
	matrix	g_matWorld;
	matrix	g_matWVP;
};

//Texture2D g_modelTexture;
float4 g_lightDirection;

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;

	output.position = mul(float4(input.position, 1.0), g_matWVP);
	output.positionW = mul(float4(input.position, 1.0), g_matWorld).xyz;
	output.normalW = mul(float4(input.normal, 0.0), g_matWorld).xyz;
	output.uv = input.uv;

	return output;
}

float4 PS(PS_INPUT input) : SV_Target0
{
	//float4 texColor = g_modelTexture.Sample(linearSampler, input.uv);
	float4 texColor = float4(0.5, 0.5, 0.5, 1.0);
	float3 lightVec = normalize(g_lightDirection.xyz - input.positionW);
	float diffuse = dot(lightVec, normalize(input.normalW));

	texColor = texColor + (diffuse * 0.5);

	return texColor;
}

technique10 DrawTechnique
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));

		SetRasterizerState(NoCulling);
		SetDepthStencilState(EnableDepth, 0xff);
	}
}

