//-----------------------------------------------------------------------------
/*! \class CPlayerCar
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CPlayerCarH
#define CPlayerCarH

#include <hge.h>
#include <hgesprite.h>
#include "CCar.h"

//-----------------------------------------------------------------------------
typedef HTEXTURE  CTexture;
//-----------------------------------------------------------------------------
class CPlayerCar : public CCar
{
	public:

		CPlayerCar();
		~CPlayerCar();

		/// Think function in case it's needed
		virtual void Update(float _fDeltaT);
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
