#ifndef MINPUT_H
#define MINPUT_H


enum MouseScroll
{
	SCROLL_X,
	SCROLL_Y
};


extern GLFWwindow* Window;
class MInput
{
protected:
	std::bitset<512> keysDown;
	std::bitset<512> keysUp;
	double scrollX;
	double scrollY;
	static void scroll_callback(GLFWwindow* window, double x, double y);
public:
	/// <summary>
	/// Set to false to free the mouse
	/// </summary>
	bool mouseControl = true;
	

	void Awake()
	{
		glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetScrollCallback(Window, scroll_callback);
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
	double GetScroll(MouseScroll axis)
	{
		if (axis == SCROLL_Y) {
			double aux = scrollY;
			scrollY = 0;
			return aux;
		}
		else if (axis == SCROLL_X) {
			double aux = scrollX;
			scrollX = 0;
			return aux;
		}
		return 0;
	}
	void SetScroll(MouseScroll axis, double val)
	{
		if (axis == SCROLL_X) {
			scrollX = val;
		}
		else if (axis == SCROLL_Y)
		{
			scrollY = val;
		}
	}
};


extern MInput Input;
void scrollCallback(double x, double y)
{
	Input.SetScroll(SCROLL_X, x);
	Input.SetScroll(SCROLL_Y, y);
}
void MInput::scroll_callback(GLFWwindow* window, double x, double y)
{
	scrollCallback(x, y);
}


#endif