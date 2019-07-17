#version 450 core

in vec2 f_texCoords;
in vec3 f_worldSpaceFragPos;
in vec3 f_worldSpaceNormal;

out vec4 outputColor;

uniform sampler2D tex_d;
uniform sampler2D tex_s;

struct PointLight
{
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

layout(std430, binding = 0) readonly buffer PointLightBuffer
{
	uint lightCount;
	PointLight lights[];
};

void main()
{
	//TODO: fix (lighting calculations are no longer done in camera space)
	vec3 fragToEye = normalize(-f_worldSpaceFragPos);

	vec3 fragColor = vec3(0.0);

		//lighting calculations
	for(int i = 0; i < lightCount; i++)
	{
			//attenuation
		float fragLightDiscance = length(lights[i].position - f_worldSpaceFragPos);
		float attenuation = 1.0 / (fragLightDiscance * fragLightDiscance);

			//ambient
		vec3 ambient = pow(vec3(texture(tex_d, f_texCoords)), vec3(2.2)) * lights[i].ambientColor;

			//diffuse
		vec3 fragToLight = normalize(lights[i].position - f_worldSpaceFragPos);
		float diffuseScalar = max(dot(normalize(f_worldSpaceNormal), fragToLight), 0.0);

		vec3 diffuse = pow(vec3(texture(tex_d, f_texCoords)), vec3(2.2)) * diffuseScalar;

			//specular
		vec3 fragToLightReflection = reflect(-fragToLight, f_worldSpaceNormal);
		float specularScalar = pow(max(dot(fragToEye, fragToLightReflection), 0.0), 16);
		vec3 specular = specularScalar * lights[i].specularColor * pow(vec3(texture(tex_s, f_texCoords)), vec3(2.2));

		fragColor += (diffuse + ambient + specular) * attenuation * lights[i].diffuseColor;
	}
	
	outputColor.rgb = pow(fragColor, vec3(1.0/2.2));
	outputColor.w = 1.0;
}