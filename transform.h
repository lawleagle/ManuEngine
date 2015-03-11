#ifndef MTRANSFORM_H
#define MTRANSFORM_H


extern MShader Shader;
class MTransform
{
protected:
	GLuint ModelMatrixID;
	glm::mat4 PositionMatrix = glm::mat4(1.0f);
	glm::mat4 ScaleMatrix = glm::mat4(1.0f);

	glm::mat4 RotationMatrixX = glm::mat4(1.0f);
	glm::mat4 RotationMatrixY = glm::mat4(1.0f);
	glm::mat4 RotationMatrixZ = glm::mat4(1.0f);
	glm::mat4 RotationMatrix = glm::mat4(1.0f);

	glm::mat4 ModelMatrix = glm::mat4(1.0f);
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 GetFront()
	{
		Update();
		glm::vec3 Direction = glm::vec3(RotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
		return glm::normalize(Direction);
	}
	glm::vec3 GetRight()
	{
		Update();
		glm::vec3 Right = glm::vec3(RotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
		return glm::normalize(Right);
	}


	MTransform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;
		Update();
	}
	void operator+= (const MTransform transform)
	{
		Position += transform.Position;
		Rotation += transform.Rotation;
		Scale += transform.Scale;
		Update();
	}
	MTransform operator+ (const MTransform transform) const 
	{
		MTransform result;
		result.Position = Position + transform.Position;
		result.Rotation = Rotation + transform.Rotation;
		result.Scale = Scale + transform.Scale;
		result.Update();
		return result;
	}
	void operator= (const MTransform transform)
	{
		Position = transform.Position;
		Rotation = transform.Rotation;
		Scale = transform.Scale;
		Update();
	}


	void Update()
	{
		PositionMatrix = glm::translate(Position);
		ScaleMatrix = glm::scale(Scale);

		glm::vec3 axisX = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 axisZ = glm::vec3(0.0f, 0.0f, 1.0f);
		RotationMatrixX = glm::mat4(1.0f) * glm::rotate(Rotation.x * 3.14f / 180.0f, axisX);
		RotationMatrixY = glm::mat4(1.0f) * glm::rotate(Rotation.y * 3.14f / 180.0f, axisY);
		RotationMatrixZ = glm::mat4(1.0f) * glm::rotate(Rotation.z * 3.14f / 180.0f, axisZ);
		RotationMatrix = RotationMatrixZ * RotationMatrixY * RotationMatrixX;

		ModelMatrix = PositionMatrix * RotationMatrix * ScaleMatrix;
	}
	void Render()
	{
		ModelMatrixID = glGetUniformLocation(Shader.ProgramID, "ModelMatrix");
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	}
};


#endif