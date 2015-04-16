#ifndef MWORLD_H
#define	MWORLD_H


extern MShader Shader;
extern MCamera Camera;
class MWorld
{
protected:
	MDirectionalLight SunLight;
	MPlayer Player;
	MSkybox Skybox;

	MFloor Floor;
	std::vector<MSphere> Spheres;
public:
	void Awake()
	{
		Shader.Create("red.vsh", "red.fsh", "red");
		Shader.Create("plain.vsh", "plain.fsh", "plain");


		Player.Awake();
		Skybox.Awake();
		SunLight.Awake();

		Floor.Awake();
	}
	void Update()
	{
		if (Input.GetKeyDown(GLFW_KEY_F))
		{
			MSphere Sphere;
			Sphere.Awake();
			Sphere.setPosition(Camera.Transform.Position);
			Sphere.setVelocity(Camera.Transform.GetFront() * 200.0f);
			Spheres.push_back(Sphere);
		}
		if (Spheres.size() > 20)
		{
			Spheres[0].Delete();
			Spheres.erase(Spheres.begin());
		}


		Player.Update();


		Shader.Use("plain");
		Skybox.Update(Player.Transform.Position);


		Shader.Use("red");
		SunLight.Update();
		Floor.Update();
		for (int i = 0; i < Spheres.size(); i++) {
			Spheres[i].Update();
		}
	}
	void Render()
	{
		Shader.Use("plain");
		Skybox.Render();


		Shader.Use("red");
		SunLight.Render();
		Player.Render();
		Floor.Render();
		for (int i = 0; i < Spheres.size(); i++) {
			Spheres[i].Render();
		}
	}
	void Delete()
	{
		Floor.Delete();
		for (int i = 0; i < Spheres.size(); i++) {
			Spheres[i].Delete();
		}
		while (!Spheres.empty()) {
			Spheres.pop_back();
		}
	}
};


#endif