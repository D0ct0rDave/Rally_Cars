//-----------------------------------------------------------------------------
#include "CGame.h"
#include <stdlib.h>
#include <stdio.h>

#include "game/map/cmap.h"
#include "game/car/ccar.h"
#include "game/car/CPlayerCar.h"
#include "game/Utils/CCollisionMgr.h"
#include "game/Utils/CRender.h"
#include "game/CGameGlobals.h"
#include "game/Utils/CDebug.h"

//-----------------------------------------------------------------------------

HGE*	CGame::m_pHGE = NULL;

//-----------------------------------------------------------------------------
void CGame::Init(HGE *_pHGE)
{
	m_pHGE = _pHGE;
	
	//
	CDebug::Init(_pHGE);

	// 
	CRender::Init(_pHGE);
	
	//
	globals.m_oMap.bInit(m_pHGE,"data/maps/map0");
	globals.m_oPCar.bInit(m_pHGE,"data/cars/mate");

	//
	CCollisionMgr::Init(&globals.m_oMap);
}
//-----------------------------------------------------------------------------
void CGame::Finish()
{
}
//-----------------------------------------------------------------------------
void CGame::Update(float _fDeltaT)
{
	CDebug::NewFrame();
	CDebug::Update(_fDeltaT);

	globals.m_oPCar.Update(_fDeltaT);
		
	// Update the collision system
	CCollisionMgr::Update(_fDeltaT);
}
//-----------------------------------------------------------------------------
void CGame::Render()
{
	globals.m_oMap.Render();	
	globals.m_oPCar.Render();
	
	CDebug::Render();
}
//-----------------------------------------------------------------------------