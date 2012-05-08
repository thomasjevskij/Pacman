struct VS_INPUT
{
	float3		position1	: POSITION0;
	float3		normal1		: NORMAL0;
	float2		uv1			: UV0;
	float3		position2	: POSITION1;
	float3		normal2		: NORMAL1;
	float2		uv2			: UV1;
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

Texture2D g_modelTexture;
float4 	g_lightDirection;
float	g_t;

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;
	
	float3 pos	= lerp(input.position1, input.position2, g_t);
	float3 nor	= lerp(input.normal1, input.normal2, g_t);

	output.position = mul(float4(pos, 1.0), g_matWVP);
	output.positionW = mul(float4(pos, 1.0), g_matWorld).xyz;
	output.normalW = mul(float4(nor, 0.0), g_matWorld).xyz;
	output.uv = lerp(input.uv1, input.uv2, g_t);

	return output;
}

float4 PS(PS_INPUT input) : SV_Target0
{
	float4 texColor = g_modelTexture.Sample(linearSampler, input.uv);
	//float4 texColor = float4(1.0, 1.0, 1.0, 1.0);
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

