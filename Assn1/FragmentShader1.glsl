#version 400

in vec4 color_out;
in vec2 st;
uniform sampler2D sample_texture; //unit 0
uniform sampler2D sample_normalmap; //unit 1
uniform bool isTextured; //if true, render with color_out
uniform bool isNormaled;
out vec3 color;

void main()
{
	/* shader for debug...
	 * samples a specific point in texture image.(no practical use)
	 * replace it with 
	 * color = texture (sample_texture, UV).rgb;
	 * where UV is "in vec2""
	 */
	if (isTextured) {
		if (isNormaled) {
			//vec3 normal = 2 * texture (sample_normalmap, UV).rbg - vec3(1, 1, 1);
			color = texture (sample_texture, st).rgb ;

		}
		else {
			color = texture (sample_texture, st).rgb ;
		}
	}
	else {
		color = color_out.xyz;
	}
}
