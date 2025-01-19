//-----------------------------------------------------------------------------
/*! \class CGameGlobals
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CGameGlobalsH
#define CGameGlobalsH
//-----------------------------------------------------------------------------

#include <hge.h>

#include "game/map/cmap.h"
#include "game/car/ccar.h"
#include "game/car/CPlayerCar.h"

//-----------------------------------------------------------------------------

class CGameGlobals
{
	public:

		CMap		m_oMap;
		CCar		m_oCar;
		CPlayerCar  m_oPCar;
};

extern CGameGlobals globals;
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
