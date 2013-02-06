//Copyright (C) 2010-2012 by Jason L. McKesson
//This file is licensed under the MIT License.


#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "framework/framework.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glutil/MatrixStack.h>

#include <ctime>

#include "Camera/TopDownCamera.h"
#include "ProgramData/ProgramData.h"
#include "Spaceship/Spaceship.h"
#include "framework/LeapListener.h"


#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))
#define PI 3.1419f

const float CAMERA_HEIGHT = 12.5f;


TopDownCamera camera = TopDownCamera(glm::vec3(0.0f, 0.0f, 0.0f), CAMERA_HEIGHT, 270.0f, 45.0f);

SimpleProgram simpleProgram;


void InitializeSimpleProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "shaders/PosColorLocalTransform.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "shaders/ColorPassthrough.frag"));

	simpleProgram.theProgram = Framework::CreateProgram(shaderList);

	simpleProgram.modelToCameraMatrixUnif = glGetUniformLocation(simpleProgram.theProgram, "modelToCameraMatrix");
	simpleProgram.cameraToClipMatrixUnif = glGetUniformLocation(simpleProgram.theProgram, "cameraToClipMatrix");

	simpleProgram.colorUnif = glGetUniformLocation(simpleProgram.theProgram, "color");
}


const float simpleVertexData[] =
{
	-1.0f, +1.0f, 0.0f, 1.0f,
	//1.0f, 1.0f,
	+1.0f, +1.0f, 0.0f, 1.0f,
	//1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 1.0f,
	//0.0f, 1.0f,

	+1.0f, -1.0f, 0.0f, 1.0f, 
	//1.0f, 0.0f,
	//-1.0f, -1.0f, 0.0f, 1.0f,
	//0.0f, 0.0f,
	//-1.0f, +1.0f, 0.0f, 1.0f,
	//0.0f, 1.0f,
};
const float textureVertexData[] =
{
	-0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 1.0f,
};

const float textureUVData[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f, 
	0.0f, 1.0f,
};

GLuint indices[] =
{
	0, 1, 2,
	2, 3, 0,
};

GLuint vertexBufferObject;
GLuint vertexBufferObjectTwo;
GLuint UVBufferObject;
GLuint indexBO;

GLuint vao;


void InnitializePlane(const glm::vec3 &position, float width, float height)
{
	std::vector<float> vertexData;
	std::vector<unsigned short> indexData;

	vertexData.push_back(position.x);
	vertexData.push_back(position.y - height);
	vertexData.push_back(position.z); vertexData.push_back(1.0f);

	vertexData.push_back(position.x - width);
	vertexData.push_back(position.y - height);
	vertexData.push_back(position.z); vertexData.push_back(1.0f);

	vertexData.push_back(position.x - width);
	vertexData.push_back(position.y);
	vertexData.push_back(position.z); vertexData.push_back(1.0f);

	vertexData.push_back(position.x);
	vertexData.push_back(position.y);
	vertexData.push_back(position.z); vertexData.push_back(1.0f);

			
	indexData.push_back(0); indexData.push_back(1); indexData.push_back(2);
	indexData.push_back(2); indexData.push_back(3); indexData.push_back(0);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 
					sizeof(float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					sizeof(unsigned short) * indexData.size(), &indexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void InitializeSimpleVertexBuffer()
{
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(simpleVertexData), simpleVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void InitializeTextureVertexBuffer()
{
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureVertexData), textureVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &UVBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, UVBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureUVData), textureUVData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &indexBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int frameCount = 0;
const char WINDOW_TITLE[] = "Test Playground: ";

void TimerFunction(int value)
{
	if(value != 0)
	{
		char *tempString = (char *)malloc(512 + strlen(WINDOW_TITLE));

		sprintf(tempString, "%s %i frames per second", WINDOW_TITLE, frameCount * 4);

		glutSetWindowTitle(tempString);
		free(tempString);
	}

	frameCount = 0;
	glutTimerFunc(250, TimerFunction, 1);
}


GLuint g_texture;

long long GetCurrentTimeMillis()
{
	return time(0) * 1000;
}

long long currentTime_milliseconds;

Spaceship spaceship = Spaceship(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
							    glm::vec3(0.0f, 0.0f, 15.0f));

int oldTimeSinceStart = 0;

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	currentTime_milliseconds = GetCurrentTimeMillis();

	glutTimerFunc(0, TimerFunction, 0);
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	InitializeSimpleProgram();
	InnitializePlane(glm::vec3(), 5.0f, 5.0f);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);


	spaceship.InitMesh("mesh-files/Ship.xml");
	//spaceship = Spaceship(glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3(), "data/mesh-files/Ship.xml");
}


glm::vec3 planePosition = glm::vec3();
float planeRotationY = 0.0f;

int deltaTime = 0;

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	frameCount++;


	long long timeNow_milliseconds = GetCurrentTimeMillis();
	//assert(timeNow_milliseconds >= currentTime_milliseconds); // TODO: remove in release
	unsigned int deltaTime_milliseconds = 
		(unsigned int)(timeNow_milliseconds - currentTime_milliseconds);
	currentTime_milliseconds = timeNow_milliseconds;
	float currentTime_seconds = timeNow_milliseconds / 1000.0f;


	glClearColor(0.0f, 0.5f, 0.7f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glm::vec3 cameraPosition = camera.ResolveCamPosition();	
	glutil::MatrixStack modelMatrix;			
	modelMatrix.SetMatrix(camera.CalcMatrix());
	

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;


	spaceship.Update(deltaTime);
	spaceship.Render(modelMatrix, simpleProgram);


	glutSwapBuffers();
	glutPostRedisplay();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int width, int height)
{
	glutil::MatrixStack projMatrix;
	float aspectRatio = width / (float) height;
	projMatrix.Perspective(45.0f, aspectRatio, 1.0f, 1000.0f);


	glUseProgram(simpleProgram.theProgram);
	glUniformMatrix4fv(simpleProgram.cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(projMatrix.Top()));
	glUseProgram(0);


	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

float newPositionX = 0.0f;
float newDistance = CAMERA_HEIGHT;


void UserListener::onInit(const Leap::Controller& controller) 
{	
	std::cout << "Initialized" << std::endl;
}

void UserListener::onConnect(const Leap::Controller& controller) 
{
	std::cout << "Connected" << std::endl;
}

void UserListener::onDisconnect(const Leap::Controller& controller) 
{
	std::cout << "Disconnected" << std::endl;
}

void UserListener::onExit(const Leap::Controller& controller) 
{
	std::cout << "Exited" << std::endl;
}

void CalculatePosition(const Leap::Hand &hand)
{
	glm::vec3 handVelocity = glm::vec3(hand.palmVelocity().x,
									   hand.palmVelocity().y,
									   hand.palmVelocity().z);
	planePosition.x += handVelocity.x / 1000.0f;
	planePosition.y += -handVelocity.z / 1000.0f;
	
}
void CalculateRotation(const Leap::Hand &hand)
{
	glm::vec3 handNormal = glm::vec3(hand.palmNormal().x,
									 hand.palmNormal().y,
									 hand.palmNormal().z);
	glm::vec3 zeroVector = glm::vec3();
	glm::vec3 deltaPos = zeroVector - handNormal;

	planeRotationY = atan2f(deltaPos.x, deltaPos.z) * 180 / PI;
}

void UserListener::onFrame(const Leap::Controller& controller)
{
	const Leap::Frame currentFrame = controller.frame();

	if(!currentFrame.hands().empty())
	{
		const Leap::Hand movementHand = currentFrame.hands()[0];

		CalculatePosition(movementHand);
		CalculateRotation(movementHand);		
	}
}



//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	case 'a':
		spaceship.Steer(deltaTime, 2.0f, -1.0f);
		break;
	case 'w':
		spaceship.Move(deltaTime, 0.00001f, 1.0f);
		break;
	}
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}