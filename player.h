#ifndef MPLAYER_H
#define MPLAYER_H


extern MCamera Camera;
class MPlayer
{
private:
public:
	MTransform Transform;
	float speed = 6.0f;
	float mouseSpeed = 10.1f;


	void Awake()
	{
		Camera.Awake();
		Transform.Position = glm::vec3(0.0f, 0.0f, 5.0f);
		Transform.Rotation = glm::vec3(0.0f, 180.0f, 0.0f);

		Camera.Transform = Transform;
		Camera.Update();
	}
	void Update()
	{
		glm::vec3 Direction = Transform.GetFront();
		glm::vec3 Right = Transform.GetRight();
		glm::vec3 Up = glm::cross(Direction, Right);


		double mouseX, mouseY;
		Input.GetMouseOffset(mouseX, mouseY);

		Transform.Rotation.y += mouseSpeed * Time.deltaTime * (float)mouseX;
		Transform.Rotation.x -= mouseSpeed * Time.deltaTime * (float)mouseY;
		if (Transform.Rotation.x < -90.0f) Transform.Rotation.x = -90.0f;
		if (Transform.Rotation.x > 90.0f) Transform.Rotation.x = 90.0f;


		if (Input.GetKey(GLFW_KEY_W)) {
			Transform.Position += Direction * Time.deltaTime * speed;
		}
		if (Input.GetKey(GLFW_KEY_S)) {
			Transform.Position -= Direction * Time.deltaTime * speed;
		}
		if (Input.GetKey(GLFW_KEY_D)) {
			Transform.Position -= Right * Time.deltaTime * speed;
		}
		if (Input.GetKey(GLFW_KEY_A)) {
			Transform.Position += Right * Time.deltaTime * speed;
		}
		if (Input.GetKey(GLFW_KEY_E)) {
			Transform.Position += Up * Time.deltaTime * speed;
		}
		if (Input.GetKey(GLFW_KEY_Q)) {
			Transform.Position -= Up * Time.deltaTime * speed;
		}
		
		Camera.Transform = Transform;
		Camera.Update();
	}
	void Render()
	{

	}
};

#endif