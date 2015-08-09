//========= Copyright Vanishing Team, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "basecombatweapon.h"
#include "explode.h"
#include "eventqueue.h"
#include "gamerules.h"
#include "ammodef.h"
#include "in_buttons.h"
#include "soundent.h"
#include "ndebugoverlay.h"
#include "vstdlib/random.h"
#include "engine/IEngineSound.h"
#include "game.h"

#include "player.h"
#include "entitylist.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Spawnflags
#define SF_MESSAGE_DISABLED		1

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CTargetIndicatorEntity : public CPointEntity
{
	DECLARE_CLASS(CTargetIndicatorEntity, CPointEntity);

public:
	void	Spawn(void);
	void	Activate(void);
	void	Think(void);
	void	DrawOverlays(void);

	virtual void UpdateOnRemove();

	void	InputEnable(inputdata_t &inputdata);
	void	InputDisable(inputdata_t &inputdata);
	void    SetMessage(inputdata_t &inputdata);

	DECLARE_DATADESC();

protected:
	string_t		m_messageText;
	bool			m_bEnabled;

private:
	Vector          relativePositionVector;
};

LINK_ENTITY_TO_CLASS(env_targetindicator, CTargetIndicatorEntity);

BEGIN_DATADESC(CTargetIndicatorEntity)

DEFINE_KEYFIELD(m_messageText, FIELD_STRING, "message"),
DEFINE_FIELD(m_bEnabled, FIELD_BOOLEAN),

// Inputs
DEFINE_INPUTFUNC(FIELD_VOID, "Enable", InputEnable),
DEFINE_INPUTFUNC(FIELD_VOID, "Disable", InputDisable),
DEFINE_INPUTFUNC(FIELD_STRING, "SetMessage", SetMessage),

END_DATADESC()

static CUtlVector< CHandle< CTargetIndicatorEntity > >	g_TargetIndicatorEntities;

//-----------------------------------------
// Spawn
//-----------------------------------------
void CTargetIndicatorEntity::Spawn(void)
{
	SetNextThink(gpGlobals->curtime + 0.1f);
	//m_bEnabled = !HasSpawnFlags(SF_MESSAGE_DISABLED);
	m_bEnabled = true;
	relativePositionVector = Vector(0, 0, 0);
	//m_debugOverlays |= OVERLAY_TEXT_BIT;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTargetIndicatorEntity::Activate(void)
{
	BaseClass::Activate();

	CHandle< CTargetIndicatorEntity > h;
	h = this;
	g_TargetIndicatorEntities.AddToTail(h);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTargetIndicatorEntity::UpdateOnRemove()
{
	BaseClass::UpdateOnRemove();

	CHandle< CTargetIndicatorEntity > h;
	h = this;
	g_TargetIndicatorEntities.FindAndRemove(h);

	BaseClass::UpdateOnRemove();
}

//-----------------------------------------
// Think
//-----------------------------------------
void CTargetIndicatorEntity::Think(void)
{
	SetNextThink(gpGlobals->curtime + 0.1f);

	// check for player distance
	CBasePlayer *pPlayer = UTIL_GetLocalPlayer();

	if (!pPlayer || (pPlayer->GetFlags() & FL_NOTARGET))
		return;

	Vector worldTargetPosition = pPlayer->GetAbsOrigin();

	// calculate relative position
	relativePositionVector = worldTargetPosition - GetAbsOrigin();
}

//-------------------------------------------
// Purpose: KEY of this entity. Draws custom message, and distance between Player and this entity.
//-------------------------------------------
void CTargetIndicatorEntity::DrawOverlays(void)
{
	if (!m_bEnabled)
		return;

	// display text if they are within range
	char tempstr[512];
	Q_snprintf(tempstr, sizeof(tempstr), "%s", STRING(m_messageText));
	EntityText(0, tempstr, 0);
	Q_snprintf(tempstr, sizeof(tempstr), "%.0f m", relativePositionVector.Length() / 64);
	EntityText(1, tempstr, 0);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTargetIndicatorEntity::SetMessage(inputdata_t &inputdata)
{
	// FIXME: possible memory leak
	m_messageText = MAKE_STRING(inputdata.value.String());
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTargetIndicatorEntity::InputEnable(inputdata_t &inputdata)
{
	m_bEnabled = true;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTargetIndicatorEntity::InputDisable(inputdata_t &inputdata)
{
	m_bEnabled = false;
}

// This is a hack to make point_message stuff appear in developer 0 release builds
//  for now
void DrawTargetIndicatorEntities()
{
	int c = g_TargetIndicatorEntities.Count();
	for (int i = c - 1; i >= 0; i--)
	{
		CTargetIndicatorEntity *me = g_TargetIndicatorEntities[i];
		if (!me)
		{
			g_TargetIndicatorEntities.Remove(i);
			continue;
		}

		me->DrawOverlays();
	}
}
