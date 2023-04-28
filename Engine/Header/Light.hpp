#pragma once

// OpenGL Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light();
	glm::vec3 Color;
	float intensity;

private:

};

class PointLight : public Light
{
public:
	PointLight(){};

private:
	glm::vec3 Position;
	float radius;
	float attenuation;
};