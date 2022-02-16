/*
 -----------------------------------------------------------------------------
 Filename:    as1.cpp
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

#include <Assignment2.h>
#include <string>
#include <vector>
#include <EntityMgr.h>
#include <Entity381.h>
using namespace Ogre;

bool as2::upDownLastFrame = false;
bool as2::downDownLastFrame = false;
bool as2::leftDownLastFrame = false;
bool as2::rightDownLastFrame = false;
bool as2::pgUpDownLastFrame = false;
bool as2::pgDownDownLastFrame = false;
bool as2::spaceDownLastFrame = false;
bool as2::qDownLastFrame = false;
bool as2::tabDownLastFrame = false;
int EntityID = 0;
int spacing = 200;
float rotateCam = 0.1;
EntityMgr entMgr;
EntityMgr *entMgrPt;

//---------------------------------------------------------------------------
as2::as2(void) {}
//---------------------------------------------------------------------------
as2::~as2(void) { }

//---------------------------------------------------------------------------
void as2::createScene(void) {
	// Set the ambient light color and enable shadows
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE); 
	// Cloudy Sky Dome
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

	//Create EntityMgr
	entMgrPt = &entMgr;
	entMgrPt->sceneMgr = mSceneMgr;

	//Create Entities, Planes
	static Ogre::Vector3 initialPlacementVec(-400,100,-200);
	for(int i = 0; i < 5; i++)
	{
		entMgrPt->createEntity("PolyPlane.mesh", initialPlacementVec, EntityID);
		initialPlacementVec.x += spacing;
	}
	//Create Entities, CG47
	initialPlacementVec.x = -400;
	initialPlacementVec.y = surfaceHeight;
	initialPlacementVec.z = 0;
	for(int i = 0; i < 5; i++)
	{
		entMgrPt->createEntity("cg47.mesh", initialPlacementVec, EntityID);
		initialPlacementVec.x += spacing;
	}


	// Position the camera and set its direction
	mCamera->setPosition(0, 200, 900);
	mCamera->lookAt(0, 0, -300);

	// Add a light to the scene (if we don't add this all we will see is a field of black)
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL); // Make the light a directional lightS
	light->setPosition(20, 80, 50);
	light->setDirection(2, -3, 0);

	// Create a plane facing upward which we will generate some additional resources from
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	// Create a ground plane
	Ogre::MeshManager::getSingleton().createPlane("ocean", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000, 10000, 20, 20, true, 1,100,100, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ocean");
	Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	groundEntity->setMaterialName("Examples/Water2"); // Texture the plane with grass
	groundNode->attachObject(groundEntity);
	groundNode->setPosition(0, surfaceHeight, 0); // Position the plan with respect to the surface height
	
}
//---------------------------------------------------------------------------
bool as2::frameRenderingQueued(const Ogre::FrameEvent& fe) {
	// Process all of the frame rendering from base application (saving if we should keep the application running)
	bool ret = BaseApplication::frameRenderingQueued(fe);

	// Process our unbuffered input
	if(!processUnbufferedInput(fe))
		return false;

	// Return if we should keep the application running
	return ret;
}
//---------------------------------------------------------------------------
bool as2::processUnbufferedInput(const Ogre::FrameEvent& fe) {
	// Exit the program
	for(int i = 0; i<entMgr.entityCount;i++)
	{
		entMgr.entitySet[i]->entityNode->showBoundingBox(false);
		if(i == entMgr.currentEntityIndex)
			{
				entMgr.entitySet[entMgr.currentEntityIndex]->entityNode->showBoundingBox(true);
			}
	}

	if(mKeyboard->isKeyDown(OIS::KC_Q))
		return false; // Returning false indicates that we should exit
	//Cycle Entity (Round Robin)
	bool tabDown = mKeyboard->isKeyDown(OIS::KC_TAB);
	if(tabDown && !tabDownLastFrame)
	{
		entMgr.nextEntity();
	}
	tabDownLastFrame = tabDown;

	// Update the camera's position based on the held keys
	Ogre::Vector3 cameraPosition = mCamera->getPosition();
	if(mKeyboard->isKeyDown(OIS::KC_W)) cameraPosition += Ogre::Vector3(0, 0, -cameraStep) * fe.timeSinceLastFrame;
	if(mKeyboard->isKeyDown(OIS::KC_S)) cameraPosition += Ogre::Vector3(0, 0, cameraStep) * fe.timeSinceLastFrame;
	if(mKeyboard->isKeyDown(OIS::KC_A))
		{
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				mCamera->yaw(Degree(2.5*rotateCam));
			}
			else
			{
				cameraPosition += Ogre::Vector3(-cameraStep, 0, 0) * fe.timeSinceLastFrame;

			}
		}
	if(mKeyboard->isKeyDown(OIS::KC_D))
		{
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				mCamera->yaw(Degree(-2.5*rotateCam));
			}
			else
			{
				cameraPosition += Ogre::Vector3(cameraStep, 0, 0) * fe.timeSinceLastFrame;
			}
		}
	if(mKeyboard->isKeyDown(OIS::KC_E)) cameraPosition += Ogre::Vector3(0, cameraStep, 0) * fe.timeSinceLastFrame;
	if(mKeyboard->isKeyDown(OIS::KC_F)) cameraPosition += Ogre::Vector3(0, -cameraStep, 0) * fe.timeSinceLastFrame;

	mCamera->setPosition(cameraPosition);


	// Adjust the PolyPlane's velocity with arrow keys and pgup/down
	bool upDown = mKeyboard->isKeyDown(OIS::KC_UP);
	bool downDown = mKeyboard->isKeyDown(OIS::KC_DOWN);
	bool leftDown = mKeyboard->isKeyDown(OIS::KC_LEFT);
	bool rightDown = mKeyboard->isKeyDown(OIS::KC_RIGHT);
	bool pgUpDown = mKeyboard->isKeyDown(OIS::KC_PGUP);
	bool pgDownDown = mKeyboard->isKeyDown(OIS::KC_PGDOWN);
	if(upDown && !upDownLastFrame) entMgr.entitySet[entMgr.currentEntityIndex]->entityVelocity  += Ogre::Vector3(0, 0, -velocityStep);
	if(downDown && !downDownLastFrame) entMgr.entitySet[entMgr.currentEntityIndex]->entityVelocity  += Ogre::Vector3(0, 0, velocityStep);
	if(leftDown && !leftDownLastFrame) entMgr.entitySet[entMgr.currentEntityIndex]->entityVelocity  += Ogre::Vector3(-velocityStep, 0, 0);
	if(rightDown && !rightDownLastFrame) entMgr.entitySet[entMgr.currentEntityIndex]->entityVelocity  += Ogre::Vector3(velocityStep, 0, 0);
	if(pgUpDown && !pgUpDownLastFrame) entMgr.entitySet[entMgr.currentEntityIndex]->entityVelocity  += Ogre::Vector3(0, velocityStep, 0);
	if(pgDownDown && !pgDownDownLastFrame) entMgr.entitySet[entMgr.currentEntityIndex]->entityVelocity  += Ogre::Vector3(0, -velocityStep, 0);
	// Update the key state for the next frame
	upDownLastFrame = upDown;
	downDownLastFrame = downDown;
	leftDownLastFrame = leftDown;
	rightDownLastFrame = rightDown;
	pgUpDownLastFrame = pgUpDown;
	pgDownDownLastFrame = pgDownDown;

	// Space resets the velocity of the plane
	bool spaceDown = mKeyboard->isKeyDown(OIS::KC_SPACE);
	if(spaceDown && !spaceDownLastFrame) entMgr.entitySet[entMgr.currentEntityIndex]->entityVelocity  = Ogre::Vector3::ZERO;
	spaceDownLastFrame = spaceDown;

	entMgrPt->tick(fe.timeSinceLastFrame);

	// Update the plane's velocity
	// Position = Velocity * DT
	//polyPlaneNode->setPosition(polyPlaneNode->getPosition() + polyPlaneVelocity * fe.timeSinceLastFrame);
	
	return true;
}
//---------------------------------------------------------------------------

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
	as2 app;

	try {
		app.go();
	} catch (Ogre::Exception &e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occurred: "
				<< e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
