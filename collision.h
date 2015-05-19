#ifndef MCOLLISION_H
#define MCOLLISION_H


enum MCollisionShape
{
	COLLISION_PLANE,
	COLLISION_SPHERE,
	COLLISION_CUBE
};


extern btDynamicsWorld* DynamicsWorld;
extern std::vector<btRigidBody*> Bodies;
class MCollision
{
private:
	int BodyID;
public:
	MCollisionShape Shape;
	btTransform Transform;
	btRigidBody* RigidBody;
	bool isCreated;

	MCollision()
	{
		isCreated = false;
	}
	
	void CreateCollisionMesh(MCollisionShape shape, float width, float depth, glm::vec3 origin)
	{
		if (shape != COLLISION_PLANE || isCreated) {
			return;
		}
		Transform.setIdentity();
		Transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
		btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0.0f, 1.0f, 0.0f), 0.0f);
		btMotionState* motion = new btDefaultMotionState(Transform);
		btRigidBody::btRigidBodyConstructionInfo info(0.0f, motion, plane);  // mass, motionstate, collision_state
		RigidBody = new btRigidBody(info);
		DynamicsWorld->addRigidBody(RigidBody);

		Bodies.push_back(RigidBody);
		isCreated = true;
	}

	void CreateCollisionMesh(MCollisionShape shape, float radius, glm::vec3 origin, btScalar mass)
	{
		if (shape != COLLISION_SPHERE || isCreated) {
			return;
		}

		Transform.setIdentity();
		Transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
		btCollisionShape* sphere = new btSphereShape(radius);
		btVector3 inertia(0.0f, 0.0f, 0.0f);
		if (mass != 0.0f) {
			sphere->calculateLocalInertia(mass, inertia);
		}

		btMotionState* motion = new btDefaultMotionState(Transform);
		btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);
		RigidBody = new btRigidBody(info);
		DynamicsWorld->addRigidBody(RigidBody);

		Bodies.push_back(RigidBody);
		isCreated = true;
	}
	void CreateCollisionMesh(MCollisionShape shape, float width, float height, float depth, glm::vec3 origin, btScalar mass)
	{
		if (shape != COLLISION_CUBE || isCreated) {
			return;
		}

		Transform.setIdentity();
		Transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
		btCollisionShape* cube = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
		btVector3 inertia(0.0f, 0.0f, 0.0f);
		if (mass != 0.0f) {
			cube->calculateLocalInertia(mass, inertia);
		}

		btMotionState* motion = new btDefaultMotionState(Transform);
		btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cube, inertia);
		RigidBody = new btRigidBody(info);
		DynamicsWorld->addRigidBody(RigidBody);

		Bodies.push_back(RigidBody);
		isCreated = true;
	}
	void DeleteCollisionMesh()
	{
		DynamicsWorld->removeCollisionObject(RigidBody);
		btMotionState* motionState = RigidBody->getMotionState();
		btCollisionShape* shape = RigidBody->getCollisionShape();
		delete motionState;
		delete shape;
		delete RigidBody;

		isCreated = false;
	}

	// Can be optimized. It updates static objects too.
	void Update()
	{
		RigidBody->getMotionState()->getWorldTransform(Transform);
	}
};


#endif