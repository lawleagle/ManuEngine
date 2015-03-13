#ifndef MSPHERE_H
#define MSPHERE_H


class MSphere : public MObject
{
protected:
	GLUquadricObj* quad;
	void OnAwake()
	{
		Texture.Load("snow.jpg");
		Mesh.Load("sphere.obj");
		Transform.Position = glm::vec3(4.0f, 0.0f, 0.0f);
	}
public:
};


#endif