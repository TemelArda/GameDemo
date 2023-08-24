#type vertex
#version 450 core

//From Vertex Array
layout (location = 0) in vec3 postion;
layout (location = 1) in vec3 normals;

struct VertexOut
{
    vec3 normals;
    vec3 postion;
    vec3 world_pos;
};

out VertexOut v_out;

//Uniform - Object
uniform mat4 u_Transform;
//Unoform - Scene
uniform mat4 u_VP;

void main()
{
    vec4 world_pos = (u_Transform * vec4(postion, 1));

    v_out.normals = normals;
    v_out.postion = postion;
    v_out.world_pos = world_pos.xyz;

    gl_Position =  u_VP * world_pos;
};

#type geometry
#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

struct VertexOut
{
    vec3 normals;
    vec3 postion;
    vec3 world_pos;
};
in VertexOut v_out[];

struct GeometryOut
{
    vec3 normals;
    vec3 postion;
    vec3 world_pos;
    vec2 barycentricCoordinates;
};

out GeometryOut g_out;
void main() 
{    
    vec3 triangleNormal = normalize(cross(v_out[1].world_pos - v_out[0].world_pos, v_out[2].world_pos - v_out[0].world_pos));
    
    gl_Position = gl_in[0].gl_Position; 
    g_out.normals = triangleNormal;
    g_out.postion = v_out[0].postion;
    g_out.world_pos = v_out[0].world_pos;
    g_out.barycentricCoordinates = vec2(1.0, 0.0);
    EmitVertex();
    
    gl_Position = gl_in[1].gl_Position; 
    g_out.normals = triangleNormal;
    g_out.postion = v_out[1].postion;
    g_out.world_pos = v_out[1].world_pos;
    g_out.barycentricCoordinates = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position; 
    g_out.normals = triangleNormal;
    g_out.postion = v_out[2].postion;
    g_out.world_pos = v_out[2].world_pos;
    g_out.barycentricCoordinates = vec2(0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}  

#type fragment
#version 450 core
layout(location = 0) out vec4 fragColor;
vec4 ambient_diffuse_specular(vec3 world_pos, vec3 light_pos, vec3 normal);

struct GeometryOut
{
    vec3 normals;
    vec3 postion;
    vec3 world_pos;
    vec2 barycentricCoordinates;
};

in GeometryOut g_out;

uniform vec4 u_Color;
uniform vec3 u_WireframeColor;
uniform float u_WireframeSmoothing;
uniform float u_WireframeThickness;

void main()
{
    vec3 light_pos = vec3(0.0, 10.0, 2.0);
    
    vec4 color = u_Color;
    
    vec3 barys;
	barys.xy = g_out.barycentricCoordinates;
	barys.z = 1 - barys.x - barys.y;
    
    vec3 deltas = fwidth(barys);
    vec3 smoothing = deltas * u_WireframeSmoothing;
	vec3 thickness = deltas * u_WireframeThickness;
    
    barys = smoothstep(thickness, thickness + smoothing, barys);
    float minBary = min(barys.x, min(barys.y, barys.z));
    
    fragColor = mix(vec4(u_WireframeColor, 1.0), color, minBary);  
};

vec4 ambient_diffuse_specular(vec3 world_pos, vec3 light_pos, vec3 normal)
{	
    vec3 color = vec3(.5, .5, .5);
    vec3 to_light = normalize (light_pos - world_pos);
	vec3 to_eye = normalize (-world_pos);
	vec3 R = reflect (-light_pos, normal);

    vec3 ambient = color;
	
    float cos_theta = max(dot(to_light, normal), 0.0);
    vec3 diffuse = color * cos_theta;

    float cos_phi = pow(max (dot(R, to_eye), 0.0), 1); 
    vec3 specular = cos_phi * color;
	
    if(dot(light_pos, normal) < 0.0)
		specular = vec3(0.0, 0.0, 0.0);

    return vec4(ambient + diffuse + specular, 1.0);
}