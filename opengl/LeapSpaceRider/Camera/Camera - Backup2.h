#ifdef CAMERA_EXPORTS
#define CAMERA_API __declspec(dllexport)
#else
#define CAMERA_API __declspec(dllimport)
#endif

#include <glm\glm.hpp>

#include "../Collision/Collision.h"

class CAMERA_API Camera
{	
private:
	glm::vec3 camTarget;	
	glm::vec3 sphereCamRelPos;

	glm::vec3 camPos;

	glm::vec3 upVector;

	glm::vec3 ResolveCamPosition();

public:
	Camera();
	Camera(glm::vec3 newCamTarget, glm::vec3 newSphereCamRelPos);

	glm::mat4 CalcLookAtMatrix();

	glm::vec3 GetPosition();
	glm::vec3 GetVelocity();

	void LookLeft(float angle_degs);
	void LookRight(float angle_degs);
	void LookUp(float angle_degs);
	void LookDown(float angle_degs);

	void MoveForward(float units, CollisionVolumeCylinder &camVolume);
	void MoveBackward(float units, CollisionVolumeCylinder camVolume);
	void MoveLeft(float units, CollisionVolumeCylinder camVolume);
	void MoveRight(float units, CollisionVolumeCylinder camVolume);

	void Move(glm::vec3 newPosition);
};