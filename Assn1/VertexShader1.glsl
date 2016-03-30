const vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
varying vec4 color_out;

void main(void)
{
	gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
	color_out = red;
}
