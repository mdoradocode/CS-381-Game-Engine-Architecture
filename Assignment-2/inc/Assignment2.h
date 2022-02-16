/*
 -----------------------------------------------------------------------------
 Filename:    as1.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include <BaseApplication.h>
#include <EntityMgr.h>

//---------------------------------------------------------------------------

class as2: public BaseApplication {
	constexpr static float surfaceHeight = -3.5;

	// Variables used to control various speeds
	constexpr static float cameraStep = 25; // Speed of camera movement
	constexpr static float velocityStep = 5; // Velocity increases per button press

	// Variables tracking the current key state
	static bool upDownLastFrame, downDownLastFrame, leftDownLastFrame, rightDownLastFrame, pgUpDownLastFrame, pgDownDownLastFrame;
	static bool spaceDownLastFrame, qDownLastFrame;
	static bool tabDownLastFrame;

public:
	as2(void);
	virtual ~as2(void);

protected:
	virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
