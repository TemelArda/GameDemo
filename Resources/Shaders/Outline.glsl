#type vertex
#version 450 core

//From Vertex Array
layout (location = 0) in vec3 postion;
layout (location = 1) in vec3 normals;

//To Frag
struct VertexOutput
{    
    vec3 world_pos;
    vec3 normal;
    vec3 vertex_pos;
    vec3 view_dir;
};

layout (location = 0) out VertexOutput v_Out;

//Uniform - Object
uniform mat4 u_Transform;
//Unoform - Scene
uniform mat4 u_VP;

void main()
{
    vec4 world_pos = (u_Transform * vec4(postion, 1));
    
    v_Out.normal = normals;
    v_Out.world_pos = world_pos.xyz;
    v_Out.vertex_pos = postion;
    v_Out.view_dir = normalize(world_pos.xyz - vec3(u_VP[3][0], u_VP[3][1], u_VP[3][2]));
    gl_Position =  u_VP * world_pos;
};

#type fragment
#version 450 core

layout(location = 0) out vec4 fragColor;

struct VertexOutput
{    
    vec3 world_pos;
    vec3 normal;
    vec3 vertex_pos;
    vec3 view_dir;
};
layout(location = 0) in VertexOutput v_Out;
//Uniforms - Material
uniform vec3 u_Color;
uniform float u_OutlineWidth;
uniform float u_OutlineSoftness;
uniform float u_OutlinePower;

void main()
{
    float edge1 = 1 - u_OutlineWidth;
    float edge2 = edge1 + u_OutlineSoftness;
    float nDotv = dot(v_Out.normal, v_Out.view_dir);
    float fresnel = pow(1.0 - clamp(nDotv, 0, 1), u_OutlinePower);
    vec3 outline = mix(1, smoothstep(edge1, edge2, fresnel), step(0, edge1)) * u_Color;
    fragColor = vec4(outline , .35);
};