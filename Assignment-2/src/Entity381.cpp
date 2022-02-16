#include <Entity381.h>

Entity381::Entity381(Ogre::SceneManager* passedSceneMgr, string meshfile, Ogre::Vector3 position, int ID)
{
	entityID = ID;
	entityName = meshfile;
	entityVelocity = Ogre::Vector3::ZERO;
	entityPosition = position;
	entity = passedSceneMgr->createEntity(meshfile);
	entityNode = passedSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	entityNode->attachObject(entity);
}


Entity381::~Entity381(){}

void Entity381::tick(float dt)
{
	entityPosition = entityNode->getPosition()+entityVelocity*dt;
	entityNode->setPosition(entityPosition);
}
