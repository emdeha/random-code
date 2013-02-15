#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <glload/gl_3_3.h>
#include <glm/glm.hpp>
#include <glutil/MatrixStack.h>
#include "../framework/framework.h"
#include "../framework/Mesh.h"
#include "../ProgramData/ProgramData.h"
#include "../bullet-physics/header/btBulletDynamicsCommon.h"


class Spaceship
{
private:
	glm::vec3 forwardVector;
	glm::vec3 rightVector;
	glm::vec3 upVector;

	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 position;
	glm::vec3 maxSpeed;
	glm::vec3 currentSpeed;
	
	//btRigidBody *body;

	float steerAngle;

	std::unique_ptr<Framework::Mesh> mesh;

public:
	Spaceship() {}
	Spaceship(glm::vec3 newForwardVector, glm::vec3 newRightVector, glm::vec3 newUpVector,
			  glm::vec3 newMaxSpeed);

	void InitMesh(const std::string &meshFileName);

	void Update(float deltaTime);
	void Render(glutil::MatrixStack &modelMatrix, const SimpleProgram &program);

	void Steer(float deltaTime, float steerFactor, float steerInput);
	void Move(float deltaTime, float accelerationFactor, float accelerationInput);

	glm::vec3 GetPosition();
	float GetSteerAngle();

	//btRigidBody *GetRigidBody();
};


#endif