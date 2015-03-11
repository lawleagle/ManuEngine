#ifndef SUZANNE_H
#define MSUZANNE_H

class MSuzanne : public MObject
{
public:
	void OnAwake()
	{
		Transform.Position.x = -1.0f;
		Texture.Load("texture.bmp");
		Mesh.LoadOBJ("suzanne.obj");
	}
	void OnUpdate()
	{
		Transform.Rotation.x--;
		Transform.Rotation.y--;
		Transform.Rotation.z--;
	}
	void OnRender()
	{
	}
};

#endif