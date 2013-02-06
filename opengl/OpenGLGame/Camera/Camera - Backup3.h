#ifdef CAMERA_EXPORTS
#define CAMERA_API __declspec(dllexport)
#else
#define CAMERA_API __declspec(dllimport)
#endif

#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>

//#include "../Collision/Collision.h"

class CAMERA_API Camera
{	
private:
	//Dynamic_Cylinder collisionVolume;

	glm::vec3 sphereCamRelPos;
	glm::vec3 camPos;
	
	glm::vec3 camTarget;	
	glm::vec3 upVector;

	//bool hasCollisionVolume;

public:
	Camera();
	Camera(glm::vec3 newCamTarget, glm::vec3 newSphereCamRelPos);

	glm::mat4 CalcLookAtMatrix();

	/*void AttachCollisionVolume(float radius = 1.5f, float height = 2.0f);
	void DetachCollisionVolume();*/

	glm::vec3 GetPosition();
	glm::vec3 GetForwardVector();

	void LookLeft(float angle_degs);
	void LookRight(float angle_degs);
	void LookUp(float angle_degs);
	void LookDown(float angle_degs);

	void MoveForward(float units/*, Dynamic_Cylinder *treeVolumes, 
								  int treeVolumesCount,
								  Static_AABB parthenonBaseVolume*/);
	void MoveBackward(float units/*, Dynamic_Cylinder *treeVolumes,
								   int treeVolumesCount,
								   Static_AABB parthenonBaseVolume*/);
	void MoveLeft(float units/*, Dynamic_Cylinder *treeVolumes,
							   int treeVolumesCount,
							   Static_AABB parthenonBaseVolume*/);
	void MoveRight(float units/*, Dynamic_Cylinder *treeVolumes,
								int treeVolumesCount,
								Static_AABB parthenonBaseVolume*/);

private:
	glm::vec3 ResolveCamPosition();
};

#endif