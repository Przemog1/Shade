#version 450 core

in vec2 f_texCoords;
in vec3 f_cameraSpaceFragPos;
in vec3 f_cameraSpaceNormal;
in vec3 f_cameraSpaceLightPos;

out vec4 outputColor;

uniform sampler2D tex_d;
uniform sampler2D tex_s;

void main()
{
		//light
	vec3 lightAmbientStr	= vec3(0.001);
	vec3 lightSpecularStr	= vec3(0.000);
	vec3 lightColor = vec3(1.0);//vec3(255.0 / 255.0, 252.0f / 255.0, 193.0 / 255.0);


		//attenuation
	float fragLightDiscance = length(f_cameraSpaceLightPos - f_cameraSpaceFragPos);
	float attenuation = 1.0 / (fragLightDiscance * fragLightDiscance); //1.0 + 0.09 * fragLightDiscance + 0.032 * fragLightDiscance * fragLightDiscance

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

		//ambient
	ambient = pow(vec3(texture(tex_d, f_texCoords)), vec3(2.2)) * lightAmbientStr;

		//diffuse
	vec3 fragToLight = normalize(vec3(f_cameraSpaceLightPos - f_cameraSpaceFragPos));
	float diffuseScalar = max(dot(normalize(f_cameraSpaceNormal), fragToLight), 0.0);

	diffuse = pow(vec3(texture(tex_d, f_texCoords)), vec3(2.2)) * diffuseScalar * vec3(0.5);

		//specular
	vec3 fragToEye = normalize(-f_cameraSpaceFragPos);
	vec3 fragToLightReflection = reflect(-fragToLight, f_cameraSpaceNormal);

	float specularScalar = pow(max(dot(fragToEye, fragToLightReflection), 0.0), 16);

	specular = specularScalar * lightSpecularStr * pow(vec3(texture(tex_s, f_texCoords)), vec3(2.2));

		//output
	outputColor = vec4(diffuse + ambient + specular, 0.0) * attenuation * vec4(lightColor, 0.0);
	outputColor.rgb = pow(outputColor.rgb, vec3(1.0/2.2));
	outputColor.w = 1.0;
}