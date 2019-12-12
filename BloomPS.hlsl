
// Defines the input to this pixel shader
// - Should match the output of our corresponding vertex shader
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float2 uv           : TEXCOORD0;
};

// Textures and such
Texture2D Pixels		: register(t0);
SamplerState Sampler	: register(s0);


// Entry point for this pixel shader
float4 main(VertexToPixel input) : SV_TARGET
{
	// Determine if the pixel is bright enough to sample
	float4 color = Pixels.Sample(Sampler, input.uv);
	// Return a transparent pixel if the pixel is not bright enough
	if (dot(color.xyz, float3(0.21f, 0.72f, 0.07f)) >= 0.85f)
		return color;
	else
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
}