#ifndef MROBOT_H
#define MROBOT_H


class MRobot : public MObject
{
private:
	void OnAwake()
	{
		Texture.Load("rust.jpg");
		Mesh.Load("robot.fbx");
		Transform.Position = glm::vec3(0.0f, 0.0f, -2.5f);
		Transform.Rotation.x = -90.0f;
		Transform.Scale = glm::vec3(0.2f, 0.2f, 0.2f);
	}
public:
};


#endif