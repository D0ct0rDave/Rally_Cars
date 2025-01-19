//-----------------------------------------------------------------------------
/*! \class CCollisionMgr
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CCollisionMgrH
#define CCollisionMgrH
//-----------------------------------------------------------------------------
#include <hge.h>
#include <vector>
#include "Game/Car/CCar.h"
#include "Game/Map/CMap.h"
//-----------------------------------------------------------------------------

typedef void (*TCollisionCallback)(CCar* _poCar,CSegment* _poSegment,uint _uiIdx,float _fDeltaT);

//-----------------------------------------------------------------------------
// Car player structure

typedef struct TCarPlayer{
	
	CCar*				m_poCar;
	TCollisionCallback	m_pCallback;

}TCarPlayer;

//-----------------------------------------------------------------------------
class CCollisionMgr
{
	public:

		/// Intialization function for collision manager
		static void Init(CMap* _poMap);
	
		/// Adds a new car to the collision manager system
		static void AddCar(CCar* _poCar,TCollisionCallback _pCallback);

		/// Performs a physic step over all the collidable elements managed
		static void Update(float _fDeltaT);

	protected:

		/// Checks the collisions of one of the points of the car against the complete system
		static std::pair<int,float> CheckPointCollision(const CVector2& _oPos,const CVector2& _oStep);
		
		/// Checks the collisions of a given car player against the complete system
		static void CheckCarCollision(const TCarPlayer& _oCarPlayer);

		///
		static std::vector<TCarPlayer>	m_oCars;
		static CMap*					m_poMap;

		static uint*					m_puiSurface;
		static uint						m_uiTX;
		static uint						m_uiTY;
		static float					m_fXFact;
		static float					m_fYFact;
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
