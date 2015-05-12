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

	std::vector<MAsteroid> Asteroids;
	std::vector<glm::vec3> Directions;
	float angle = 1.57f;


	glm::vec3 gravity = glm::vec3(0.0f, -25.0f, 0.0f);
	bool started = false;
public:
	void Awake()
	{
		Shader.Create("red.vsh", "red.fsh", "red");
		Shader.Create("plain.vsh", "plain.fsh", "plain");


		Player.Awake(); Player.Transform.Position = glm::vec3(0.0f, 1050.0f, 0.0f);
		Skybox.Awake();
		SunLight.Awake();
		//Boundry.Awake();


		// From here on it's awaking the objects
		for (int i = 1; i <= 100; i++) {
			int nr = Random.getInt(1, 5);
			for (int j = 1; j <= nr; j++) {
				MAsteroid Asteroid;
				Asteroid.Transform.Position = glm::vec3(Random.getFloat(-50.0f, 50.0f), i * 10.0f + Random.getFloat(-5.0f, 5.0f), Random.getFloat(-50.0f, 50.0f));
				Asteroid.Transform.Scale = glm::vec3(Random.getFloat(1.0f, 15.0f), 1.0f, Random.getFloat(1.0f, 15.0f));
				Asteroids.push_back(Asteroid);

				Directions.push_back(glm::vec3(Random.getFloat(0.0f, 10.0f), 0.0f, Random.getFloat(0.0f, 10.0f)));
			}
		}
	}
	void Update()
	{
		if (!started) Player.Transform.Position = glm::vec3(0.0f, 1050.0f, 0.0f);
		if (Input.GetKey(GLFW_KEY_F)) started = true;
		if (started == true) {
			Player.Velocity += gravity * Time.deltaTime;
		}
		Player.Transform.Position += Player.Velocity * Time.deltaTime;
		Player.Update();
		



		Shader.Use("plain");
		Skybox.Update(Player.Transform.Position);


		Shader.Use("red");
		SunLight.Update();

		
		// From here on it's the updating of objects.
		for (size_t i = 0; i < Asteroids.size(); i++) {
			if (Asteroids[i].Transform.Position.y - 10.0f > Player.Transform.Position.y)
			{
				Asteroids[i].Transform.Position.y -= 1000.0f;
			}
			if (Asteroids[i].Collides(Player.Transform.Position)) {
				Player.Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				Player.Transform.Position = glm::vec3(0.0f, 1050.0f, 0.0f);
				started = false;
				for (size_t i = 0; i < Asteroids.size(); i++) {
					while (Asteroids[i].Transform.Position.y <= 0.0f) Asteroids[i].Transform.Position.y += 1000.0f;
				}
			}
			Asteroids[i].Transform.Position += Directions[i] * sin(angle) * Time.deltaTime;
			Asteroids[i].Update();
		}
		angle += 0.01f;
	}
	void Render()
	{
		Shader.Use("plain");
		Skybox.Render();


		Shader.Use("red");
		SunLight.Render();
		Player.Render();

		
		// From here on it's the rendering of objects.
		for (size_t i = 0; i < Asteroids.size(); i++) {
			Asteroids[i].Render();
		}
	}
	void Delete()
	{
	}
};


#endif