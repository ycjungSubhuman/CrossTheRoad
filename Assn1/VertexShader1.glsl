const vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
out vec4 color_out;
uniform mat4 u_Projection;
uniform mat4 u_Model;
in vec3 position;
void main(void)
{
	gl_Position = u_Projection * u_Model * vec4(position, 1.0);
	color_out = red;
}
