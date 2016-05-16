#version 400

out vec4 color_out;
out vec2 st;
uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform int mode_shader;
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 facenorm;
uniform vec4 color_in;
const vec4 err = vec4(1.0, 0, 0, 1.0);
const vec4 goo = vec4(0, 1.0, 0, 1.0);
void main(void)
{
	gl_Position = u_Projection * u_Model * vec4(position, 1.0);
	color_out = color_in;
	st = texture;
}
