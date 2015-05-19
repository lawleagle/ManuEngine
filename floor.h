#ifndef MFLOOR_H
#define MFLOOR_H



class MFloor : public MObject
{
public:
	void onAwake()
	{
		//Texture.Load("blueice.jpg");
		Texture.Load("tron.jpg");

		Mesh.verts = {
			glm::vec3(-10000.0f, 0.0f, 10000.0f),
			glm::vec3(10000.0f, 0.0f, 10000.0f),
			glm::vec3(-10000.0f, 0.0f, -10000.0f),
			glm::vec3(10000.0f, 0.0f, -10000.0f)
		};
		Mesh.uvs = {
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1000.0f),
			glm::vec2(1000.0f, 0.0f),
			glm::vec2(1000.0f, 1000.0f)
		};
		Mesh.normals = {
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		};
		Mesh.tris = { 0, 1, 2, 3, 2, 1 };
		Transform.Scale = glm::vec3(0.25f, 0.25f, 0.25f);

		Collision.CreateCollisionMesh(COLLISION_PLANE, 200.0f, 200.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	}
};


#endif