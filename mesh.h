#ifndef MMESH_H
#define MMESH_H


class MMesh
{
public:
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;
public:
	bool unindexed = false;
	std::vector< glm::vec3 > verts;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	std::vector< size_t > tris;

	MMesh()
	{
		
	}
	void Reset()
	{
		verts.clear();
		uvs.clear();
		normals.clear();
	}
	void LoadOBJ(std::string file_path)
	{
		std::cout << "Loading OBJ mesh: " << file_path << std::endl;
		file_path = "Assets/models/" + file_path;

		FILE* file = fopen(file_path.c_str(), "rb");
		if (file == NULL) {
			std::cerr << "Can't open file." << std::endl;
			return;
		}
		Reset();

		std::vector< size_t > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_verts;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;

		while (1)
		{
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) break;

			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_verts.push_back(vertex);
			}
			if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			if (strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			if (strcmp(lineHeader, "f") == 0)
			{
				std::string vertex1, vertex2, vertex3;
				size_t vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9){
					std::cerr << "File can't be read by my simple parser." << std::endl;
					return;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		for (size_t i = 0; i < vertexIndices.size(); i++)
		{
			size_t vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_verts[vertexIndex - 1];
			verts.push_back(vertex);
		}
		for (size_t i = 0; i < uvIndices.size(); i++)
		{
			size_t uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			uvs.push_back(uv);
		}
		for (size_t i = 0; i < normalIndices.size(); i++)
		{
			size_t normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			normals.push_back(normal);
		}
		unindexed = true;
		std::cout << "[COMPLETE]\n" << std::endl;
	}
	void Update()
	{
		if (!verts.size() || !uvs.size() || !normals.size()) {
			return;
		}
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* verts.size(), &verts[0], GL_STATIC_DRAW);

		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)* uvs.size(), &uvs[0], GL_STATIC_DRAW);

		glGenBuffers(1, &normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

		if (unindexed == false) {
			glGenBuffers(1, &elementbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, elementbuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(size_t)* tris.size(), &tris[0], GL_STATIC_DRAW);
		}
	}
	void Render()
	{
		if (!verts.size() || !uvs.size() || !normals.size()) {
			return;
		}

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);


		if (unindexed == false){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
			glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, NULL);
		} else {
			glDrawArrays(GL_TRIANGLES, 0, verts.size());
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
};


#endif