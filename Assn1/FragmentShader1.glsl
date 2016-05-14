#version 400

in vec4 color_out;
uniform sampler2D sample_texture; //unit 0
out vec3 color;

void main()
{
	color = texture (sample_texture, vec2(0.5f,0.5f)).rgb ;
}
