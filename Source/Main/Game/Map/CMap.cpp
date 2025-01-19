//-----------------------------------------------------------------------------
#include "CMap.h"
#include <stdlib.h>
#include <stdio.h>
#include "Game/Utils/CRender.h"
#include "Game/Utils/CMapUtils.h"

//-----------------------------------------------------------------------------

const float SECTOR_WIDTH  = 512;
const float SECTOR_HEIGHT = 512;

//-----------------------------------------------------------------------------
CMap::CMap() : m_poSurfaceMap(NULL), m_uiXSectors(),m_uiYSectors(0), m_poSectors(NULL)
{

}
//-----------------------------------------------------------------------------
CMap::~CMap()
{

}
//-----------------------------------------------------------------------------
bool CMap::bInit(HGE *_pHGE,char* _szFilename)
{
	char szFilename[1024];

	// Take a copy of the engine object
	m_pHGE = _pHGE;


	/*
	// hardcoded at this moment
	m_uiXSectors = 6;
	m_uiYSectors = 6;

	// Load any of the texture sectors of the map
	m_poSectors = new HTEXTURE[m_uiXSectors*m_uiYSectors];
	
	for(uint j=0;j<m_uiYSectors;j++)
		for(uint i=0;i<m_uiXSectors;i++)
		{
			sprintf(szFilename,"%s/sector_%d_%d.tga",_szFilename,j,i);
			
			// Load texture
			m_poSectors[j*m_uiXSectors+i] = m_pHGE->Texture_Load(szFilename);	
		}
	*/

	// Load global map texture
	sprintf(szFilename,"%s/circuit.tga",_szFilename);		
	m_poGlobalMap= m_pHGE->Texture_Load(szFilename);	

	// Load the surface texture and setup its properties
	sprintf(szFilename,"%s/surface.tga",_szFilename);		
	m_poSurfaceMap	= m_pHGE->Texture_Load(szFilename);	

	m_puiSurface = (uint*)m_pHGE->Texture_Lock(m_poSurfaceMap);
	m_uiTX = m_pHGE->Texture_GetWidth (m_poSurfaceMap);
	m_uiTY = m_pHGE->Texture_GetHeight(m_poSurfaceMap);

	// m_fXFact = (float)m_pHGE->Texture_GetWidth (m_poGlobalMap,true) / (float)m_pHGE->Texture_GetWidth (m_poSurfaceMap,true); 
	// m_fYFact = (float)m_pHGE->Texture_GetHeight(m_poGlobalMap,true) / (float)m_pHGE->Texture_GetHeight(m_poSurfaceMap,true);

	m_fXFact = (float)STD_SCR_WIDTH  / (float)m_pHGE->Texture_GetWidth (m_poSurfaceMap,true); 
	m_fYFact = (float)STD_SCR_HEIGHT / (float)m_pHGE->Texture_GetHeight(m_poSurfaceMap,true);

	m_pHGE->Texture_Unlock(m_poSurfaceMap);

	CMapUtils::SetScales(m_fXFact,m_fYFact);

	// Get external segments
	std::vector<CSegment>* poSegLst = CMapUtils::poGetSegmentListFromBitmapSegments(m_pHGE,m_poSurfaceMap,0x00ffff00,0x00ff0000,0x0000ff00,false);
	m_oSegLst = *poSegLst;
	delete poSegLst;

	// Get internal segments
	poSegLst = CMapUtils::poGetSegmentListFromBitmapSegments(m_pHGE,m_poSurfaceMap,0x000000ff,0x00ff0000,0x0000ff00,true);
	m_oSegLst.insert(m_oSegLst.end(),poSegLst->begin(),poSegLst->end());
	delete poSegLst;
	
	// Setup flags
	for (uint s=0;s<m_oSegLst.size();s++)
		m_oSegLst[s].m_uiFlags = 0;


	// Get starting point
	std::pair<bool,CVector2> oA = CMapUtils::GetPoint(m_pHGE,m_poSurfaceMap,0x0000ffff);
	std::pair<bool,CVector2> oB = CMapUtils::GetPoint(m_pHGE,m_poSurfaceMap,0x00ff00ff);

	CSegment oS(oA.second,oB.second);
	oS.m_uiFlags  = 0x00000001;
	m_oSegLst.insert(m_oSegLst.end(),oS);

	return(false);
}
//-----------------------------------------------------------------------------
void CMap::Update(float _fDeltaT)
{
}
//-----------------------------------------------------------------------------
void CMap::Render()
{
	// Render global map
	CRender::RenderQuad(0,0,640,480*HEIGHT_CORRECTION,m_poGlobalMap,BLEND_ALPHABLEND);
}
//-----------------------------------------------------------------------------