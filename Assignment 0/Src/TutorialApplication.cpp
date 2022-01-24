/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5,0.5,0.5));

    Ogre::Entity* ogreEntity1 = mSceneMgr->createEntity("cg47.mesh");
    Ogre::SceneNode* ogreNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode1->attachObject(ogreEntity1);

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);
	mCamera->setPosition(0, 120, 500);

	Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("cg47.mesh");
	Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode2->setPosition(-200,0,0);
	ogreNode2->yaw(Ogre::Degree(90));
	ogreNode2->attachObject(ogreEntity2);

	Ogre::Entity* ogreEntity3 = mSceneMgr->createEntity("cg47.mesh");
	Ogre::SceneNode* ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode3->setPosition(200,0,0);
	ogreNode3->yaw(Ogre::Degree(-90));
	ogreNode3->attachObject(ogreEntity3);

	Ogre::Entity* ogreEntity4 = mSceneMgr->createEntity("cg47.mesh");
	Ogre::SceneNode* ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode4->setPosition(-100,100,0);
	ogreNode4->yaw(Ogre::Degree(180));
	ogreNode4->setScale(1, -1, 1);
	ogreNode4->attachObject(ogreEntity4);

	Ogre::Entity* ogreEntity5 = mSceneMgr->createEntity("cg47.mesh");
		Ogre::SceneNode* ogreNode5 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		ogreNode5->setPosition(100,100,0);
		ogreNode5->yaw(Ogre::Degree(270));
		ogreNode5->setScale(1, 2, 1);
		ogreNode5->attachObject(ogreEntity5);





}
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
