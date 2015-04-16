#ifndef MASTEROID_H
#define MASTEROID_H


class MAsteroid : public MObject
{
private:
	glm::vec3 movingSpeed;
	glm::vec3 rotationSpeed;
	float speedMultiplier = 1.0f;
	float rotationMultiplier = 1.0f;
public:
	MAsteroid(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		MObject::Awake();
		Transform.Position = position;
		movingSpeed = speed;
		rotationSpeed = rotation;

	}

	void setSpeed(glm::vec3 _speed)
	{
		rotationSpeed = _speed;
	}


	void onUpdate()
	{
		Transform.Position += movingSpeed * speedMultiplier;
		Transform.Rotation += rotationSpeed * rotationMultiplier;
	}
};


#endif