#shader vertex
#version 330 core

//From Vertex Array
layout (location = 0) in vec3 postion;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

//To Frag
out vec2 v_TexCoord;
out vec3 v_Pos;
out vec3 v_Normal;

//Unoform Postion
uniform mat4 u_Transform;
//Unoforms Material
uniform float u_Shininess;
//Unoforms Enviroment
uniform mat4 u_VP;


void main()
{
    vec4 world_pos = (u_Transform * vec4(postion, 1));
    gl_Position =  u_VP * world_pos;
    v_TexCoord = texCoord;
    v_Normal = normals;
    v_Pos = world_pos.xyz;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Pos;
in vec3 v_Normal;

//Uniforms Enviroment
uniform float u_Time;
uniform vec4 u_LightPosition;
//Uniforms Material
uniform vec4 u_AmbientProduct, u_DiffuseProduct, u_SpecularProduct;
uniform float u_Shininess;
uniform sampler2D u_Texture;


void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);

    vec3 cirColor = 0.5 + 0.5 * cos(u_Time + vec3(0,1,0)) * sin(u_Time + vec3(2,0,4));
    float thickness = 1.0;
    // Control with mouse
    // thickness = iMouse.x / iResolution.x;
    float fade = 0.05;
    float r = 1.0;
    float distance = r - length(v_TexCoord * 2 - 1);
    vec3 cir = vec3(smoothstep(0.0, fade, distance));
    cir *= vec3(smoothstep(thickness + fade, thickness, distance));
    vec4 c =  vec4(v_Pos, 1.0);
    color =  c * texColor;
};