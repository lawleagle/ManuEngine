#ifndef MSKYBOX_H
#define MSKYBOX_H


class MSkybox
{
private:
	MObject Face[6];
public:
	void Load(std::string front_filepath, std::string back_filepath, std::string left_filepath, std::string right_filepath, std::string top_filepath, std::string bottom_filepath)
	{
		Face[0].Texture.Load(front_filepath);
		Face[1].Texture.Load(back_filepath);
		Face[2].Texture.Load(left_filepath);
		Face[3].Texture.Load(right_filepath);
		Face[4].Texture.Load(top_filepath);
		Face[5].Texture.Load(bottom_filepath);
		


		glm::vec3 verts[24] = {
			// Front face
			glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f),
			// Back face
			glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(50.0f, -50.0f, -50.0f),
			// Left face
			glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f),
			// Right face
			glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(50.0f, -50.0f, -50.0f), glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(50.0f, -50.0f, 50.0f),
			// Top face
			glm::vec3(-50.0f, 50.0f, -50.0f), glm::vec3(50.0f, 50.0f, -50.0f), glm::vec3(-50.0f, 50.0f, 50.0f), glm::vec3(50.0f, 50.0f, 50.0f),
			// Bottom face
			glm::vec3(50.0f, -50.0f, -50.0f), glm::vec3(-50.0f, -50.0f, -50.0f), glm::vec3(50.0f, -50.0f, 50.0f), glm::vec3(-50.0f, -50.0f, 50.0f),
		};
		std::vector< glm::vec2 > uvs = {
			glm::vec2(0.0f, 1.0f), 
			glm::vec2(0.0f, 0.0f), 
			glm::vec2(1.0f, 1.0f), 
			glm::vec2(1.0f, 0.0f)
		};
		std::vector< glm::vec3 > normals = {
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		};
		std::vector< size_t > tris = { 0, 1, 2, 3, 2, 1 };


		for (int i = 0; i < 6; i++) {
			Face[i].Mesh.verts.push_back(verts[4 * i + 0]);
			Face[i].Mesh.verts.push_back(verts[4 * i + 1]);
			Face[i].Mesh.verts.push_back(verts[4 * i + 2]);
			Face[i].Mesh.verts.push_back(verts[4 * i + 3]);

			Face[i].Mesh.uvs = uvs;
			Face[i].Mesh.normals = normals;
			Face[i].Mesh.tris = tris;

			Face[i].Mesh.Update();
		}
	}
	
	void Awake()
	{
		Load("skybox/front.jpg", "skybox/back.jpg", "skybox/left.jpg", "skybox/right.jpg", "skybox/top.jpg", "skybox/bottom.jpg");
	}
	void Update(glm::vec3 position)
	{
		for (int i = 0; i < 6; i++) {
			Face[i].Transform.Position = position;
			Face[i].Update();
		}
	}
	void Render()
	{
		glDepthMask(0);
		for (int i = 0; i < 6; i++) {
			Face[i].Render();
		}
		glDepthMask(1);
	}
};


#endif