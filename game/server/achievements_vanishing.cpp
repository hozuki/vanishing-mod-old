//========= Copyright Vanishing Team, All rights reserved. ============//
//
// Purpose: Declaring Vanishing achievements
//
//=============================================================================


#include "cbase.h"
#include "achievementmgr.h"
#include "baseachievement.h"

#ifdef GAME_DLL

#define ACHIEVEMENT_VANISHING_PRESSED_TEST_BUTTON (201)

class CAchievementVanishingPressedTestButton : public CBaseAchievement
{

protected:

	void Init()
	{
		SetFlags(ACH_LISTEN_MAP_EVENTS | ACH_SAVE_GLOBAL);
		//SetGameDirFilter("Vanishing");
		SetGoal(1);
	}

	virtual bool AlwaysEnabled()
	{
		return true;
	}

};

DECLARE_ACHIEVEMENT(CAchievementVanishingPressedTestButton, ACHIEVEMENT_VANISHING_PRESSED_TEST_BUTTON, "VANISHING_PRESSED_TEST_BUTTON", 5);

#endif
