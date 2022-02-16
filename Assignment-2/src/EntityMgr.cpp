#include <EntityMgr.h>

EntityMgr::EntityMgr(Ogre::SceneManager* passedSceneMgr)
{
	currentEntityIndex = -1;
	sceneMgr = passedSceneMgr;
	entityCount = 0;
	currentEntity = 0;

}


EntityMgr::EntityMgr(){}


void EntityMgr::createEntity(string meshfile, Ogre::Vector3 position, int ID)
{
	Entity381* entity381 = new Entity381(sceneMgr, meshfile, position, ID);
	entityCount++;
	entitySet.push_back((Entity381 *) entity381);
}


void EntityMgr::nextEntity()
{
	if(currentEntityIndex == entityCount-1)
	{
		currentEntityIndex = 0;
	}
	else
	{
		currentEntityIndex++;
	}
	currentEntity = entitySet[currentEntityIndex];
}

void EntityMgr::tick(float dt)
{
	for(int i = 0; i < entityCount; i++)
	{
		entitySet[i]->tick(dt);
	}
}
