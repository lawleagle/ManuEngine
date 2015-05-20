#ifndef MPLAYER_H
#define MPLAYER_H


extern MCamera Camera;
class MPlayer
{
protected:
public:
	MTransform Transform;
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	float speed = 3.0f;
	float decceleartionSpeed = 100.0f;
	float verticalSpeed = 0.3f;
	float mouseSpeed = 10.1f;
	float rotationSpeed = 1.0f; float yRotated = 0.0f;


	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 initialRotation, rotated = glm::vec3(0.0f, 0.0f, 0.0f);


	void Awake()
	{
		Camera.Awake();
		Transform.Position = glm::vec3(0.0f, 12.0f, 0.0f);
		Transform.Rotation = glm::vec3(15.0f, 180.0f, 0.0f);
		initialRotation = Transform.Rotation;

		Camera.Transform = Transform;
		Camera.Update();
	}
	void Update()
	{
		//forward = Transform.GetFront(); forward.y = 0.0f;
		//right = Transform.GetRight(); right.y = 0.0f;


		if (Input.GetKey(GLFW_KEY_W)) {
			velocity += forward * Time.deltaTime * speed;
		}
		else if (Input.GetKey(GLFW_KEY_S)) {
			velocity -= forward * Time.deltaTime * speed;
		}
		else {
			velocity.z = 0.9f * velocity.z;
		}


		if (Input.GetKey(GLFW_KEY_D) && rotated.z < 4.0f) {
			velocity += right * Time.deltaTime * speed;
			rotationVelocity += forward * Time.deltaTime * speed * (30.0f - std::abs(rotated.x)) / 30.0f;
		}
		else if (Input.GetKey(GLFW_KEY_A) && rotated.z > -4.0f) {
			velocity -= right * Time.deltaTime * speed;
			rotationVelocity -= forward * Time.deltaTime * speed;
		}
		else {
			velocity.x = 0.9f * velocity.x;
			rotationVelocity = 0.9f * rotationVelocity;
			rotated = 0.9f * rotated;
		}

		/*if (Input.GetKey(GLFW_KEY_A)) {
			yRotated += rotationSpeed;
		}
		if (Input.GetKey(GLFW_KEY_D)) {
			yRotated -= rotationSpeed;
		}*/


		if (rotated.z > 20) rotated.z = 20;
		if (rotated.z < -20) rotated.z = -20;


		if (Input.GetKey(GLFW_KEY_Q)) {
			velocity -= up * Time.deltaTime * verticalSpeed;
		}
		else if (Input.GetKey(GLFW_KEY_E)) {
			velocity += up * Time.deltaTime * verticalSpeed;
		}
		else {
			velocity.y = 0.9f * velocity.y;
		}

		
		Transform.Position += velocity;
		rotated += rotationVelocity;
		Transform.Rotation = initialRotation + rotated;
		Transform.Rotation.y += yRotated;
		if (Transform.Position.y < 0.5f) Transform.Position.y = 0.5f;
		
		Camera.Transform = Transform;
		Camera.Update();
	}
	void Render()
	{

	}
};

#endif