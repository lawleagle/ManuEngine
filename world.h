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
	std::vector<MSphere> spheres;
	std::vector<MCube> cubes;
	MSpaceship Spaceship;
public:
	void Awake()
	{
		Shader.Create("red.vsh", "red.fsh", "red");
		Shader.Create("plain.vsh", "plain.fsh", "plain");
		Shader.Create("specular.vsh", "specular.fsh", "specular");


		Player.Awake(); Player.Transform.Position = glm::vec3(0.0f, 5.0f, 0.0f);
		Skybox.Awake();
		SunLight.Awake();

		


		// From here on it's awaking the objects
		Floor.Awake();
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {
				MCube Cube; Cube.Awake(glm::vec3(2 * i, 2 * j, -10));
				cubes.push_back(Cube);
			}
		}
		Spaceship.Awake();
	}
	void Update()
	{
		Player.Transform.Position += Player.Velocity * Time.deltaTime;
		Player.Update();



		Shader.Use("plain");
		Skybox.Update(Player.Transform.Position);


		Shader.Use("red");
		SunLight.Update();

		
		// From here on it's the updating of objects.
		if (Input.GetKeyDown(GLFW_KEY_F)) {
			MSphere Sphere; Sphere.Awake(Camera.Transform.Position);
			Sphere.setVelocity(Camera.Transform.GetFront() * 50.0f);
			spheres.push_back(Sphere);
		}
		if (Input.GetKeyDown(GLFW_KEY_C)) {
			MCube Cube; Cube.Awake(Camera.Transform.Position);
			Cube.setVelocity(Camera.Transform.GetFront() * 1.0f);
			cubes.push_back(Cube);
		}

		Floor.Update();
		for (int i = 0; i < spheres.size(); i++) {
			spheres[i].Update();
		}
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].Update();
		}
		Spaceship.Update();
	}
	void Render()
	{
		Shader.Use("plain");
		Skybox.Render();


		Shader.Use("red");
		SunLight.Render();
		Floor.Render();

		
		// From here on it's the rendering of objects.
		Shader.Use("specular");
		SunLight.Render();
		for (int i = 0; i < spheres.size(); i++) {
			spheres[i].Render();
		}
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].Render();
		}
		//Spaceship.Render();
	}
	void Delete()
	{
	}
};


#endif