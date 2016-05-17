#version 400

out vec4 color_out;
out vec2 st;

out vec3 lightdirection_tangentspace; //use this for calculating normal map shading
out vec3 eyedirection_tangentspace; //use this for calculating normal map shading

out vec3 fN;
out vec3 fE;
out vec3 fL1;
out vec3 fL2;

out int shnum;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform int mode_shader;
uniform vec3 LightPosition1;
uniform vec3 LightPosition2;
uniform int light_point;
uniform mat4 M;
uniform mat4 V;
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 facenorm;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bitangent;
uniform vec4 color_in;
const vec4 err = vec4(1.0, 0, 0, 1.0);
const vec4 goo = vec4(0, 1.0, 0, 1.0);
void main(void)
{
	//normal and tangent/bitangent
	vec3 T = mat3(u_Model) * normalize(tangent);
	vec3 B = mat3(u_Model) * normalize(bitangent);
	vec3 N = mat3(u_Model) * normalize(normal);

	fN = (u_Model * vec4(normal,0)).xyz;
	fE = (u_Model * vec4(position,1)).xyz;
	fL1 = (V * vec4(LightPosition1,1)).xyz;
	fL2 = (V * vec4(LightPosition2,1)).xyz;
	shnum = mode_shader;

	if(light_point == 1)
	{
		fL1 = LightPosition1 - position;
		fL2 = LightPosition2 - position;
	}
	if(mode_shader == 1)
	{
		fN = (u_Model * vec4(facenorm,0)).xyz;
	}

	//a matrix that converts from camera space to tangent space
	mat3 TBN = transpose(mat3(T,B,N));

	//TODO: uncomment after loading light/eye directions
	//lightdirection_tangentspace = TBN * u_Model * lightdirection;
	//eyedirection_tangentspace = TBN * u_Model * eyedirection;

	gl_Position = u_Projection * u_Model * vec4(position, 1.0);
	color_out = color_in;
	st = texture;
}
