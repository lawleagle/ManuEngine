#ifndef MTIME_H
#define MTIME_H

extern GLFWwindow* Window;
class MTime
{
protected:
	int frames = 0;

	void UpdateMSPF()
	{
		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		frames++;

		if (currentTime - lastTime >= 1.0) {
			char tmp[128];
			sprintf(tmp, "Manu OpenGL @ %lf ms/frame\n", 1000.0 / (double)frames);
			glfwSetWindowTitle(Window, tmp);
			frames = 0;
			lastTime += 1.0;
		}
	}
	void UpdateDeltaTime()
	{
		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		deltaTime = (float)(currentTime - lastTime);
		lastTime = currentTime;
	}
public:
	float deltaTime;

	
	void Update()
	{
		UpdateMSPF();
		UpdateDeltaTime();
	}
};

#endif