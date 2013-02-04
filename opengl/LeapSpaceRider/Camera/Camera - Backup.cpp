#include "stdafx.h"
#include "Camera.h"

float DegToRad(float angle_degs)
{
	const float fDegToRad = 3.14159f * 2.0f / 360.0f;
	return angle_degs * fDegToRad;
}

Camera::Camera()
{
	camTarget = glm::vec3();
	sphereCamRelPos = glm::vec3();
	camPos = ResolveCamPosition();

	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	forwardVector = glm::vec3(0.0f, 0.0f, 1.0f);
}
Camera::Camera(glm::vec3 newCamTarget, glm::vec3 newSphereCamRelPos)
{
	camTarget = newCamTarget;
	sphereCamRelPos = newSphereCamRelPos;
	camPos = ResolveCamPosition();

	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	forwardVector = glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 Camera::ResolveCamPosition()
{
	float phi = DegToRad(sphereCamRelPos.x);
	float theta = DegToRad(sphereCamRelPos.y + 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosPhi = cosf(phi);
	float fSinPhi = sinf(phi);

	glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
	return (dirToCamera * sphereCamRelPos.z) + camTarget;
}

glm::mat4 Camera::CalcLookAtMatrix()
{
	glm::vec3 lookDir = glm::normalize(camTarget - camPos);
	glm::vec3 upDir = glm::normalize(glm::vec3(upVector));

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f);

	rotMat = glm::transpose(rotMat);

	glm::mat4 transMat(1.0f);
	transMat[3] = glm::vec4(-camPos, 1.0f);

	return rotMat * transMat;
}

void Camera::LookDown(float angle_degs)
{
	sphereCamRelPos.y += angle_degs;
	sphereCamRelPos.y = glm::clamp(sphereCamRelPos.y, -78.75f, -1.0f);
	camPos = ResolveCamPosition();
}
void Camera::LookUp(float angle_degs)
{
	sphereCamRelPos.y += angle_degs;
	sphereCamRelPos.y = glm::clamp(sphereCamRelPos.y, -78.75f, -1.0f);
	camPos = ResolveCamPosition();
}
void Camera::LookLeft(float angle_degs)
{
	sphereCamRelPos.x += angle_degs;
	camPos = ResolveCamPosition();
}
void Camera::LookRight(float angle_degs)
{
	sphereCamRelPos.x += angle_degs;
	camPos = ResolveCamPosition();
}

void Camera::MoveForward(float units)
{
	glm::vec3 forwardVector(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::normalize(forwardVector);

	camTarget += units * forwardVector;
	camPos = ResolveCamPosition();
}
void Camera::MoveBackward(float units)
{
	glm::vec3 forwardVector(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::normalize(forwardVector);

	camTarget -= units * forwardVector;
	camPos = ResolveCamPosition();
}
void Camera::MoveLeft(float units)
{
	glm::vec3 forwardVector(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::vec3 rightVector = glm::cross(forwardVector, upVector);
	glm::normalize(rightVector);

	camTarget -= units * rightVector;
	camPos = ResolveCamPosition();
}
void Camera::MoveRight(float units)
{
	glm::vec3 forwardVector(camTarget.x - camPos.x, 0.0f, camTarget.z - camPos.z);
	glm::vec3 rightVector = glm::cross(forwardVector, upVector);
	glm::normalize(rightVector);

	camTarget += units * rightVector;
	camPos = ResolveCamPosition();
}

/*#define PI 3.14159265f


void Camera::RotateAroundX(glm::vec3 &vect, float angle_degs)
{
	double alpha = angle_degs * PI/180;
	float newY = vect.y * cos(alpha) - vect.z * sin(alpha);
	float newZ = vect.y * sin(alpha) + vect.z * cos(alpha);
	vect.y = newY;
	vect.z = newZ;
}
void Camera::RotateAroundY(glm::vec3 &vect, float angle_degs)
{
	double alpha = angle_degs * PI/180;
	float newZ = vect.z * cos(alpha) - vect.x * sin(alpha);
	float newX = vect.z * sin(alpha) + vect.x * cos(alpha);
	vect.z = newZ;
	vect.x = newX;
}
void Camera::RotateAroundZ(glm::vec3 &vect, float angle_degs)
{
	float alpha = angle_degs * PI/180;
	float newX = vect.x * cos(alpha) - vect.y * sin(alpha);
	float newY = vect.x * sin(alpha) + vect.y * cos(alpha);
	vect.y = newY;
	vect.x = newX;
}


Camera::Camera()
{
	currentCameraPosition = glm::vec3();
	eulerRotation_degs = glm::vec3();

	forwardVector = glm::vec3(0.0f, 0.0f, -1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
}

void Camera::SetPosition(glm::vec3 newPosition)
{
	currentCameraPosition = newPosition;
}

void Camera::SetRotation(glm::vec3 newEulerRotation_degs)
{
	eulerRotation_degs = newEulerRotation_degs;
	if(eulerRotation_degs.x > 90.0f)
	{
		eulerRotation_degs.x = 90.0f;
	}
	else if(eulerRotation_degs.x < -90.0f)
	{
		eulerRotation_degs.x = -90.0f;
	}

	glm::vec3 newForwardVector(0.0f, 0.0f, -1.0f);
	glm::vec3 newUpVector(0.0f, 1.0f, 0.0f);
	glm::vec3 newRightVector(1.0f, 0.0f, 0.0f);

	RotateAroundX(newForwardVector, eulerRotation_degs.x);
	RotateAroundY(newForwardVector, eulerRotation_degs.y);
	RotateAroundZ(newForwardVector, eulerRotation_degs.z);

	RotateAroundX(newUpVector, eulerRotation_degs.x);
	RotateAroundY(newUpVector, eulerRotation_degs.y);
	RotateAroundZ(newUpVector, eulerRotation_degs.z);

	RotateAroundX(newRightVector, eulerRotation_degs.x);
	RotateAroundY(newRightVector, eulerRotation_degs.y);
	RotateAroundZ(newRightVector, eulerRotation_degs.z);

	glm::normalize(newForwardVector);
	glm::normalize(newUpVector);
	glm::normalize(newRightVector);

	forwardVector = newForwardVector;
	upVector = newUpVector;
	rightVector = newRightVector;
}

/*void Camera::ApplyLook(glutil::MatrixStack camMatrix)
{
	camMatrix.RotateX(eulerRotation_degs.x);
	camMatrix.RotateY(eulerRotation_degs.y);
	camMatrix.RotateZ(eulerRotation_degs.z);

	camMatrix.Translate(currentCameraPosition);
}*/

/*void Camera::MoveForward(float units)
{
	currentCameraPosition += forwardVector * units;
}
void Camera::MoveRight(float units)
{
	currentCameraPosition += rightVector * units;
}
void Camera::MoveUp(float units)
{
	currentCameraPosition += upVector * units;
}

void Camera::LookRight(float angle_degs)
{
	glm::vec3 newRotation = eulerRotation_degs;
	newRotation.y += angle_degs;
	SetRotation(newRotation);
}
void Camera::LookLeft(float angle_degs)
{
	glm::vec3 newRotation = eulerRotation_degs;
	newRotation.y -= angle_degs;
	SetRotation(newRotation);
}
void Camera::LookUp(float angle_degs)
{
	glm::vec3 newRotation = eulerRotation_degs;
	newRotation.x -= fabs(angle_degs);
	SetRotation(newRotation);
}
void Camera::LookDown(float angle_degs)
{
	glm::vec3 newRotation = eulerRotation_degs;
	newRotation.x += fabs(angle_degs);
	SetRotation(newRotation);
}*/