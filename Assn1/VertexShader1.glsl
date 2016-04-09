out vec4 color_out;
uniform mat4 u_Projection;
uniform mat4 u_Model;
in vec3 position;
in vec4 color_in;
void main(void)
{
	gl_Position = u_Projection * u_Model * vec4(position, 1.0);
	color_out = color_in;
}
