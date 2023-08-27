#type vertex
#version 450 core
layout (location = 0) in vec3 postion;;

out vec3 TexCoords;

//Unoform - Scene
uniform mat4 u_VP;

void main()
{
    TexCoords = postion;
    gl_Position = u_VP * vec4(postion, 1.0);
    
}  

#type fragment
#version 450 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube u_Skybox;

void main()
{    
    FragColor = texture(u_Skybox, TexCoords);
}