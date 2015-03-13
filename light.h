#ifndef MLIGHT_H
#define MLIGHT_H


class MLight
{
protected:
	GLuint LightColorID;
	GLuint LightIntensityID;

	MTransform Transform;
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	float lightIntensity = 0.8f;

	virtual void OnAwake() {}
	virtual void OnUpdate() {}
	virtual void OnRender() {}
public:
	void Awake()
	{
		OnAwake();
	}
	void Update()
	{
		OnUpdate();
		Transform.Update();
	}
	void Render()
	{
		OnRender();
	}
};


#endif;