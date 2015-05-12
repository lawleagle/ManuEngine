#ifndef MASTEROID_H
#define MASTEROID_H


extern MRandom Random;
extern MCamera Camera;
class MAsteroid : public MObject
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



	glm::vec3 movingSpeed;
	glm::vec3 rotationSpeed;
	glm::vec3 gravity;
	float speedMultiplier = 1.0f;
	float rotationMultiplier = 1.0f;
	


	void onAwake()
	{
	}
	void onUpdate()
	{
		/*gravity = Camera.Transform.Position - Transform.Position; gravity /= 100; gravity = glm::normalize(gravity);
		movingSpeed += (glm::vec3(gravity.x / 10, gravity.y / 10, gravity.z / 10));
		Transform.Position += movingSpeed * speedMultiplier;
		Transform.Rotation += rotationSpeed * rotationMultiplier;*/
		
		//Transform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
		//std::cout << Transform.Position.x << ' ' << Transform.Position.y << ' ' << Transform.Position.z << std::endl;
	}
public:
	MAsteroid(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		MObject::Awake();
		Texture.Load("rust.jpg");
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

		/*if (position == glm::vec3(0.0f, 0.0f, 0.0f) &&
			scale == glm::vec3(1.0f, 1.0f, 1.0f) &&
			speed == glm::vec3(0.0f, 0.0f, 0.0f) &&
			rotation == glm::vec3(0.0f, 0.0f, 0.0f))
		{
			Transform.Position.x = Camera.Transform.Position.x + Random.getInt(-100, 100);
			Transform.Position.y = Camera.Transform.Position.y + Random.getInt(-100, 100);
			Transform.Position.z = Camera.Transform.Position.z + Random.getInt(-100, 100);

			Transform.Rotation.x = Random.getFloat(0.0f, 1.0f);
			Transform.Rotation.y = Random.getFloat(0.0f, 1.0f);
			Transform.Rotation.z = Random.getFloat(0.0f, 1.0f);

			int key = Random.getInt(1, 3);
			if (key == 1) Transform.Rotation.x = 0.0f;
			if (key == 2) Transform.Rotation.y = 0.0f;
			if (key == 3) Transform.Rotation.z = 0.0f;
		}
		else
		{
			Transform.Position = position;
			Transform.Scale = scale;
			movingSpeed = speed;
			rotationSpeed = rotation;
		}*/
	}
	
	bool Collides(glm::vec3 position)
	{
		float diff = 0.3f;
		if (Transform.Position.x - Transform.Scale.x / 2 - diff <= position.x && position.x <= Transform.Position.x + Transform.Scale.x / 2 + diff &&
			Transform.Position.y - Transform.Scale.y / 2 - diff <= position.y && position.y <= Transform.Position.y + Transform.Scale.y / 2 + diff &&
			Transform.Position.z - Transform.Scale.z / 2 - diff <= position.z && position.z <= Transform.Position.z + Transform.Scale.z / 2 + diff) {
			return true;
		}
		return false;
	}

	void setSpeed(glm::vec3 _speed)
	{
		rotationSpeed = _speed;
	}


	
};


#endif