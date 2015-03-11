#ifndef MOBJECT_H
#define MOBJECT_H

extern MCamera Camera;
class MObject
{
protected:
	MMesh Mesh;
	MTransform Transform;
	MTexture Texture;

	virtual void OnAwake() {}
	virtual void OnUpdate() {}
public:
	bool hasTransparency = false;
	MObject()
	{

	}
	void Awake()
	{
		OnAwake();
	}
	void Update()
	{
		OnUpdate();
		Transform.Update();
		Mesh.Update();
	}
	void Render()
	{
		if (hasTransparency) {
			glEnable(GL_BLEND);
			glDepthMask(0);
		}
		Texture.Use();
		Transform.Render();
		Mesh.Render();

		if (hasTransparency) {
			glDisable(GL_BLEND);
			glDepthMask(1);
		}
	}
};


#endif