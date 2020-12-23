#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class Alien : public GameObject
{
public:
	Alien();
	Alien(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	Alien(const Alien& s);
	virtual ~Alien(void);

	virtual void Update(int t);
	virtual void Render(void);
	virtual void Rotate(float r);

	void SetAlienShape(shared_ptr<Shape> alien_ship) { mSpaceshipShape = alien_ship; }
	void SetAlien(shared_ptr<GameObject>ptr) { alienShip = ptr; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

private:
	float mThrust;

	shared_ptr<Shape> mSpaceshipShape;
	shared_ptr<Shape> mThrusterShape;
	shared_ptr<GameObject> alienShip;
};

#endif