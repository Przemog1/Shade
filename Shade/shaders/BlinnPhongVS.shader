#version 450 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_tex_uv;
layout(location = 2) in vec3 v_normals;

out vec2 f_texCoords;
out vec3 f_cameraSpaceNormal;
out vec3 f_cameraSpaceFragPos;
out vec3 f_cameraSpaceLightPos;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;
uniform mat4 perspectiveMatrix;

uniform vec3 worldSpaceCameraPos;

void main()
{
	f_texCoords = v_tex_uv;
	gl_Position = perspectiveMatrix * cameraMatrix * modelMatrix * vec4(v_position, 1.0);

	f_cameraSpaceNormal = vec3(cameraMatrix * modelMatrix * vec4(v_normals,0.0));
	f_cameraSpaceFragPos = vec3(cameraMatrix * modelMatrix * vec4(v_position, 1.0));
	f_cameraSpaceLightPos = vec3(cameraMatrix * vec4(worldSpaceCameraPos, 1.0));
}