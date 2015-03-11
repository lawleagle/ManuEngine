#ifndef MINPUT_H
#define MINPUT_H

extern GLFWwindow* Window;
class MInput
{
protected:
	std::bitset<512> keysDown;
	std::bitset<512> keysUp;
public:
	bool mouseControl = true;
	

	void Awake()
	{
		glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);
	}

	bool GetKeyDown(int key)
	{
		if (GetKey(key) && keysDown[key] == false) {
			keysDown[key] = true;
			return true;
		}
		if (!GetKey(key)) {
			keysDown[key] = false;
		}
		return false;
	}
	bool GetKeyUp(int key)
	{
		if (!GetKey(key) && keysUp[key] == true) {
			keysUp[key] = false;
			return true;
		}
		if (GetKey(key)) {
			keysUp[key] = true;
		}
		return false;
	}
	bool GetKey(int key)
	{
		return glfwGetKey(Window, key) == GLFW_PRESS;
	}
	void GetMouseOffset(double &mouseX, double &mouseY)
	{
		int width, height;
		glfwGetWindowSize(Window, &width, &height);

		if (mouseControl)
		{
			glfwGetCursorPos(Window, &mouseX, &mouseY);
			glfwSetCursorPos(Window, width / 2, height / 2);

			mouseX = (double)(width / 2) - mouseX;
			mouseY = (double)(height / 2) - mouseY;
		}
		else
		{
			mouseX = 0.0;
			mouseY = 0.0;
		}
	}
};


#endif