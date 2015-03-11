#ifndef MOBJECT_H
#define MOBJECT_H

class MObject
{
protected:
	MMesh Mesh;
	MTexture Texture;

	virtual void OnAwake() {}
	virtual void OnUpdate() {}
	virtual void OnRender() {}
public:
	MTransform Transform;

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
		OnRender();
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