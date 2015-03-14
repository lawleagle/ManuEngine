#define _CRT_SECURE_NO_WARNINGS
#define GLM_FORCE_RADIANS


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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <freeimage.h>
#include <GL/GLU.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/LinearMath/btHashMap.h>


#include "time.h"
#include "input.h"
#include "shader.h"
#include "transform.h"
#include "light.h"
#include "directionallight.h"
#include "camera.h"
#include "texture.h"
#include "mesh.h"
#include "object.h"
	#include "floor.h"
	#include "cube.h"
	#include "suzanne.h"
	#include "robot.h"
	#include "sphere.h"
#include "skybox.h"
#include "player.h"
#include "world.h"


GLFWwindow* Window;
MTime Time;
MInput Input;
MShader Shader;
MCamera Camera;


MWorld World;
MSphere Sphere;


btBroadphaseInterface* broadphase = new btDbvtBroadphase();
btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);




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
	glfwSetScrollCallback(Window, scroll_callback);

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
	World.Awake();
	Sphere.Awake(); Sphere.Transform.Position = glm::vec3(-4.0f, 0.0f, 0.0f);


	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btCollisionShape* fallShape = new btSphereShape(1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);


		

	
	do {
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Input.GetKeyDown(GLFW_KEY_F)) Input.mouseControl ^= true;

		Time.Update();
		World.Update();

		World.Render();

		dynamicsWorld->stepSimulation(1 / 60.f, 10);

		btTransform trans;
		fallRigidBody->getMotionState()->getWorldTransform(trans);
		Sphere.Transform.Position.y = trans.getOrigin().getY();
		Sphere.Update();
		Sphere.Render();

		glfwSwapBuffers(Window);
		glfwPollEvents();
	} while (Input.GetKey(GLFW_KEY_ESCAPE) == false && glfwWindowShouldClose(Window) == false);


	dynamicsWorld->removeRigidBody(fallRigidBody);
	delete fallRigidBody->getMotionState();
	delete fallRigidBody;

	dynamicsWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;


	delete fallShape;

	delete groundShape;


	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;


	glfwTerminate();
	return 0;
}