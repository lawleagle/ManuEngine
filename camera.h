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
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 CameraMatrix;
	

	float initialFoV = 45.0f;


	void ComputeMatrices()
	{
		glm::vec3 Direction = Transform.GetFront();
		glm::vec3 Right = Transform.GetRight();
		glm::vec3 Up = glm::cross(Direction, Right);
		Projection = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 1000.0f);
		View = glm::lookAt(
			Transform.Position,
			Transform.Position + Direction,
			Up
			);
	}
public:
	MTransform Transform;
	void Awake()
	{
	}
	void Update()
	{
		ComputeMatrices();
		CameraMatrix = Projection * View;

		CameraMatrixID = glGetUniformLocation(Shader.ProgramID, "CameraMatrix");
		glUniformMatrix4fv(CameraMatrixID, 1, GL_FALSE, &CameraMatrix[0][0]);
	}
};


#endif