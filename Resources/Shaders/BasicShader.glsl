#type vertex
#version 450 core

//From Vertex Array
layout (location = 0) in vec3 postion;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

//To Frag
struct VertexOutput
{    
    vec2 texCoord;
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
    vec4 world_pos = (u_Transform * vec4(postion, 1.0));
    
    v_Out.texCoord = texCoord;
    v_Out.normal = normals;
    v_Out.world_pos = world_pos.xyz;
    v_Out.vertex_pos = postion;

    gl_Position =  u_VP * world_pos;
};


#type fragment
#version 450 core

vec4 ambient_diffuse_specular(vec3 world_pos, vec3 light_pos, vec3 normal);

layout(location = 0) out vec4 color;

struct VertexOutput
{    
    vec2 texCoord;
    vec3 world_pos;
    vec3 normal;
    vec3 vertex_pos;
};
layout(location = 0) in VertexOutput v_Out;



//Uniforms - Material
uniform sampler2D u_Texture;
uniform vec3 u_Ambient_product;
uniform vec3 u_Diffuse_product;
uniform vec3 u_Specular_product;
uniform float u_Shininess;

void main()
{
    vec4 texColor = texture(u_Texture, v_Out.texCoord);
    vec4 c = ambient_diffuse_specular(v_Out.world_pos, vec3(0.0, 0.0, 0.0), v_Out.normal);
    color = c * texColor;
};

vec4 ambient_diffuse_specular(vec3 world_pos, vec3 light_pos, vec3 normal)
{	
    vec3 to_light = normalize (light_pos - world_pos);
	vec3 to_eye = normalize (-world_pos);
	vec3 R = reflect (-light_pos, normal);

    vec3 ambient = u_Ambient_product;
	
    float cos_theta = max(dot(to_light, normal), 0.0);
    vec3 diffuse = u_Diffuse_product * cos_theta;

    float cos_phi = pow(max (dot(R, to_eye), 0.0), u_Shininess); 
    vec3 specular = cos_phi * u_Specular_product;
	
    if(dot(light_pos, normal) < 0.0)
		specular = vec3(0.0, 0.0, 0.0);

    return vec4(ambient + diffuse + specular, 1.0);
}