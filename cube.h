#ifndef MCUBE_H
#define MCUBE_H


class MCube : public MObject
{
protected:
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 left = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 back = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 zero = glm::vec3(0.0f, 0.0f, 0.0f);

	std::vector< glm::vec3 > verts;
	std::vector< glm::vec3 > normals;
	std::vector< glm::vec2 > uvs;
	std::vector< size_t > tris;
public:
	void OnAwake()
	{
		Texture.Load("snow.jpg");
		Transform.Position.x = 1.0f;
		glm::vec3 offset(-0.5f, -0.5f, +0.5f);
		BuildFace(zero + offset, right, up);
		BuildFace(right + offset, front, up);
		BuildFace(right + front + offset, left, up);
		BuildFace(front + offset, back, up);
		BuildFace(up + offset, right, front);
		BuildFace(zero + offset, front, right);
	
		Mesh.verts = verts;
		Mesh.normals = normals;
		Mesh.uvs = uvs;
		Mesh.tris = tris;
	}
	void OnUpdate()
	{
		Transform.Rotation.y++;
		Transform.Rotation.z++;
		Transform.Rotation.x++;
	}

	void BuildFace(glm::vec3 position, glm::vec3 offset1, glm::vec3 offset2)
	{
		size_t index = verts.size();

		verts.push_back(position);
		verts.push_back(position + offset1);
		verts.push_back(position + offset2);
		verts.push_back(position + offset1 + offset2);

		normals.push_back(glm::cross(offset1, offset2));
		normals.push_back(normals[normals.size() - 1]);
		normals.push_back(normals[normals.size() - 1]);
		normals.push_back(normals[normals.size() - 1]);

		uvs.push_back(glm::vec2(0.0f, 0.0f));
		uvs.push_back(glm::vec2(0.0f, 1.0f));
		uvs.push_back(glm::vec2(1.0f, 0.0f));
		uvs.push_back(glm::vec2(1.0f, 1.0f));

		tris.push_back(index + 0);
		tris.push_back(index + 1);
		tris.push_back(index + 2);
		tris.push_back(index + 3);
		tris.push_back(index + 2);
		tris.push_back(index + 1);
	}
};


#endif