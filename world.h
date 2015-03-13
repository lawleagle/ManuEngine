#ifndef MWORLD_H
#define	MWORLD_H


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
		SunLight.Awake();
		Player.Awake();
		Skybox.Awake();

		Cube.Awake();
		Floor.Awake();
		Floor2.Awake(); Floor2.Transform.Position.y += 5;
		Suzanne.Awake();
		Robot.Awake();
	}
	void Update()
	{
		SunLight.Update();
		Player.Update();
		Skybox.Update(Player.Transform.Position);

		Cube.Update();
		Floor.Update();
		Floor2.Update();
		Suzanne.Update();
		Robot.Update();
	}
	void Render()
	{
		SunLight.Render();
		Player.Render();
		Skybox.Render();

		Floor.Render();
		Floor2.Render();
		Suzanne.Render();
		Cube.Render();
		Robot.Render();
	}
};


#endif