#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <Entity381.h>
#include <OgreSceneManager.h>
#include <vector>
#include <string>
using namespace std;

class EntityMgr{
public:
	EntityMgr(Ogre::SceneManager*);
	EntityMgr();

	vector<Entity381*> entitySet;
	Entity381* currentEntity;
	int currentEntityIndex;
	Ogre::SceneManager* sceneMgr;
	int entityCount;

	void nextEntity();
	void tick(float dt);
	void createEntity(string, Ogre::Vector3,int);
private:


};

#endif
