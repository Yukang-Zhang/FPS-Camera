#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#include<tuple>

class GroundCamera
{
public:
	GroundCamera()
	{
		view = glm::mat4(1.0f);
		view1 = glm::mat4(1.0f);
		pitchAngle = 0.0f;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
		orientation = glm::vec3(0, 0, -1);

		view1 = glm::translate(view1, glm::vec3(0.0f, -1.0f, 0.0f));
	}

	glm::mat4 getView()
	{
		return view * view1;
	}

	glm::mat4 getProjection()
	{
		return projection;
	}

	void turnLeft(float speed)
	{
		view = glm::rotate(view, glm::radians(-speed), glm::vec3(0.0f, 1.0f, 0.0f));
		orientation = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(speed), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(orientation, 0.0f));
	}

	void turnRight(float speed)
	{
		view = glm::rotate(view, glm::radians(speed), glm::vec3(0.0f, 1.0f, 0.0f));
		orientation = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(-speed), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(orientation, 0.0f));
	}

	void lookUp(float speed)
	{
		if(speed > 0) {
			float pitchAmount = std::min(speed,89.9999f - pitchAngle);
			view = glm::rotate(view,glm::radians(pitchAmount),glm::cross(glm::vec3(glm::vec4(0.0f,0.0f,1.0f,0.0f) * view),glm::vec3(0.0f,1.0f,0.0f)));
			pitchAngle += pitchAmount;
		} else {
			float pitchAmount = std::max(speed, -89.9999f - pitchAngle);
			view = glm::rotate(view, glm::radians(-pitchAmount), glm::cross(glm::vec3(glm::vec4(0.0f, 0.0f, -1.0f, 0.0f) * view), glm::vec3(0.0f, 1.0f, 0.0f)));
			pitchAngle += pitchAmount;
		}
	}

	void lookDown(float speed)
	{
		
	}

	void moveForward(float speed)
	{
		view1 = glm::translate(view1, orientation * -speed);
	}

	void moveBack(float speed)
	{
		view1 = glm::translate(view1, orientation * speed);
	}

	void moveLeft(float speed)
	{
		view1 = glm::translate(view1, glm::cross(orientation, glm::vec3(0.0f, 1.0f, 0.0f)) * speed);
	}

	void moveRight(float speed)
	{
		view1 = glm::translate(view1, glm::cross(orientation, glm::vec3(0.0f, -1.0f, 0.0f)) * speed);
	}

	void rise(float speed)
	{
		view1 = glm::translate(view1, glm::vec3(0.0f, -1.0f, 0.0f) * speed);
	}

	void fall(float speed)
	{
		view1 = glm::translate(view1, glm::vec3(0.0f, 1.0f, 0.0f) * speed);
	}

	std::tuple<float, float, float> getPosition()
	{
		glm::vec3 cameraPos = glm::vec3(glm::inverse(view1)[3]);
		return std::make_tuple(cameraPos.x, cameraPos.y, cameraPos.z);
	}

private:
	glm::mat4 view;
	glm::mat4 view1;
	float pitchAngle;
	glm::vec3 orientation;
	glm::mat4 projection;
};


#endif