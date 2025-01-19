//-----------------------------------------------------------------------------
#include "CPlayerCar.h"
#include <stdlib.h>
#include <stdio.h>

//-----------------------------------------------------------------------------
CPlayerCar::CPlayerCar()
{
}
//-----------------------------------------------------------------------------
CPlayerCar::~CPlayerCar()
{

}
//-----------------------------------------------------------------------------
void CPlayerCar::Update(float _fDeltaT)
{	
	// Process keys
	m_bLeft  = m_pHGE->Input_GetKeyState(HGEK_LEFT);
	m_bRight = m_pHGE->Input_GetKeyState(HGEK_RIGHT);
	m_bAccel = m_pHGE->Input_GetKeyState(HGEK_UP);
	m_bBrake = m_pHGE->Input_GetKeyState(HGEK_DOWN);
	
	CCar::Update(_fDeltaT);
}
//-----------------------------------------------------------------------------