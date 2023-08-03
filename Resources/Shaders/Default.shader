#shader vertex
#version 330 core

layout (location = 0) in vec4 postion;
layout (location = 1) in vec2 texCoord;
out vec2 v_TexCoord;

uniform float u_Time;
uniform mat4 u_MVP;

void main()
{
    gl_Position =  u_MVP * postion ;
    v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;
uniform float u_Time;
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

    color =  texColor;
};