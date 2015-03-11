#ifndef MDIRECTIONALLIGHT_H
#define MDIRECTIONALLIGHT_H


class MDirectionalLight : public MLight
{
protected:
	GLuint LightDirectionID;
	glm::vec3 lightDirection;

	void OnAwake()
	{
		Transform.Rotation = glm::vec3(-45.0f, 45.0f, 0.0f);
		lightDirection = Transform.GetFront();
		lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		lightIntensity = 0.8f;
	}
	void OnUpdate()
	{
	}
	void OnRender()
	{
		LightColorID = glGetUniformLocation(Shader.ProgramID, "SunLight.Color");
		glUniform3f(LightColorID, lightColor.x, lightColor.y, lightColor.z);

		LightIntensityID = glGetUniformLocation(Shader.ProgramID, "SunLight.Intensity");
		glUniform1f(LightIntensityID, lightIntensity);

		LightDirectionID = glGetUniformLocation(Shader.ProgramID, "SunLight.Direction");
		glUniform3f(LightDirectionID, lightDirection.x, lightDirection.y, lightDirection.z);
	}
};


#endif