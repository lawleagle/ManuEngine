#ifndef MFLOOR_H
#define MFLOOR_H



class MFloor : public MObject
{
public:
	void OnAwake()
	{
		Texture.Load("blueice.jpg");

		Mesh.verts = {
			glm::vec3(-100.0f, 0.0f, 100.0f),
			glm::vec3(100.0f, 0.0f, 100.0f),
			glm::vec3(-100.0f, 0.0f, -100.0f),
			glm::vec3(100.0f, 0.0f, -100.0f)
		};
		Mesh.uvs = {
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 10.0f),
			glm::vec2(10.0f, 0.0f),
			glm::vec2(10.0f, 10.0f)
		};
		Mesh.normals = {
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		};
		Mesh.tris = { 0, 1, 2, 3, 2, 1 };


		Collision.CreateCollisionMesh(COLLISION_PLANE, 200.0f, 200.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	}
};


#endif