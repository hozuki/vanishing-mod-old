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

// Achievement settings guide:
//
// Step 1: Prepare Achievements List
// Step 2: Code Your Achievements
//       - Suppose that the achievement name is MOD_ACHIEVEMENT.
//       - * achievementName in macro DECLARE_ACHIEVEMENT => "MOD_ACHIEVEMENT"
//       - * achievement name provided for Hammer (in .fgd) => ACHIEVEMENT_EVENT_MOD_ACHIEVEMENT (see logic_achievement.cpp)
//       - * global achievement name => MOD_ACHIEVEMENT
//       - * achievement icon file name => MOD_ACHIEVEMENT.vmt
//       - Code the class, derived from CBaseAchievement.
//       - The achievement class should contains flags either ACH_SAVE_WITH_GAME or ACH_SAVE_GLOBAL. Lacking this leads to an assertion failure.
//       - If you want to award the achievement without Steamworks (needs Internet connection and Steamworks authorization), override the achievements class' AlwaysEnabled() method. (See CAchievementMgr::AwardAchievement())
// Step 3: Set Up the Icon
//       - 1. Prepare a SQUARE image.
//       - 2. Use VTFEdit to convert it into .vtf format, using default parameters.
//       - 3. Generate .vmt file using the parameter: Shader = Decal, Additive = true, Translucent = false.
//       - 4. Save .vtf and .vmt to {path_to_your_mod}/materials/vgui/achievements/MOD_ACHIEVEMENT[.vmt/.vtf].
// Step 4: Activate the Achievement
//       - Open hammer and insert a logic_achievement point entity naming "achiever", with AchievementName property set to "ACHIEVEMENT_EVENT_MOD_ACHIEVEMENT" (or equivalent selection value, based on custom FGD).
//       - Add an output, setting its target to achiever's FireEvent() input.
// Step 5: Run the Map and Enjoy

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
