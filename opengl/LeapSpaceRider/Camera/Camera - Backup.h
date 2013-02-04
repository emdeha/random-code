#ifdef CAMERA_EXPORTS
#define CAMERA_API __declspec(dllexport)
#else
#define CAMERA_API __declspec(dllimport)
#endif

#include <glm\glm.hpp>

#pragma warning(disable : 4251)

class CAMERA_API Camera
{
private:
	glm::vec3 camTarget;
	glm::vec3 camPos;
	glm::vec3 sphereCamRelPos;

	glm::vec3 forwardVector;
	glm::vec3 upVector;

public:
	Camera();
	Camera(glm::vec3 newCamTarget, glm::vec3 newSphereCamRelPos);

	glm::vec3 ResolveCamPosition();
	glm::mat4 CalcLookAtMatrix();

	void LookLeft(float angle_degs);
	void LookRight(float angle_degs);
	void LookUp(float angle_degs);
	void LookDown(float angle_degs);

	void MoveForward(float units);
	void MoveBackward(float units);
	void MoveLeft(float units);
	void MoveRight(float units);
};

// Camera class, made with Euler angles. Not good. 
// Quaternions will be introduced soon.
/*class CAMERA_API Camera
{
private:
	glm::vec3 currentCameraPosition;
	glm::vec3 upVector, rightVector, forwardVector;
	glm::vec3 eulerRotation_degs;

	void RotateAroundX(glm::vec3 &vect, float angle_degs);
	void RotateAroundY(glm::vec3 &vect, float angle_degs);
	void RotateAroundZ(glm::vec3 &vect, float angle_degs);

public:
	Camera();
	void SetPosition(glm::vec3 newPosition);
	void SetRotation(glm::vec3 newEulerRotation_degs);

	glm::vec3 GetPosition()
	{
		return currentCameraPosition;
	}
	glm::vec3 GetRotation()
	{
		return eulerRotation_degs;
	}

	//void ApplyLook(glutil::MatrixStack camMatrix);

	void MoveForward(float units);
	void MoveRight(float units);
	void MoveUp(float units);

	void LookRight(float angle_degs);
	void LookLeft(float angle_degs);
	void LookUp(float angle_degs);
	void LookDown(float angle_degs);
};*/