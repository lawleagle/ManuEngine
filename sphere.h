#ifndef MSPHERE_H
#define MSPHERE_H


class MSphere : public MObject
{
protected:
	void OnUpdate()
	{
		//std::cout << Collision.Transform.getOrigin().getY() << std::endl;
	}
public:
	void Awake(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		MObject::Awake();
		Texture.Load("snow.jpg");
		Mesh.Load("sphere.obj");

		Transform.Position.x = position.x;
		Transform.Position.y = position.y;
		Transform.Position.z = position.z;

		//Collision.CreateCollisionMesh(COLLISION_SPHERE, 1.0f, glm::vec3(Transform.Position.x, Transform.Position.y, Transform.Position.z), 1.0f);
	}
	void setVelocity(glm::vec3 velocity)
	{
		if (Collision.isCreated)
		{
			Collision.RigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
		}
	}
};


#endif