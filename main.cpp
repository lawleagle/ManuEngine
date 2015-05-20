#define _CRT_SECURE_NO_WARNINGS
#define GLM_FORCE_RADIANS


#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <freeimage.h>
#include <GL/GLU.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/LinearMath/btHashMap.h>

#include "utility.h"
#include "random.h"
#include "time.h"
#include "input.h"
#include "shader.h"
#include "transform.h"
#include "light.h"
#include "directionallight.h"
#include "camera.h"
#include "collision.h"
#include "texture.h"
#include "mesh.h"
#include "object.h"
	#include "floor.h"
	#include "cube.h"
	#include "suzanne.h"
	#include "robot.h"
	#include "sphere.h"
	#include "asteroid.h"
	#include "spaceship.h"
#include "skybox.h"
#include "player.h"
#include "world.h"


GLFWwindow* Window;
MTime Time;
MInput Input;
MRandom Random;
MShader Shader;
MCamera Camera;


MWorld World;

btDynamicsWorld* DynamicsWorld;
btDispatcher* Dispatcher;
btCollisionConfiguration* CollisionConfiguration;
btBroadphaseInterface* Broadphase;
btConstraintSolver* Solver;
std::vector<btRigidBody*> Bodies;


void DynamicsWorldInit()
{
	CollisionConfiguration = new btDefaultCollisionConfiguration();
	Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
	Broadphase = new btDbvtBroadphase();
	Solver = new btSequentialImpulseConstraintSolver();
	DynamicsWorld = new btDiscreteDynamicsWorld(Dispatcher, Broadphase, Solver, CollisionConfiguration);
	DynamicsWorld->setGravity(btVector3(0.0f, 0.0f, 0.0f));
}




int main()
{
	if (!glfwInit()) {
		std::cerr << "Could not initialize glfw." << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Window = glfwCreateWindow(800, 600, "Manu OpenGL", NULL, NULL);
	if (Window == NULL) {
		std::cerr << "Could not open window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(Window);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Could not initialize glew." << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Input.Awake();
	DynamicsWorldInit();
	World.Awake();

	


		

	
	do {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		Time.Update();

		World.Update();


		World.Render();


		DynamicsWorld->stepSimulation(Time.deltaTime);
		glfwSwapBuffers(Window);
		glfwPollEvents();
	} while (Input.GetKey(GLFW_KEY_ESCAPE) == false && glfwWindowShouldClose(Window) == false);

	//World.Delete();

	for (int i = 0; i < Bodies.size(); i++)
	{
		DynamicsWorld->removeCollisionObject(Bodies[i]);
		btMotionState* motionState = Bodies[i]->getMotionState();
		btCollisionShape* shape = Bodies[i]->getCollisionShape();
		delete Bodies[i];
		delete shape;
		delete motionState;
	}

	delete CollisionConfiguration;
	delete Dispatcher;
	delete Broadphase;
	delete Solver;
	delete DynamicsWorld;


	glfwTerminate();
	std::cout << "PROGRAM REACHED THIS POINT" << std::endl;
	return 0;
}