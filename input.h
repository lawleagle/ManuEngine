#ifndef MINPUT_H
#define MINPUT_H

extern GLFWwindow* Window;
class MInput
{
protected:
	std::bitset<512> keysDown;
	std::bitset<512> keysUp;
public:
	/// <summary>
	/// Set to false to free the mouse
	/// </summary>
	bool mouseControl = true;
	

	void Awake()
	{
		glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);
	}

	/// <summary>
	/// Returns true at the moment 'key' is pressed
	/// </summary>
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

	/// <summary>
	/// Returns true at the moment 'key' is released
	/// </summary>
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

	/// <summary>
	/// Checks if 'key' is being pressed
	/// </summary>
	bool GetKey(int key)
	{
		return glfwGetKey(Window, key) == GLFW_PRESS;
	}

	/// <summary>
	/// Provides mouse offset if 'moseControl' is true
	/// </summary>
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