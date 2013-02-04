#ifndef PROGRAM_DATA_H
#define PROGRAM_DATA_H


struct ParticleProgData
{
	GLuint theProgram;

	GLuint deltaTime_millisecondsUnif;
	GLuint randomTextureUnif;
	GLuint timeUnif;
	GLuint launcherLifetimeUnif;
	GLuint shellLifetimeUnif;
	GLuint secondaryShellLifetimeUnif;

	GLuint particleTypeAttrib;
	GLuint particlePositionAttrib;
	GLuint particleVelocityAttrib;
	GLuint particleAgeAttrib;
};

struct BillboardProgData
{
	GLuint theProgram;

	GLuint positionAttrib;
	GLuint textureCoordAttrib;

	GLuint modelToCameraMatrixUnif;
	GLuint cameraToClipMatrixUnif;
	GLuint cameraPositionUnif;
	GLuint samplerUnif;
	GLuint billboardSizeUnif;

	GLuint currentTime_secondsUnif;
	GLuint velocityUnif;
	GLuint deltaPositionUnif;
};

struct SimpleProgram
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;
	GLuint cameraToClipMatrixUnif;

	GLuint colorUnif;
};

struct TextureProgData
{
	GLuint theProgram;

	GLuint modelToCameraMatrixUnif;
	GLuint cameraToClipMatrixUnif;

	GLuint colorUnif;

	GLuint samplerUniform;

	GLuint positionAttrib;
	GLuint texCoordAttrib;
};

struct InstancedProgramData
{
	GLuint theProgram;

	GLuint samplerUnif;
	GLuint cameraToClipMatrixUnif;
	GLuint modelToCameraMatrixUnif;

	GLuint positionAttrib;
	GLuint texCoordAttrib;
	GLuint modelMatrixAttrib;
};


#endif