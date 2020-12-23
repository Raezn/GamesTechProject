#include "GameUtil.h"
#include "GameWorld.h"
#include "Alien.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Alien::Alien()
	: GameObject("Alien")
{
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Alien::Alien(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Alien", p, v, a, h, r), mThrust(0)
{
}

/** Copy constructor. */
Alien::Alien(const Alien& s)
	: GameObject(s), mThrust(0)
{
}

/** Destructor. */
Alien::~Alien(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this alien */
void Alien::Update(int t)
{
	mAngle = (atan2f(mPosition.y - alienShip->GetPosition().y, mPosition.x - alienShip->GetPosition().x) * 180 / 3.14f) - 180.0f;
	mVelocity.x = 15*cos(DEG2RAD*mAngle);
	mVelocity.y = 15*sin(DEG2RAD*mAngle);

	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void Alien::Render(void)
{
	if (mSpaceshipShape.get() != NULL) mSpaceshipShape->Render();

	// If ship is thrusting
	if ((mThrust > 0) && (mThrusterShape.get() != NULL)) {
		mThrusterShape->Render();
	}

	GameObject::Render();
}


/** Set the rotation. */
void Alien::Rotate(float r)
{
	mRotation = r;
}

bool Alien::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() == GameObjectType("Asteroid")) return false;
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());


}

void Alien::OnCollision(const GameObjectList &objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}