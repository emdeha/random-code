#include "stdafx.h"
#include "Spaceship.h"


Spaceship::Spaceship(glm::vec3 newForwardVector, glm::vec3 newRightVector, glm::vec3 newUpVector,
					 glm::vec3 newMaxSpeed)
{
	forwardVector = newForwardVector;
	rightVector = newRightVector;
	upVector = newUpVector;
	maxSpeed = newMaxSpeed;
	currentSpeed = glm::vec3();
	acceleration = glm::vec3();
	velocity = glm::vec3();
	position = glm::vec3();
	steerAngle = 0.0f;	
}

void Spaceship::InitMesh(const std::string &meshFileName)
{
	try
	{
		mesh = std::unique_ptr<Framework::Mesh>(new Framework::Mesh(meshFileName));
	}
	catch(std::exception &except)
	{
		std::printf(except.what());
		throw;
	}
	/*
	btBoxShape *collisionShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
	btScalar mass = 1.0f;

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(position.x, position.y, position.z));
	btDefaultMotionState *motionState = new btDefaultMotionState(transform);
	btVector3 localInertia = btVector3(0, 0, 0);
	//collisionShape->calculateLocalInertia(mass, localInertia);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, collisionShape, localInertia);

	body = new btRigidBody(info);*/
}

void Spaceship::Update(float deltaTime)
{
	glm::vec3 lateralVelocity = rightVector * glm::dot(velocity, rightVector);
	float lateralFrictionFactor = 0.0001f;
	glm::vec3 lateralFriction = -lateralVelocity * lateralFrictionFactor;

	float backwardsFrictionFactor = 0.00001f;
	glm::vec3 backwardsFriction = -velocity * backwardsFrictionFactor;

	velocity += (backwardsFriction + lateralFriction) * deltaTime;
	
	//currentSpeed = glm::normalize(velocity);
	//if(currentSpeed < maxSpeed)
	//{
		velocity += acceleration * deltaTime;
	//}
/*
	btTransform bodyTransform;
	bodyTransform.setOrigin(btVector3(position.x, position.y, position.z));
	//body->getMotionState()->setWorldTransform(bodyTransform);*/
	position += velocity * deltaTime;
}
void Spaceship::Render(glutil::MatrixStack &modelMatrix, const SimpleProgram &program)
{
	glUseProgram(program.theProgram);
	{
		glutil::PushStack push(modelMatrix);
	
		modelMatrix.Translate(position);
		modelMatrix.Rotate(forwardVector, steerAngle);
		modelMatrix.Scale(0.5f);
		
		glUniformMatrix4fv(program.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(program.colorUnif, 0.21f, 0.42f, 0.34f, 1.0f);

		mesh->Render("flat");
	}
	glUseProgram(0);
}

void Spaceship::Steer(float deltaTime, float steerFactor, float steerInput)
{
	steerAngle = steerInput * steerFactor;
	/*glutil::MatrixStack transform;
	transform.Rotate(upVector, -steerAngle);
	glm::vec3 newForwardVector = forwardVector;
	newForwardVector = glm::mat3(transform.Top()) * newForwardVector;
	forwardVector = glm::normalize(newForwardVector);
	*/

	// lerping for keyboard. remove if leap.
	/*
	float steerLerpFactor = 0.001f;
	float amount = deltaTime * steerLerpFactor;
	forwardVector = glm::mix(forwardVector, newForwardVector, amount);
	forwardVector = glm::normalize(forwardVector);*/
}
void Spaceship::Move(float deltaTime, float accelerationFactor, float accelerationInput)
{
	acceleration = forwardVector * accelerationInput * accelerationFactor;
}

glm::vec3 Spaceship::GetPosition()
{
	return position;
}
float Spaceship::GetSteerAngle()
{
	return steerAngle;
}
/*
btRigidBody *Spaceship::GetRigidBody()
{
	return body;
}*/