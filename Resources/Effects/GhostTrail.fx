float4 Color;
Texture2D Texture;

struct VSParticleIn
{
    float3 Position				: POSITION;         //position of the particle
    float3 Velocity				: VELOCITY;           //velocity of the particle
    float3 Acceleration			: ACCELERATION;     //acceleration of the particle
    float TimeLived				: TIMELIVED;		//how long the particle has lived
	float TimeToLive			: TIMETOLIVE;		//how ling the particle is supposed to live
};

struct VSParticleDrawOut
{
    float3 Position : POSITION;
    float Radius : RADIUS;
};

struct PSSceneIn
{
    float4 Position : SV_Position;
    float2 Tex : TEXTURE;
};

cbuffer cb0
{
    float4x4 WorldViewProj;
	float4x4 InvView;
};

cbuffer Immutable
{
    float3 g_positions[4] =
    {
        float3( -0.2, 0.2, 0 ),
        float3( 0.2, 0.2, 0 ),
        float3( -0.2, -0.2, 0 ),
        float3( 0.2, -0.2, 0 ),
    };
    float2 g_texcoords[4] = 
    { 
        float2(0,1), 
        float2(1,1),
        float2(0,0),
        float2(1,0),
    };
};

SamplerState SamLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};

BlendState AdditiveBlending
{
    AlphaToCoverageEnable = false;
    BlendEnable[0] = true;
    SrcBlend = SRC_ALPHA;
    DestBlend = ONE;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0f;
};

DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};

DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS_EQUAL;
};

VSParticleDrawOut VSScenemain(VSParticleIn input)
{
    VSParticleDrawOut output = (VSParticleDrawOut)0;
    
    //
    // Pass the point through
    //
    output.Position = input.Position;
    output.Radius = 1.5;
	
    
    
    return output;
}

[maxvertexcount(4)]
void GSScenemain(point VSParticleDrawOut input[1], inout TriangleStream<PSSceneIn> SpriteStream)
{
    PSSceneIn output;
    
    //
    // Emit two new triangles
    //
    for(int i=0; i<4; i++)
    {
        float3 position = g_positions[i]*input[0].Radius;
        position = mul( position, (float3x3)InvView ) + input[0].Position;
        output.Position = mul( float4(position,1.0), WorldViewProj );
        
        output.Tex = g_texcoords[i];
        SpriteStream.Append(output);
    }
    SpriteStream.RestartStrip();
}

float4 PSScenemain(PSSceneIn input) : SV_Target
{   
    return Texture.Sample( SamLinear, input.Tex ) * Color;
}




technique10 RenderParticles
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, VSScenemain() ) );
        SetGeometryShader( CompileShader( gs_4_0, GSScenemain() ) );
        SetPixelShader( CompileShader( ps_4_0, PSScenemain() ) );
        
        SetBlendState( AdditiveBlending, float4( 1.0f, 1.0f, 1.0f, 1.0f ), 0xFFFFFFFF );
        SetDepthStencilState(EnableDepth, 0xff);
    }  
}