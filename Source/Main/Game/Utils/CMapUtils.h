//-----------------------------------------------------------------------------
/*! \class CMapUtils
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CMapUtilsH
#define CMapUtilsH
//-----------------------------------------------------------------------------
#include "Game/Map/CMap.h"
#include <hge.h>
#include <vector>

//-----------------------------------------------------------------------------
class CMapUtils
{
	public:
		static void SetScales(float _fXScale,float _fYScale)
		{
			m_fXScale = _fXScale;
			m_fYScale = _fYScale;
		}

		static std::vector<CSegment>* poGetSegmentListFromBitmapControlPoints(HGE* _pHGE,HTEXTURE _poSurfaceMap,uint _uiStartPointColor,uint _uiControlPointColor,uint _uiChangeDirColor,bool _bChangeWinding);
		static std::vector<CSegment>* poGetSegmentListFromBitmapSegments(HGE* _pHGE,HTEXTURE _poSurfaceMap,uint _uiStartColor,uint _uiColorA,uint _uiColorB,bool _bChangeWinding);
		
		// Retrieves the coordinates of the pixel equal to the given color
		static std::pair<bool,CVector2> GetPoint(HGE* _pHGE,HTEXTURE _poSurfaceMap,uint _uiColor);
	
	protected:
		/// Gets the list of segments starting from the initial coordinates
		static std::vector<CSegment>* poGetSegmentListFromBitmapControlPoints(uint _uiX,uint _uiY,bool _bChangeWinding);
		static std::vector<CSegment>* poGetSegmentListFromBitmapSegments(uint _uiX,uint _uiY,bool _bChangeWinding);
		static std::pair<int,int> GetPoint(uint _uiX = 0,uint _uiY = 0);

		static float m_fXScale;
		static float m_fYScale;
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
