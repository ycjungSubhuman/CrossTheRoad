#version 400

in vec4 color_out;
in vec2 st;
in vec3 t_fL1;
in vec3 t_fL2;
in vec3 t_fE;
in vec3 fN;
in vec3 fE;
in vec3 fL1;
in vec3 fL2;
in vec3 eyeDirection;

uniform sampler2D sample_texture; //unit 0
uniform sampler2D sample_normalmap; //unit 1
uniform samplerCube sample_cube; //unit 2
uniform bool isTextured; //if true, render with color_out
uniform bool isNormaled;
uniform bool isSkyBox;
uniform int mode_shader;
out vec3 color;

void main()
{
	/* shader for debug...
	 * samples a specific point in texture image.(no practical use)
	 * replace it with 
	 * color = texture (sample_texture, UV).rgb;
	 * where UV is "in vec2""
	 */
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	vec3 L1 = normalize(fL1);
	vec3 L2 = normalize(fL2);
	vec4 product = vec4(0.4,0.4,0.4,1.0);

	vec4 ambient = product;

	float Kd1 = max(dot(L1, N), 0.0);
	vec4 diffuse1 = Kd1*product;
	float Kd2 = max(dot(L2, N), 0.0);
	vec4 diffuse2 = Kd2*product;

	vec4 specular1, specular2;
	if(mode_shader == 2)
	{
		vec3 R1 = normalize( reflect(L1, N) );
		vec3 R2 = normalize( reflect(L2, N) );
		float Ks1 = pow(max(dot(R1, E), 0.0), 0.3);
		specular1 = Ks1*product;
		float Ks2 = pow(max(dot(R2, E), 0.0), 0.3);
		specular2 = Ks2*product;
	}
	else if(mode_shader == 3)
	{
		vec3 H1 = normalize( L1 + E ); 
		vec3 H2 = normalize( L2 + E ); 
		float Ks1 = pow(max(dot(N, H1), 0.0), 0.3);
		specular1 = Ks1*product;
		float Ks2 = pow(max(dot(N, H2), 0.0), 0.3);
		specular2 = Ks2*product;
	}

	vec4 lightcolor = ambient + diffuse1 + diffuse2 + specular1 + specular2;

	if (isSkyBox) {
		//render skybox
		color = texture ( sample_cube, eyeDirection ).rgb;
	}
	else if (isTextured) {
		if (isNormaled) { //shading with normal map
			vec3 normal_map = normalize( 
				texture (sample_normalmap, st).rgb * 2.0  - 1.0);

			/* TODO: implement shading with
				* normal_map for surface normal
				* t_fL1, t_fL2
					for light direction
				* t_fE
					for eye direction
			vec3 FL1 = t_fL1;
			vec3 FL2 = t_fL2;
			vec3 FE = t_fE;

			vec3 H1 = FL1 + FE; 
			vec3 H2 = FL2 + FE; 
			float Ks1 = pow(max(dot(normal_map, H1), 0.0), 0.3);
			specular1 = Ks1*product;
			float Ks2 = pow(max(dot(normal_map, H2), 0.0), 0.3);
			specular2 = Ks2*product;*/
			//lightcolor = specular1 + specular2;
			//placeholder
			color = texture (sample_texture, st).rgb * lightcolor.xyz;	
		}
		else {
			color = texture (sample_texture, st).rgb * lightcolor.xyz;
		}
	}
	else {
		color = color_out.xyz;
	}
}
