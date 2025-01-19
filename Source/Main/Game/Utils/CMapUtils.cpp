//-----------------------------------------------------------------------------
#include "CMapUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <hge.h>
//-----------------------------------------------------------------------------
float CMapUtils::m_fXScale = 1.0f;
float CMapUtils::m_fYScale = 1.0f;
//-----------------------------------------------------------------------------

uint START_POINT_COLOR   = 0;
uint CONTROL_POINT_COLOR = 0;
uint CHANGE_DIR_COLOR    = 0;
uint COLORA = 0;
uint COLORB = 0;

uint uiTX;
uint uiTY;
uint* puiSurface;

//-----------------------------------------------------------------------------
std::vector<CSegment>* CMapUtils::poGetSegmentListFromBitmapControlPoints(HGE* _pHGE,HTEXTURE _poSurfaceMap,uint _uiStartPointColor,uint _uiControlPointColor,uint _uiChangeDirColor,bool _bChangeWinding)
{
	START_POINT_COLOR   = _uiStartPointColor;
	CONTROL_POINT_COLOR = _uiControlPointColor;
	CHANGE_DIR_COLOR    = _uiChangeDirColor;

	puiSurface	= (uint*)_pHGE->Texture_Lock(_poSurfaceMap);
	uiTX       	= _pHGE->Texture_GetWidth (_poSurfaceMap);
	uiTY       	= _pHGE->Texture_GetHeight(_poSurfaceMap);

	std::vector<CSegment>* poSegLst = NULL;

	// look for the starting point
	for (uint j=0;j<uiTY;j++)
		for (uint i=0;i<uiTX;i++)
		{
			uint uiColor = puiSurface[j*uiTX+i] & 0x00ffffff;

			if (uiColor == START_POINT_COLOR)
			{
				std::vector<CSegment>* poCurSegLst = poGetSegmentListFromBitmapControlPoints(i,j,_bChangeWinding);

				if (poSegLst == NULL)
					poSegLst = poCurSegLst;
				else
				{
					// add the segment list to the current one
					poSegLst->insert(poSegLst->end(),poCurSegLst->begin(),poCurSegLst->end());
					delete poCurSegLst;
				}
			}
		}

	_pHGE->Texture_Unlock(_poSurfaceMap);
	return(poSegLst);
}
//-----------------------------------------------------------------------------
std::vector<CSegment>* CMapUtils::poGetSegmentListFromBitmapControlPoints(uint _uiX,uint _uiY,bool _bChangeWinding)
{
	std::vector<CSegment>* poSegLst = new std::vector<CSegment>;

	bool bFound;
	CVector2  oSP(_uiX,_uiY);	// Starting point	
	CVector2  oCP = oSP;		// Current point

	// Start search
	CVector2 oA,oB;
	uint uiDir  = 0;
	uint uiSegs = 0;
	
	int i,j;

	do
	{
		bFound = false;

		oA.x = oCP.x * m_fXScale;
		oA.y = oCP.y * m_fYScale;
		
		int iXMin = oCP.x-16;
		int iXMax = oCP.x+16;
		int iYMin = oCP.y-16;
		int iYMax = oCP.y+16;

		if (iXMin<0) iXMin = 0; else if (iXMax >= uiTX) iXMax = uiTX-1;
		if (iYMin<0) iYMin = 0; else if (iYMax >= uiTY) iYMax = uiTY-1;

		switch (uiDir)
		{
			// Horizontal search, vertical retrace
			case 0:
			{
				for (i=oCP.x+1;((i<uiTX) && (! bFound));i++)
					for (j=iYMin;((j<iYMax) && (! bFound));j++)
					{
						uint uiColor = puiSurface[j*uiTX+i] & 0x00ffffff;

						if (
								(uiColor == CONTROL_POINT_COLOR)
							||	(uiColor == CHANGE_DIR_COLOR)
							||	((i==_uiX) &&  (j==_uiY))
							// (uiColor == START_POINT_COLOR)
							)
						{
							bFound = true;
							if (uiColor == CHANGE_DIR_COLOR) uiDir = 1;
							
							// setup control point
							oCP.x = i;
							oCP.y = j;
							break;
						}
					}
			}
			break;
			
			// Vertical search, horizontal reverse retrace
			case 1:
			{
				for (j=oCP.y+1;((j<uiTY) && (! bFound));j++)
					for (i=iXMax;((i>=iXMin) && (! bFound));i--)
					{
						uint uiColor = puiSurface[j*uiTX+i] & 0x00ffffff;

						if (
								(uiColor == CONTROL_POINT_COLOR)
							||	(uiColor == CHANGE_DIR_COLOR)
							||	((i==_uiX) &&  (j==_uiY))
							// ||	(uiColor == START_POINT_COLOR)
							)
						{
							bFound = true;
							if (uiColor == CHANGE_DIR_COLOR) uiDir = 2;
							
							// setup control point
							oCP.x = i;
							oCP.y = j;
							break;
						}
					}
			}
			break;


			// Horizontal reverse search, vertical reverse retrace
			case 2:
			{
				for (i=oCP.x-1;((i>=0) && (! bFound));i--)
					for (j=iYMax;((j>=iYMin) && (! bFound));j--)
					{
						uint uiColor = puiSurface[j*uiTX+i] & 0x00ffffff;

						if (
								(uiColor == CONTROL_POINT_COLOR)
							||	(uiColor == CHANGE_DIR_COLOR)
							||	((i==_uiX) &&  (j==_uiY))
							// ||	(uiColor == START_POINT_COLOR)
							)
						{
							bFound = true;
							if (uiColor == CHANGE_DIR_COLOR) uiDir = 3;

							// setup control point
							oCP.x = i;
							oCP.y = j;
							break;
						}
					}
			}
			break;
			
			// Vertical reverse search, horizontal retrace
			case 3:
			{
				for (j=oCP.y-1;((j>=0) && (! bFound));j--)
					for (i=iXMin;((i<iXMax) && (! bFound));i++)
					{
						uint uiColor = puiSurface[j*uiTX+i] & 0x00ffffff;

						if (
								(uiColor == CONTROL_POINT_COLOR)
							||	(uiColor == CHANGE_DIR_COLOR)
							||	((i==_uiX) &&  (j==_uiY))
							// ||	(uiColor == START_POINT_COLOR)
							)
						{
							bFound = true;
							if (uiColor == CHANGE_DIR_COLOR) uiDir = 0;

							// setup control point
							oCP.x = i;
							oCP.y = j;
							break;
						}
					}
			}
			break;
		}


		// Control point not found? return
		if (! bFound) return(poSegLst);
		
		// Complete segment
		oB.x = oCP.x * m_fXScale;
		oB.y = oCP.y * m_fYScale;

		// Create the segment
		CSegment oS;
		if (_bChangeWinding)
			oS.Init(oB,oA);
		else
			oS.Init(oA,oB);

		// Insert segment into the list
		poSegLst->push_back(oS);
		uiSegs ++;

	} while (! ((oCP.x == oSP.x) && (oCP.y == oSP.y)) ) ; 

	return(poSegLst);
}
//-----------------------------------------------------------------------------
std::vector<CSegment>* CMapUtils::poGetSegmentListFromBitmapSegments(HGE* _pHGE,HTEXTURE _poSurfaceMap,uint _uiStartColor,uint _uiColorA,uint _uiColorB,bool _bChangeWinding)
{
	START_POINT_COLOR   = _uiStartColor;
	COLORA				= _uiColorA;
	COLORB				= _uiColorB;

	puiSurface	= (uint*)_pHGE->Texture_Lock(_poSurfaceMap);
	uiTX       	= _pHGE->Texture_GetWidth (_poSurfaceMap);
	uiTY       	= _pHGE->Texture_GetHeight(_poSurfaceMap);

	std::vector<CSegment>* poSegLst = NULL;

	// look for the starting point
	for (uint j=0;j<uiTY;j++)
		for (uint i=0;i<uiTX;i++)
		{
			uint uiColor = puiSurface[j*uiTX+i] & 0x00ffffff;

			if (uiColor == START_POINT_COLOR)
			{
				std::vector<CSegment>* poCurSegLst = poGetSegmentListFromBitmapSegments(i,j,_bChangeWinding);

				if (poSegLst == NULL)
					poSegLst = poCurSegLst;
				else
				{
					// add the segment list to the current one
					poSegLst->insert(poSegLst->end(),poCurSegLst->begin(),poCurSegLst->end());
					delete poCurSegLst;
				}
			}
		}

	_pHGE->Texture_Unlock(_poSurfaceMap);
	return(poSegLst);
}
//-----------------------------------------------------------------------------
// xxx 123
// x·x 4·5
// xxx 678
//-----------------------------------------------------------------------------
std::vector<CSegment>* CMapUtils::poGetSegmentListFromBitmapSegments(uint _uiX,uint _uiY,bool _bChangeWinding)
{
	typedef struct TScanCoords
	{
		int x;
		int y;
	}TScanCoords;
	
	TScanCoords oScanCoords[8] = {
				{-1,-1},{0,-1},{1,-1},
				{-1, 0}       ,{1, 0},
				{-1, 1},{0, 1},{1, 1}};

	std::vector<CSegment>* poSegLst = new std::vector<CSegment>;

	int i = _uiX+1;
	int j = _uiY;
	uint uiLastColor = puiSurface[ j*uiTX + i] & 0x00ffffff;

	CVector2  oSP((float)_uiX* m_fXScale,(float)_uiY* m_fYScale);	// Starting point
	CVector2  oA = oSP;
	CVector2  oB;

	while (! ((i == _uiX) && (j == _uiY)) )
	{
		// Clear this point
		puiSurface[ j*uiTX + i] = 0xff808080; 

		bool bNextIter = false;

		for (uint c=0;((c<8) && (bNextIter == false));c++)
		{
			int iNewI = i + oScanCoords[c].x;
			int iNewJ = j + oScanCoords[c].y;

			uint uiColor = puiSurface[ iNewJ*uiTX + iNewI ] & 0x00ffffff;

			if (uiColor == START_POINT_COLOR)
			{
				continue;
			}

			if (uiColor == uiLastColor) 
			{
				// update i,j
				i = iNewI;
				j = iNewJ;
				
				// perform next iteration
				bNextIter = true;
				break;
			}

	   else if (   ((uiColor == COLORA) && (uiLastColor == COLORB))
				|| ((uiColor == COLORB) && (uiLastColor == COLORA))
				)
			{
				oB.x = (i+oScanCoords[c].x)* m_fXScale;
				oB.y = (j+oScanCoords[c].y)* m_fYScale;

				// Create the segment
				CSegment oS;
				if (_bChangeWinding)
					oS.Init(oB,oA);
				else
					oS.Init(oA,oB);

				// Insert segment into the list
				poSegLst->push_back(oS);
				oA = oB;

				// Set new lastcolor
				uiLastColor = uiColor;

				// update i,j
				i = iNewI;
				j = iNewJ;

				// perform next iteration
				bNextIter = true;
			}
		}	// end for
		
		//
		if (bNextIter == false)
		{
			// Unfinished segment ??
			if ((oB.x != oSP.x) || (oB.y != oSP.y))
			{ 	
				CSegment oS;
				
				if (_bChangeWinding)
					oS.Init(oSP,oB);
				else
					oS.Init(oB,oSP);
			
				// Insert segment into the list
				poSegLst->push_back(oS);
			}

			return (poSegLst);
		}
	} 

	// Create the last segment in case
	if ((oB.x != oSP.x) || (oB.y != oSP.y))
	{ 	
		CSegment oS;
		
		if (_bChangeWinding)
			oS.Init(oB,oA);
		else
			oS.Init(oA,oB);
	}

	return (poSegLst);
}
//-----------------------------------------------------------------------------
std::pair<int,int> CMapUtils::GetPoint(uint _uiX,uint _uiY)
{
	std::pair<int,int> oRes(-1,-1);

	// look for the starting point
	for (uint j=_uiY;j<uiTY;j++)
		for (uint i=_uiX;i<uiTX;i++)
		{
			if ((puiSurface[j*uiTX+i] & 0x00ffffff) == START_POINT_COLOR)
			{
				oRes.first  = i;
				oRes.second = j;				

				return(oRes);
			}
		}

	return(oRes);
}
//-----------------------------------------------------------------------------
std::pair<bool,CVector2> CMapUtils::GetPoint(HGE* _pHGE,HTEXTURE _poSurfaceMap,uint _uiColor)
{
	START_POINT_COLOR	= _uiColor;
	puiSurface			= (uint*)_pHGE->Texture_Lock(_poSurfaceMap);
	uiTX       			= _pHGE->Texture_GetWidth (_poSurfaceMap);
	uiTY       			= _pHGE->Texture_GetHeight(_poSurfaceMap);

	std::pair<int,int> oR = GetPoint();

	std::pair<bool,CVector2> oRes;

	oRes.first    = (oR.first >= 0);
	oRes.second.x = (float)oR.first  * m_fXScale;
	oRes.second.y = (float)oR.second * m_fYScale;

	_pHGE->Texture_Unlock(_poSurfaceMap);
	return(oRes);
}
//-----------------------------------------------------------------------------
