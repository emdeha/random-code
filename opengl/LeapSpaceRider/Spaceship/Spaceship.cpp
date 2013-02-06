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
}

void Spaceship::Update(float deltaTime)
{

}
void Spaceship::Render(glutil::MatrixStack &modelMatrix, const SimpleProgram &program)
{
	glUseProgram(program.theProgram);
	{
		glutil::PushStack push(modelMatrix);
	
		modelMatrix.Translate(glm::vec3());
		modelMatrix.Scale(0.5f);
		
		glUniformMatrix4fv(program.modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
		glUniform4f(program.colorUnif, 0.21f, 0.42f, 0.34f, 1.0f);

		mesh->Render("flat");
	}
	glUseProgram(0);
}

void Spaceship::Steer(float steerFactor)
{

}
void Spaceship::Move(float accelerationFactor)
{

}