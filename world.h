#ifndef MWORLD_H
#define	MWORLD_H


extern MShader Shader;
class MWorld
{
private:
	MDirectionalLight SunLight;
	MPlayer Player;
	MSkybox Skybox;

	MFloor Floor, Floor2;
	MSuzanne Suzanne;
	MCube Cube;
	MRobot Robot;
public:
	void Awake()
	{
		Shader.Create("red.vsh", "red.fsh", "red");
		Shader.Create("plain.vsh", "plain.fsh", "plain");


		Player.Awake();


		Shader.Use("plain");
		Skybox.Awake();


		Shader.Use("red");
		SunLight.Awake();

		Cube.Awake();
		Floor.Awake();
		Floor2.Awake(); Floor2.Transform.Position.y += 5;
		Suzanne.Awake();
		Robot.Awake();
	}
	void Update()
	{
		Player.Update();


		Shader.Use("plain");
		Skybox.Update(Player.Transform.Position);


		Shader.Use("red");
		SunLight.Update();

		Cube.Update();
		Floor.Update();
		Floor2.Update();
		Suzanne.Update();
		Robot.Update();
	}
	void Render()
	{
		Shader.Use("plain");
		Skybox.Render();


		Shader.Use("red");
		SunLight.Render();
		Player.Render();

		Floor.Render();
		Floor2.Render();
		Suzanne.Render();
		Cube.Render();
		Robot.Render();
	}
};


#endif