//-----------------------------------------------------------------------------
#include "CCollisionMgr.h"
#include "CRender.h"
#include "CDebug.h"

#include <stdlib.h>
#include <stdio.h>
//-----------------------------------------------------------------------------
std::vector<TCarPlayer>		CCollisionMgr::m_oCars;
			
CMap*						CCollisionMgr::m_poMap		= NULL;
uint*						CCollisionMgr::m_puiSurface = NULL;		
uint						CCollisionMgr::m_uiTX		= 0;
uint						CCollisionMgr::m_uiTY		= 0;
float						CCollisionMgr::m_fXFact		= 1.0f;
float						CCollisionMgr::m_fYFact		= 1.0f;
//-----------------------------------------------------------------------------		
void CCollisionMgr::Init(CMap* _poMap)
{
	m_poMap = _poMap;

	// Retrieve surface texture
	m_puiSurface= _poMap->m_puiSurface;
	m_uiTX		= _poMap->m_uiTX;
	m_uiTY		= _poMap->m_uiTY;

	m_fXFact	= _poMap->m_fXFact; 
	m_fYFact	= _poMap->m_fXFact;
}
//-----------------------------------------------------------------------------
void CCollisionMgr::AddCar(CCar* _poCar,TCollisionCallback _pCallback)
{
	TCarPlayer oCarPlayer;

	oCarPlayer.m_pCallback = _pCallback;
	oCarPlayer.m_poCar     = _poCar;

	m_oCars.push_back( oCarPlayer );
}
//-----------------------------------------------------------------------------
std::pair<bool,float> SegmentIntersectionTest(const CSegment& _roSeg,const CSegment& _roPnt)
{
	std::pair<bool,float> oRes;

	/*
	E = B-A = ( Bx-Ax, By-Ay )
	F = D-C = ( Dx-Cx, Dy-Cy ) 
	P = ( -Ey, Ex )
	h = ( (A-C) * P ) / ( F * P )
	*/
	/*
	CVector2 E,F,P;
	float h;

	E =	_roSeg.m_oBA;
	F = _roPnt.m_oBA;

	P.x = -E.y;	// la normal !?!?
	P.y = E.x;

	float fFP = F.Dot(&P);

	if (fFP != 0.0f)
	{
		CVector2 AC = _roSeg.m_oA - _roPnt.m_oA;
		h = AC.Dot(&P) / fFP;
		
		oRes.first  = ((h>=0.0f) && (h<=1.0f));
		oRes.second = h;
		if (oRes.first == true)
		{
			int a = 0;
		}
		return oRes;
	}
	*/
	/*
	float fLambdaDen = ((_roSeg.m_oDir.y / _roPnt.m_oDir.y) - (_roSeg.m_oDir.x / _roPnt.m_oDir.x));
	float fLambdaNum = ((_roSeg.m_oA.y / _roPnt.m_oA.y) - (_roSeg.m_oA.x / _roPnt.m_oA.x)); 
	float fLambda    = fLambdaNum / fLambdaDen;

	float fMu = ((_roSeg.m_oA.x - _roPnt.m_oA.x) - (fLambda*_roSeg.m_oDir.x)) / _roPnt.m_oDir.x; 

	oRes.first  = ((fLambda>=0.0f) && (fLambda<=1.0f)) && ((fMu>=0.0f) && (fMu<=1.0f));
	oRes.second = fMu;
	*/

	CVector2 oSAPA = _roPnt.m_oA - _roSeg.m_oA;
	CVector2 oSAPB = _roPnt.m_oB - _roSeg.m_oA;

	float fDotPA = oSAPA.Dot(&_roSeg.m_oNormal);
	float fDotPB = oSAPB.Dot(&_roSeg.m_oNormal);



	CVector2 oPASA = _roSeg.m_oA - _roPnt.m_oA;
	CVector2 oPASB = _roSeg.m_oB - _roPnt.m_oA;

	float fDotSA = oPASA.Dot(&_roPnt.m_oNormal);
	float fDotSB = oPASB.Dot(&_roPnt.m_oNormal);


	// Both dot products should have different sign then the multiply should give a negative number
	oRes.first  = ((fDotPA*fDotPB) < 0.0f) && ((fDotSA*fDotSB)<0.0f); 
	oRes.second = 0.0f;

	return (oRes);
}
//-----------------------------------------------------------------------------
// OUT: <index into the segment vector,fraction of DeltaT>
//-----------------------------------------------------------------------------
std::pair<int,float> CCollisionMgr::CheckPointCollision(const CVector2& _oOldPos,const CVector2& _oNewPos)
{
	std::pair<int,float> oRes(-1,0.0f);

	// check whether one of collision points of the car collides agains the map	
	for (uint s=0;s<m_poMap->m_oSegLst.size();s++)
	{	
		CSegment oS = m_poMap->m_oSegLst[s];
		CSegment oC(_oOldPos,_oNewPos);

		std::pair<bool,float> oR = SegmentIntersectionTest(oS,oC);

		if (oR.first == true)
		{
			// Set the segment index
			oRes.first  = s;
			
			// Set the fraction of DeltaT
			oRes.second = oR.second;

			return(oRes);
		}
	}

	return(oRes);
}
//-----------------------------------------------------------------------------
/// Checks the collisions of a given car player against the complete system
//-----------------------------------------------------------------------------
//      0-----1
//      |     |
//      3-----2
//-----------------------------------------------------------------------------
void CCollisionMgr::CheckCarCollision(const TCarPlayer& _oCarPlayer)
{
	CVector2 oOldVXs[4];
	CVector2 oNewVXs[4];

	// Coger las 4 esquinas del coche, y testearlas contra el mapa de colisiones
	CRender::GetBoundingBox(oOldVXs,_oCarPlayer.m_poCar->m_poSprite,
							_oCarPlayer.m_poCar->m_oOldPos.x,_oCarPlayer.m_poCar->m_oOldPos.y,
							_oCarPlayer.m_poCar->m_fOldAngle,_oCarPlayer.m_poCar->m_fScale);

	// Coger las 4 esquinas del coche, y testearlas contra el mapa de colisiones
	CRender::GetBoundingBox(oNewVXs,_oCarPlayer.m_poCar->m_poSprite,
							_oCarPlayer.m_poCar->m_oPos.x   ,_oCarPlayer.m_poCar->m_oPos.y   ,
							_oCarPlayer.m_poCar->m_fAngle   ,_oCarPlayer.m_poCar->m_fScale);

	// Check if any of the 4 point displacements collides or not
	for (uint p=0;p<4;p++)
	{
		std::pair<int,float> oRes;
		oRes = CheckPointCollision(oOldVXs[p],oNewVXs[p]);

		if (oRes.first >= 0)
			_oCarPlayer.m_pCallback(_oCarPlayer.m_poCar, &m_poMap->m_oSegLst[oRes.first], p, oRes.second);
	}
}
//-----------------------------------------------------------------------------
/// Performs a physic step over all the collidable elements managed
void CCollisionMgr::Update(float _fDeltaT)
{
	for (uint c=0;c<m_oCars.size();c++)
		CheckCarCollision( m_oCars[c] );	
}
//-----------------------------------------------------------------------------
