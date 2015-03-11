#ifndef MCAMERA_H
#define MCAMERA_H

extern GLFWwindow* Window;
extern MTime Time;
extern MInput Input;
extern MShader Shader;
class MCamera
{
protected:
	GLuint MatrixID;
	GLuint CameraMatrixID;
	MTransform Transform;
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 CameraMatrix;
	

	float initialFoV = 45.0f;
	float speed = 6.0f;
	float mouseSpeed = 10.1f;


	void ComputeMatricesFromInputs()
	{
		double mouseX, mouseY;
		Input.GetMouseOffset(mouseX, mouseY);


		Transform.Rotation.y += mouseSpeed * Time.deltaTime * (float)mouseX;
		Transform.Rotation.x -= mouseSpeed * Time.deltaTime * (float)mouseY;
		if (Transform.Rotation.x < -90.0f) Transform.Rotation.x = -90.0f;
		if (Transform.Rotation.x > 90.0f) Transform.Rotation.x = 90.0f;


		glm::vec3 Direction = Transform.GetFront();
		glm::vec3 Right = Transform.GetRight();
		glm::vec3 Up = glm::cross(Direction, Right);


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
		
		Projection = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 1000.0f);
		View = glm::lookAt(
			Transform.Position,
			Transform.Position + Direction,
			Up
			);
	}
public:
	void Awake()
	{
		Transform.Position = glm::vec3(0.0f, 0.0f, 5.0f);
		Transform.Rotation = glm::vec3(0.0f, 180.0f, 0.0f);
	}
	void Update()
	{
		ComputeMatricesFromInputs();
		CameraMatrix = Projection * View;


		CameraMatrixID = glGetUniformLocation(Shader.ProgramID, "CameraMatrix");
		glUniformMatrix4fv(CameraMatrixID, 1, GL_FALSE, &CameraMatrix[0][0]);
	}
};


#endif