#include "camera.h"
Camera::Camera()
{
	renew();
	firstmouse = true;
}

Camera::Camera(glm::vec3 position, glm::vec3 worldup, float yaw = YAW, float pitch = PITCH){
	this->pos = position;
	this->worldup = worldup;
	this->yaw = yaw;
	this->pitch = pitch;
	firstmouse = true;
	renew();
}

Camera::~Camera()
{
}

void Camera::renew()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldup));
	up = glm::normalize(glm::cross(this->right, this->front));
}

glm::mat4 Camera::get_view()
{
	return glm::lookAt(this->pos, pos + front, up);
}

glm::mat4 Camera::get_projection(float ratio = 800.0f / 600.0f, float rear = 0.1f, float far_dis = 1000.0f) {
	return glm::perspective(glm::radians(zoom), ratio, rear, far_dis);
}

void Camera::onKeyBoard(char key, float t) {
	switch (key)
	{
	case 'W':
		pos += front*speed*t;
		break;
	case 'S':
		pos -= front*speed*t;
		break;
	case 'A':
		pos -= right*speed*t;
		break;
	case 'D':
		pos += right*speed*t;
	default:
		break;
	}
}

void Camera::onMouseMove(int xpos, int ypos) {
	if (firstmouse) {
		lastx = xpos;
		lasty = ypos;
		firstmouse = false;
	}
	double xoffset;
	double yoffset;
	xoffset = xpos - lastx;
	yoffset = lasty - ypos;
	lastx = xpos;
	lasty = ypos;
	xoffset *= sensitivty;
	yoffset *= sensitivty;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0)
		pitch = 89.0;
	if (pitch < -89.0)
		pitch = -89.0;
	renew();
}

void Camera::onMouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

glm::vec3 Camera::get_front() {
	return this->front;
}