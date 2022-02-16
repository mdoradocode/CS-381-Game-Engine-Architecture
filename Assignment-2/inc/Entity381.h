#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <vector>
#include <string>
using namespace std;

class Entity381
{
public:
	Entity381(Ogre::SceneManager*, string, Ogre::Vector3, int);
	~Entity381();
	int entityID;
	Ogre::String entityName;
	Ogre::Vector3 entityVelocity = Ogre::Vector3::ZERO;
	Ogre::Vector3 entityPosition = Ogre::Vector3::ZERO;
	Ogre::SceneNode* entityNode = nullptr;
	Ogre::Entity* entity;

	void tick(float dt);

};

#endif
