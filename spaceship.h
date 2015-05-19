#ifndef MSPACESHIP_H
#define MSPACESHIP_H


extern MCamera Camera;
class MSpaceship : public MObject
{
private:
	void onAwake()
	{
		Texture.Load("gray.jpg");
		Mesh.Load("Ship2.obj");
	}
	void onUpdate()
	{
		Transform.Position = Camera.Transform.Position + 15.0f * Camera.Transform.GetFront() + glm::vec3(0.0f, -2.0f, 0.0f);
	}
public:
};


#endif;