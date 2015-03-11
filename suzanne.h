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
		Transform.Rotation.y--;
		Transform.Rotation.z--;
		Transform.Rotation.x--;
	}
};

#endif