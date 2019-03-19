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
	vec3 lightAmbientStr  = vec3(0.05);
	vec3 lightSpecularStr = vec3(0.2);

		//attenuation
	float fragLightDiscance = length(f_cameraSpaceLightPos - f_cameraSpaceFragPos);
	float attenuation = 1.0 / (1.0 + 0.09 * fragLightDiscance + 0.032 * fragLightDiscance * fragLightDiscance);

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

		//ambient
	ambient = vec3(texture(tex_d, f_texCoords)) * lightAmbientStr;

		//diffuse
	vec3 fragToLight = normalize(vec3(f_cameraSpaceLightPos - f_cameraSpaceFragPos));
	float diffuseScalar = max(dot(normalize(f_cameraSpaceNormal), fragToLight), 0.0);

	diffuse = vec3(texture(tex_d, f_texCoords)) * diffuseScalar;

		//specular
	vec3 fragToEye = normalize(-f_cameraSpaceFragPos);
	vec3 fragToLightReflection = reflect(-fragToLight, f_cameraSpaceNormal);

	float specularScalar = pow(max(dot(fragToEye, fragToLightReflection), 0.0), 64);

	specular = specularScalar * lightSpecularStr * vec3(texture(tex_s, f_texCoords));

		//output
	outputColor = vec4(diffuse + ambient + specular, 0.0) * attenuation;
	outputColor.w = 1.0;
}