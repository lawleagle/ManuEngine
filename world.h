#ifndef MWORLD_H
#define	MWORLD_H


class MWorld
{
private:
	MFloor Floor;
	MSuzanne Suzanne;
	MCube Cube;
	MDirectionalLight SunLight;
public:
	void Awake()
	{
		SunLight.Awake();
		Floor.Awake();
		Suzanne.Awake();
		Cube.Awake();
	}
	void Update()
	{
		SunLight.Update();
		Floor.Update();
		Suzanne.Update();
		Cube.Update();
	}
	void Render()
	{
		SunLight.Render();
		Floor.Render();
		Suzanne.Render();
		Cube.Render();
	}
};


#endif