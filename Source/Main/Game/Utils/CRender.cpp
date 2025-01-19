//-----------------------------------------------------------------------------
#include "CRender.h"
#include <stdlib.h>
#include <stdio.h>
//-----------------------------------------------------------------------------

/*
	Las coordenadas que mandan son las de pantalla!
	1 pixel de pantalla se corresponde con 1 pixel de mundo

*/

//-----------------------------------------------------------------------------

HGE*	CRender::m_pHGE = NULL;
float   CRender::m_fXFact = 1.0f;
float   CRender::m_fYFact = 1.0f;
//-----------------------------------------------------------------------------
void CRender::Init(HGE *_pHGE)
{
	m_pHGE = _pHGE;

	m_fXFact = (float)m_pHGE->System_GetState(HGE_SCREENWIDTH ) / (float)STD_SCR_WIDTH;
	m_fYFact = (float)m_pHGE->System_GetState(HGE_SCREENHEIGHT) / (float)STD_SCR_HEIGHT;
}
//-----------------------------------------------------------------------------
void CRender::RenderSprite(hgeSprite* _poSprite,float _fX,float _fY,float _fAngle,float _fScale)
{
	float fX = _fX * m_fXFact;
	float fY = _fY * m_fYFact;

	_poSprite->RenderEx(fX,fY,_fAngle,_fScale*m_fXFact,_fScale*m_fYFact);
}
//-----------------------------------------------------------------------------
void CRender::RenderQuad(float _fIX,float _fIY,float _fFX,float _fFY,HTEXTURE _hTex,uint _uiBlend,uint _uiColor)
{
	hgeQuad quad;

	quad.blend   = _uiBlend;
	quad.tex     = _hTex;

	quad.v[0].col= _uiColor;
	quad.v[0].tx = 0;																																																							
	quad.v[0].ty = 0;
	quad.v[0].x  = _fIX*m_fXFact;
	quad.v[0].y  = _fIY*m_fYFact;
	quad.v[0].z  = 0;

	quad.v[1].col= _uiColor;
	quad.v[1].tx = 1;
	quad.v[1].ty = 0;
	quad.v[1].x  = _fFX*m_fXFact;
	quad.v[1].y  = _fIY*m_fYFact;
	quad.v[1].z  = 0;

	quad.v[2].col= _uiColor;
	quad.v[2].tx = 1;
	quad.v[2].ty = 1;
	quad.v[2].x  = _fFX*m_fXFact;
	quad.v[2].y  = _fFY*m_fYFact;
	quad.v[2].z  = 0;

	quad.v[3].col= _uiColor;
	quad.v[3].tx = 0;
	quad.v[3].ty = 1;
	quad.v[3].x  = _fIX*m_fXFact;
	quad.v[3].y  = _fFY*m_fYFact;
	quad.v[3].z  = 0;

	m_pHGE->Gfx_RenderQuad(&quad);
}
//-----------------------------------------------------------------------------
void CRender::GetBoundingBox(CVector2* _poVX,hgeSprite* _poSprite,float _fX,float _fY,float _fAngle,float _fScale)
{
	float fX = _fX * m_fXFact;
	float fY = _fY * m_fYFact;

	// _poSprite->GetBoundingBoxEx(fX,fY,0.0f,_fScale*m_fXFact,_fScale*m_fYFact,_pRect);

	float fSW = _poSprite->GetWidth()  * 0.5f;
	float fSH = _poSprite->GetHeight() * 0.5f;

	float fHSX,fHSY;
	_poSprite->GetHotSpot(&fHSX,&fHSY);

	fHSX = (fSW - fHSX)*0.5f;
	fHSY = (fSH - fHSY)*0.5f;

	_poVX[0].x = (-fSW+fHSX) *_fScale;
	_poVX[0].y = (-fSH+fHSY) *_fScale;

	_poVX[1].x = ( fSW+fHSX) *_fScale;
	_poVX[1].y = (-fSH+fHSY) *_fScale;
	
	_poVX[2].x = ( fSW+fHSX) *_fScale;
	_poVX[2].y = ( fSH+fHSY) *_fScale;

	_poVX[3].x = (-fSW+fHSX) *_fScale;
	_poVX[3].y = ( fSH+fHSY) *_fScale;

	for (uint i=0;i<4;i++)
	{
		_poVX[i].Rotate(_fAngle);

		_poVX[i].x += (_fX);
		_poVX[i].y += (_fY);
	}
}
//-----------------------------------------------------------------------------
