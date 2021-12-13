#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

// Some of this class was provided from an OpenGL tutorial
// https://youtu.be/45MIykWJ-C4


#include "shaderClass.h"


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	bool firstClick = true;
	bool onGround = false;

	int width;
	int height;

	float speed = .01f;
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 position);

	void Matrix(Shader& shader, const char* uniform);
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Inputs(GLFWwindow* window);
};

#endif /* CAMERA_CLASS_H */