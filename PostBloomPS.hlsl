
cbuffer Data : register(b0)
{
	float pixelWidth;
	float pixelHeight;
	int blurAmount;
}


// Defines the input to this pixel shader
// - Should match the output of our corresponding vertex shader
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float2 uv           : TEXCOORD0;
};

// Textures and such
Texture2D originalRender	: register(t0);
Texture2D brightSamples		: register(t1);
SamplerState Sampler		: register(s0);


float4 main(VertexToPixel input) : SV_TARGET
{
	// Blur the bright sample render
	float4 totalColor = float4(0,0,0,0);
	uint numSamples = 0;

	for (int y = -blurAmount; y <= blurAmount; y++)
	{
		for (int x = -blurAmount; x <= blurAmount; x++)
		{
			float2 uv = input.uv + float2(x * pixelWidth, y * pixelHeight);
			totalColor += brightSamples.Sample(Sampler, uv);

			numSamples++;
		}
	}

	// Combine the original render with the blurred sample
	return (totalColor / numSamples) + originalRender.Sample(Sampler, input.uv);
}