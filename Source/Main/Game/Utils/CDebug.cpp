//-----------------------------------------------------------------------------
#include "CDebug.h"
#include "CRender.h"
#include "Game/CGameGlobals.h"
#include <stdlib.h>
#include <vector>
#include <hgefont.h>
//-----------------------------------------------------------------------------
typedef struct TSegmentInfo {
	
	CSegment m_oSeg;
	float    m_fTime;
	float    m_fMaxTime;
		
}TSegmentInfo;

typedef struct TVectorInfo {
	
	CVector2 m_oVX;
	float    m_fTime;
	float    m_fMaxTime;

}TVectorInfo;

typedef struct TTextInfo {
	
	char	m_szStr[256];
	uint	m_uiX;
	uint	m_uiY;

	float    m_fTime;
	float    m_fMaxTime;

}TTextInfo;

std::vector <TSegmentInfo> m_oSegInfo;
std::vector <TVectorInfo>  m_oVecInfo;
std::vector <TTextInfo>    m_oTextInfo;

hgeFont*					m_oFnt;
//-----------------------------------------------------------------------------

HGE*	CDebug::m_pHGE = NULL;

//-----------------------------------------------------------------------------
void CDebug::Init(HGE *_pHGE)
{
	m_pHGE = _pHGE;
	
	// Load a font
	m_oFnt = new hgeFont("font1.fnt");
}
//-----------------------------------------------------------------------------
void CDebug::AddInfo(const CSegment& _oSeg,float _fTime)
{
	TSegmentInfo oS;

	oS.m_oSeg		= _oSeg;
	oS.m_fTime		= _fTime;
	oS.m_fMaxTime	= _fTime;

	m_oSegInfo.push_back(oS);	
}
//-----------------------------------------------------------------------------
void CDebug::AddInfo(const CVector2& _oVector,float _fTime)
{
	TVectorInfo oV;

	oV.m_oVX		= _oVector;
	oV.m_fTime		= _fTime;
	oV.m_fMaxTime	= _fTime;

	m_oVecInfo.push_back(oV);	
}
//------------------------------------------------------------------------
void CDebug::AddInfo(char* _szStr,uint _uiX,uint _uiY,float _fTime )
{
	TTextInfo oT;

	strcpy(oT.m_szStr,_szStr);
	oT.m_uiX		= _uiX;
	oT.m_uiY		= _uiY;
	oT.m_fTime		= _fTime;
	oT.m_fMaxTime	= _fTime;

	m_oTextInfo.push_back(oT);
}
//-----------------------------------------------------------------------------
/// Should be called once per frame, before calling any AddInfo function
//-----------------------------------------------------------------------------
void CDebug::NewFrame()
{
	// m_oSegInfo.clear();
	// m_oVecInfo.clear();
}
//-----------------------------------------------------------------------------
void CDebug::Update(float _fDeltaT)
{
	#ifdef _DEBUG

	// Update the segment list
	std::vector <TSegmentInfo>::iterator poSeg;

	for ( poSeg = m_oSegInfo.begin() ; poSeg != m_oSegInfo.end( ) ; )
	{
		(*poSeg).m_fTime -= _fDeltaT;
		
		if ((*poSeg).m_fTime <= 0.0f)
		{
			// delete the element
			poSeg = m_oSegInfo.erase( poSeg );
		}
		else
		{
			poSeg ++;
		}
	}

	// Update the vector list
	std::vector <TVectorInfo>::iterator poVec;

	for ( poVec = m_oVecInfo.begin() ; poVec != m_oVecInfo.end( ) ; )
	{
		(*poVec).m_fTime -= _fDeltaT;
		
		if ((*poVec).m_fTime <= 0.0f)
		{
			// delete the element
			poVec = m_oVecInfo.erase( poVec );
		}
		else
		{
			poVec++;
		}
	}
	
	// Update the text list
	std::vector <TTextInfo>::iterator poText;

	for ( poText= m_oTextInfo.begin() ; poText != m_oTextInfo.end( ) ; )
	{
		(*poText).m_fTime -= _fDeltaT;
		
		if ((*poText).m_fTime <= 0.0f)
		{
			// delete the element
			poText = m_oTextInfo.erase( poText );
		}
		else
		{
			poText ++;
		}
	}
	#endif
}
//-----------------------------------------------------------------------------
/// Renders all the retained debug info in the current frame
//-----------------------------------------------------------------------------
void CDebug::Render()
{
	#ifdef _DEBUG

	uint i,j,k;
	CVector2 oVXs[4];

	// Coger las 4 esquinas del coche, y testearlas contra el mapa de colisiones
	CRender::GetBoundingBox(oVXs,globals.m_oPCar.m_poSprite,globals.m_oPCar.m_oPos.x,globals.m_oPCar.m_oPos.y,globals.m_oPCar.m_fAngle,globals.m_oPCar.m_fScale);

	uint colors[4] = {
		
		0xffff0000,
		0xff00ff00,
		0xff0000ff,
		0xffffff00,
	};

	for (k=0;k<4;k++)
	{
		float x = oVXs[k].x;
		float y = oVXs[k].y;

		CRender::RenderQuad((float)x-4,(float)y-4,(float)x+4,(float)y+4,NULL,0,colors[k]);	
	}
		
	// overlay surface map
	// CRender::RenderQuad(0,0,640,480*HEIGHT_CORRECTION,m_poSurfaceMap,BLEND_ALPHABLEND);
		
	// Render map segments 
	for (i=0;i<globals.m_oMap.m_oSegLst.size();i++)
	{
		CSegment oS = globals.m_oMap.m_oSegLst[i];
		m_pHGE->Gfx_RenderLine(oS.m_oA.x,oS.m_oA.y,oS.m_oB.x,oS.m_oB.y,0xffffff00);
		
		CVector2 oP = 0.5f * (oS.m_oA + oS.m_oB);
		CVector2 oP2 = oP + (oS.m_oNormal * 16.0f);

		m_pHGE->Gfx_RenderLine(oP.x,oP.y,oP2.x,oP2.y,0xffff0000);
	}
	
	// Render debug info
	for (i=0;i<m_oVecInfo.size();i++)
	{
		float x = m_oVecInfo[i].m_oVX.x;
		float y = m_oVecInfo[i].m_oVX.y;

		float fAlpha = m_oVecInfo[i].m_fTime / m_oVecInfo[i].m_fMaxTime;
		uint uiAlpha = ((uint)(fAlpha * 255.0f)) << 24;

		uint uiColor = 0x00ff8080 | uiAlpha;

		CRender::RenderQuad((float)x-4,(float)y-4,(float)x+4,(float)y+4,NULL,0,uiColor);	
	}

	for (i=0;i<m_oSegInfo.size();i++)
	{
		CSegment oS = m_oSegInfo[i].m_oSeg;
		float fAlpha = m_oSegInfo[i].m_fTime / m_oSegInfo[i].m_fMaxTime;
		uint uiAlpha = ((uint)(fAlpha * 255.0f)) << 24;

		uint uiColor = 0x00ff0000 | uiAlpha;

		m_pHGE->Gfx_RenderLine(oS.m_oA.x  ,oS.m_oA.y  ,oS.m_oB.x  ,oS.m_oB.y  ,uiColor);
		m_pHGE->Gfx_RenderLine(oS.m_oA.x+1,oS.m_oA.y  ,oS.m_oB.x+1,oS.m_oB.y  ,uiColor);
		m_pHGE->Gfx_RenderLine(oS.m_oA.x  ,oS.m_oA.y+1,oS.m_oB.x  ,oS.m_oB.y+1,uiColor);
	}

	for (i=0;i<m_oTextInfo.size();i++)
	{
		char* szStr = m_oTextInfo[i].m_szStr;
		uint uiX = m_oTextInfo[i].m_uiX;
		uint uiY = m_oTextInfo[i].m_uiY;
		
		float fAlpha = m_oTextInfo[i].m_fTime / m_oSegInfo[i].m_fMaxTime;
		uint uiAlpha = ((uint)(fAlpha * 255.0f)) << 24;

		uint uiColor = 0x00ff0000 | uiAlpha;

		m_oFnt->SetColor(uiColor);
		m_oFnt->printf(uiX, uiY, HGETEXT_LEFT,szStr);
	}

	
	
	#endif // ifdef _DEBUG
}
//-----------------------------------------------------------------------------
