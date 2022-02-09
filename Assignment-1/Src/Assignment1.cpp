/*
Filename: Assignment0.cpp
Developer Name: Michael Dorado
Developer Email: michaeldorado@nevada.unr.edu
*/

#include <Assignment1.h>
#include "OgrePlane.h"
#include "OgreMeshManager.h"
#include "OgreResourceGroupManager.h"
#include "OgreLight.h"
using namespace std;

Ogre::Real toggleTimer = 0.0;

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

	//Camera and light Settings
	mCamera->lookAt(0, 0, -300);
	mCamera->setPosition(0, 30, 400);
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    Ogre::Light* directionalLight = mSceneMgr->createLight();
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDirection(Ogre::Vector3(2, -3, 0));
    directionalLight->setDiffuseColour(Ogre::ColourValue(1,1,1));
    directionalLight->setSpecularColour(Ogre::ColourValue(1, 1,1));


    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);


    Ogre::Entity* AirplaneEntity  = mSceneMgr->createEntity("PolyPlane.mesh");
    Ogre::SceneNode* AirplaneNode= mSceneMgr->getRootSceneNode()->createChildSceneNode("AirplaneNode");
    AirplaneNode->attachObject(AirplaneEntity);


    //Ground Settings
    int surfaceHeight = -3.5;
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y,surfaceHeight);
	Ogre::MeshManager::getSingleton().createPlane(
	 "ground",
	 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	 plane,
	 1500,1500,20,20,
	 true,
	 1, 5, 5,
	Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setMaterialName("381/Grass");



}
//---------------------------------------------------------------------------

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{


	bool ret = BaseApplication::frameRenderingQueued(fe);
	if(!processUnbufferedInput(fe))
		  return false;
	//toggleTimer -= fe.timeSinceLastFrame;

	return ret;
}
//---------------------------------------------------------------------------
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	//Variables for I/O section
	static Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	Ogre::Vector3 camDirVec = Ogre::Vector3::ZERO;
	static Ogre::Real camMove = 30;
	Ogre::Real movez = 0;
	Ogre::Real movey = 0;
	Ogre::Real movex = 0;



	//Section for the planes unbuffered physics
	toggleTimer -= fe.timeSinceLastFrame;

	if (toggleTimer < 0){
		toggleTimer = .1;
		if (mKeyboard->isKeyDown(OIS::KC_UP)){
			movez += 1000;
			dirVec.z = (dirVec.z + movez*fe.timeSinceLastFrame);
		}
		if (mKeyboard ->isKeyDown(OIS::KC_DOWN)){
			movez += 1000;
			dirVec.z = (dirVec.z - movez*fe.timeSinceLastFrame);
		}
		if (mKeyboard->isKeyDown(OIS::KC_PGUP)){
			movey += 1000;
			dirVec.y = (dirVec.y + movey*fe.timeSinceLastFrame);
		}
		if (mKeyboard->isKeyDown(OIS::KC_PGDOWN)){
			movey += 1000;
			dirVec.y = (dirVec.y - movey*fe.timeSinceLastFrame);
		}
		if (mKeyboard->isKeyDown(OIS::KC_RIGHT)){
			movex += 1000;
			dirVec.x = (dirVec.x + movex*fe.timeSinceLastFrame);
		}
		if (mKeyboard->isKeyDown(OIS::KC_LEFT)){
			movex += 1000;
			dirVec.x = (dirVec.x - movex*fe.timeSinceLastFrame);
		}
	}


	if (mKeyboard->isKeyDown(OIS::KC_SPACE)){
		dirVec = Ogre::Vector3::ZERO;
		movex = 0;
		movey= 0;
		movez = 0;
	}
	if (mKeyboard->isKeyDown(OIS::KC_Q)){
		mShutDown = true;
	}

	//Camera I/O controls
	//+Z
	if (mKeyboard->isKeyDown(OIS::KC_W)){
		camDirVec.z -= camMove;
	}
	//-Z
	if (mKeyboard ->isKeyDown(OIS::KC_S)){
		camDirVec.z += camMove;
	}
	//+Y
	if (mKeyboard->isKeyDown(OIS::KC_E)){
		camDirVec.y += camMove;
	}
	//-Y
	if (mKeyboard->isKeyDown(OIS::KC_F)){
		camDirVec.y -= camMove;
	}
	//+X
	if (mKeyboard->isKeyDown(OIS::KC_D)){
		camDirVec.x += camMove;
	}
	//-X
	if (mKeyboard->isKeyDown(OIS::KC_A)){
		camDirVec.x -= camMove;
	}


	//Render the frames based on the performance of the machine for the plane
	mSceneMgr->getSceneNode("AirplaneNode")->translate(
	  dirVec * fe.timeSinceLastFrame,
	  Ogre::Node::TS_LOCAL);

	//Move the camera
	mSceneMgr->getCamera("PlayerCam")->move(
			camDirVec * fe.timeSinceLastFrame);
			//Ogre::Node::TS_LOCAL);
	return true;
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
