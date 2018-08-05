//==============================================================================
// 顶点着色器
//==============================================================================
cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
struct VS_3D {
	float4 pos0 : POSITION0;
	float2 tex : TEXCOORD;
};
struct PS_3D {
	float4 pos0 : SV_POSITION;
	float3 pos1 : POSITION;
	float2 tex : TEXCOORD;
};
PS_3D vs_3d(VS_3D i) {
	PS_3D o;
	o.pos0 = i.pos0;
	o.pos0 = mul(o.pos0, g_world);
	o.pos1 = o.pos0.xyz;
	o.pos0 = mul(o.pos0, g_view);
	o.pos0 = mul(o.pos0, g_projection);
	o.tex = i.tex;
	return o;
}
//==============================================================================
// 像素着色器
//==============================================================================
cbuffer cb0 : register(b0) {
	float3 g_eyepos;
	float4 g_fogcolor;
	float g_fogstart;
	float g_fogrange;
}
Texture2D tx : register(t0);
SamplerState sam : register(s0);
struct PS_3D {
	float4 pos0 : SV_POSITION;
	float3 pos1 : POSITION;
	float2 tex : TEXCOORD;
};
float4 ps_3d(PS_3D i) : SV_TARGET{
	float4 v = tx.Sample(sam, i.tex);

	const float d = distance(g_eyepos, i.pos1);
	if (d > g_fogstart) {
		const float s = saturate((d - g_fogstart) / g_fogrange);
		v = lerp(v, g_fogcolor, s);
	}
	return v;
}
//==============================================================================
// 顶点格式
//==============================================================================
三维::C顶点格式 v顶点格式;
v顶点格式.f添加(三维::C顶点格式::e位置, 4);
v顶点格式.f添加(三维::C顶点格式::e纹理, 2);