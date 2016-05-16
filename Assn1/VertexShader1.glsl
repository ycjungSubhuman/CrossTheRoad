#version 400

out vec4 color_out;
out vec2 st;

out vec3 lightdirection_tangentspace; //use this for calculating normal map shading
out vec3 eyedirection_tangentspace; //use this for calculating normal map shading

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform int mode_shader;
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

	//a matrix that converts from camera space to tangent space
	mat3 TBN = transpose(mat3(T,B,N));

	//TODO: uncomment after loading light/eye directions
	//lightdirection_tangentspace = TBN * u_Model * lightdirection;
	//eyedirection_tangentspace = TBN * u_Model * eyedirection;

	gl_Position = u_Projection * u_Model * vec4(position, 1.0);
	color_out = color_in;
	st = texture;
}
