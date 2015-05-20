#ifndef MSPACESHIP_H
#define MSPACESHIP_H


extern MCamera Camera;
class MSpaceship : public MObject
{
private:
	float angle = 0.0f;
	float updownspeed = 2.0f;
	float updowndistance = 0.6f;


	void onAwake()
	{
		Texture.Load("gray.jpg");
		Mesh.Load("Ship2.obj");
	}

	void onUpdate()
	{
		Transform.Position = Camera.Transform.Position + 30.0f * Camera.Transform.GetFront() + glm::vec3(0.0f, -2.0f, 0.0f);

		Transform.Position.y = Transform.Position.y + sin(angle) * updowndistance;
		Transform.Rotation.z = Camera.Transform.Rotation.z;
		Transform.Rotation.y = 180.0f + Camera.Transform.Rotation.y;
		if (Transform.Position.y < 0.0f) Transform.Position.y = 0.0f;
		if (angle > 2 * 3.14f) angle = 0.0f;
		angle += Time.deltaTime * updownspeed;
	}
public:
};


#endif;