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

    gl_Position =  u_VP * world_pos;
};

#type fragment
#version 450 core

layout(location = 0) out vec4 color;

struct VertexOutput
{    
    vec3 world_pos;
    vec3 normal;
    vec3 vertex_pos;
};
layout(location = 0) in VertexOutput v_Out;

//Uniforms - Material
uniform vec3 u_Color;

void main()
{
    color = vec4(u_Color, 1.0);
};
