#ifndef MOBJECT_H
#define MOBJECT_H

extern btDynamicsWorld* DynamicsWorld;
class MObject
{
protected:
	virtual void OnAwake() {}
	virtual void OnUpdate() {}
	virtual void OnRender() {}
public:
	MTransform Transform;
	MCollision Collision;
	MTexture Texture;
	MMesh Mesh;


	void setPosition(glm::vec3 position)
	{
		if (Collision.isCreated)
		{
			Collision.Transform.setOrigin(btVector3(position.x, position.y, position.z));
			Collision.RigidBody->translate(btVector3(position.x, position.y, position.z));
		}
		else {
			Transform.Position.x = position.x;
			Transform.Position.y = position.y;
			Transform.Position.z = position.z;
		}
	}


	bool hasTransparency = false;
	MObject()
	{
		Awake();
	}
	void Awake()
	{
		OnAwake();
	}
	void Update()
	{
		OnUpdate();
		if (Collision.isCreated == true)
		{
			float mat[16];
			Collision.Update();
			Collision.Transform.getOpenGLMatrix(mat);
			Transform.ModelMatrix = glm::make_mat4(mat);

			/*Collision.Update();
			Transform.Position.x = Collision.Transform.getOrigin().getX();
			Transform.Position.y = Collision.Transform.getOrigin().getY();
			Transform.Position.z = Collision.Transform.getOrigin().getZ();
			std::cout << '*' << std::endl;*/
		}
		else Transform.Update();
		Mesh.Update();
	}
	void Render()
	{
		OnRender();
		if (hasTransparency) {
			glEnable(GL_BLEND);
			glDepthMask(0);
		}
		Texture.Use();
		Transform.Render();
		Mesh.Render();

		if (hasTransparency) {
			glDisable(GL_BLEND);
			glDepthMask(1);
		}
	}
	void Delete()
	{
		if (Collision.isCreated)
		{
			Collision.DeleteCollisionMesh();
		}
	}
};


#endif