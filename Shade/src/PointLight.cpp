//#include "PointLight.h"
//#include <string>
//
//#include <iostream>
//
//void PointLight::addToShader(Shader* shader, int lightIndex) const
//{
//	std::string lightUniformName = "lights[" + std::to_string(lightIndex) + "].";
//
//	shader->uniform3f(lightUniformName + "position", pos);
//	shader->uniform3f(lightUniformName + "ambientColor", ambientColor);
//	shader->uniform3f(lightUniformName + "diffuseColor", diffuseColor);
//	shader->uniform3f(lightUniformName + "specularColor", specularColor);
//}