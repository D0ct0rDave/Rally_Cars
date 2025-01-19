//-----------------------------------------------------------------------------
/*! \class CGame
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CGameH
#define CGameH

#include <hge.h>
//-----------------------------------------------------------------------------
class CGame
{
	public:
	
		/// This functions load the map and intializes this class members
		static void Init(HGE *_pHGE);

		/// This functions load the map and intializes this class members
		static void Finish();
				
		/// Think function in case it's needed
		static void Update(float _fDeltaT);
		
		/// Render function for the map
		static void Render();
	
	protected:		
		static HGE*		m_pHGE;
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
