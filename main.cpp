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
#include "skybox.h"
#include "player.h"
#include "world.h"


GLFWwindow* Window;
MTime Time;
MInput Input;
MShader Shader;
MCamera Camera;


MWorld World;


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

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Could not initialize glew." << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	Input.Awake();
	
	//Camera.Awake();
	World.Awake();

	
	do {
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Input.GetKeyDown(GLFW_KEY_F)) Input.mouseControl ^= true;
		Time.Update();

		//Camera.Update();
		World.Update();

		World.Render();

		glfwSwapBuffers(Window);
		glfwPollEvents();
	} while (Input.GetKey(GLFW_KEY_ESCAPE) == false && glfwWindowShouldClose(Window) == false);


	glfwTerminate();
	return 0;
}