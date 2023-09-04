#include "skinned_mesh.hlsli"

#define POINT 0
#define LINEAR 1
#define ANISOTROPIC 2
SamplerState samplerStates[5] : register(s0);
Texture2D textureMaps[4]:register(t0);

// SHADOW
SamplerComparisonState comparisonSamplerState : register(s5);
Texture2D shadowMap : register(t8);

// DISSOLVE
Texture2D maskTexture : register(t15);

float4 main(VS_OUT pin) :SV_TARGET
{
    float mask_value = maskTexture.Sample(samplerStates[0],pin.texcoord) * pin.color;

    float4 color = textureMaps[0].Sample(samplerStates[ANISOTROPIC],pin.texcoord);
    float alpha = color.a;

#if 0
    // 逆ガンマ補正
    //const float GAMMA = 1.0;
    const float GAMMA = 2.2;
    color.rgb = pow(color.rgb, GAMMA);
#else
    // ガンマ補正
    const float GAMMA = 2.2;
    color.rgb = pow(color.rgb, 1.0 / GAMMA);
#endif

    float3 N = normalize(pin.worldNormal.xyz);

#if 1
    float3 T = normalize(pin.worldTangent.xyz);
    float sigma = pin.worldTangent.w;
    T = normalize(T - N * dot(N, T));
    float3 B = normalize(cross(N, T) * sigma);

    float4 normal = textureMaps[1].Sample(samplerStates[LINEAR], pin.texcoord);
    normal = (normal * 2.0) - 1.0;
    N = normalize((normal.x * T) + (normal.y * B) + (normal.z * N));
#endif

    float3 L = normalize(-lightDirection.xyz);
    float3 diffuse = color.rgb * max(0, dot(N, L));
    float3 V = normalize(cameraPosition.xyz - pin.worldPosition.xyz);
    float3 specular = pow(max(0, dot(N, normalize(V + L))), 128);

    // dissolve
#if 0
    alpha = step(parameters.x, mask_value);
#endif

    // SHADOW
#if 1
    const float shadowDepthBias = 0.001;
#else
    // ここでは、サーフェスの法線と光の方向に基づいて、バイアスの最大値が 0.01、最小値が 0.001 になっています。
    const float shadowDepthBias = max(0.01 * (1.0 - dot(N, L)), 0.001);
#endif

    float4 lightViewPosition = mul(pin.worldPosition, lightViewProjection);
    lightViewPosition = lightViewPosition / lightViewPosition.w;
    float2 lightViewTexcoord = 0;
    lightViewTexcoord.x = lightViewPosition.x * 0.5 + 0.5;
    lightViewTexcoord.y = lightViewPosition.y * -0.5 + 0.5;
    float depth = saturate(lightViewPosition.z - shadowDepthBias);

    float3 shadowFactor = 1.0f;
    shadowFactor = shadowMap.SampleCmpLevelZero(comparisonSamplerState, lightViewTexcoord, depth).xxx;

    return float4((diffuse + specular) * shadowFactor/*SHADOW*/, alpha) * pin.color;

    //color.a *= alpha;
    //return color;
    

    //return color * pin.color;
    //return float4(diffuse, alpha) * pin.color;
    
    //return float4(diffuse + specular, alpha) * pin.color;
}

#if 0
#include "skinned_mesh.hlsli"
#define POINT 0
#define LINEAR 1
#define ANISOTROPIC 2
SamplerState sampler_states[3]:register(s0);
Texture2D texture_maps[4]:register(t0);
Texture2D mask_texture : register(t15);
float4 main(VS_OUT pin) :SV_TARGET
{
    float mask_value = mask_texture.Sample(sampler_states[0],pin.texcoord) * pin.color;

    float4 color = texture_maps[0].Sample(sampler_states[ANISOTROPIC],pin.texcoord);
    //float alpha = color.a;
#if 1
    // Inverse gamma process
    const float GAMMA = 1.0;
    //const float GAMMA = 2.2;
    color.rgb = pow(color.rgb, GAMMA);
#endif

    float3 N = normalize(pin.world_normal.xyz);
    float3 T = normalize(pin.world_tangent.xyz);
    float sigma = pin.world_tangent.w;
    T = normalize(T - N * dot(N, T));
    float3 B = normalize(cross(N, T) * sigma);

    float4 normal = texture_maps[1].Sample(sampler_states[LINEAR], pin.texcoord);
    normal = (normal * 2.0) - 1.0;
    N = normalize((normal.x * T) + (normal.y * B) + (normal.z * N));

    float3 L = normalize(-light_direction.xyz);
    float3 diffuse = color.rgb * max(0, dot(N, L));
    float3 V = normalize(camera_position.xyz - pin.world_position.xyz);
    float3 specular = pow(max(0, dot(N, normalize(V + L))), 128);

    // dissolve
    float alpha = step(parameters.x, mask_value);


    //color.a *= alpha;
    //return color;


    return color * pin.color;
    //return float4(diffuse, alpha) * pin.color;

    return float4(diffuse + specular, alpha) * pin.color;
}
#endif