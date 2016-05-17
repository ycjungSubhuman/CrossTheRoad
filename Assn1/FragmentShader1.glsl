#version 400

in vec4 color_out;
in vec2 st;
in vec3 lightdirection_tangentspace;
in vec3 eyedirection_tangentspace;
in vec3 eyeDirection;

uniform sampler2D sample_texture; //unit 0
uniform sampler2D sample_normalmap; //unit 1
uniform samplerCube sample_cube; //unit 2
uniform bool isTextured; //if true, render with color_out
uniform bool isNormaled;
uniform bool isSkyBox;
out vec3 color;

void main()
{
	/* shader for debug...
	 * samples a specific point in texture image.(no practical use)
	 * replace it with 
	 * color = texture (sample_texture, UV).rgb;
	 * where UV is "in vec2""
	 */
	if (isSkyBox) {
		//render skybox
		color = texture ( sample_cube, eyeDirection ).rgb;
	}
	else if (isTextured) {
		if (isNormaled) { //shading with normal map
			vec3 normal_map = normalize( 
				texture (sample_normalmap, st).rgb * 2.0 
				-1.0);

			/* TODO: implement shading with
				* normal_map for surface normal
				* lightdirection_tangentspace 
					for light direction
				* eyedirection_tangentspace
					for eye direction
			*/

			//placeholder
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
