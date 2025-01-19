//-----------------------------------------------------------------------------
/*! \class CRender
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CRenderH
#define CRenderH
//-----------------------------------------------------------------------------
#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
//-----------------------------------------------------------------------------
const uint STD_SCR_WIDTH  = 640;
const uint STD_SCR_HEIGHT = 480;
//-----------------------------------------------------------------------------
class CRender
{
	public:
	
		/// This function load the map and intializes this class members
		static void Init(HGE *_pHGE);
		
		/// Renders a sprite
		static void RenderSprite(hgeSprite* _poSprite,float _fX,float _fY,float _fAngle = 0.0f,float _fScale = 1.0f);
		
		/// Renders a quad
		static void RenderQuad(float _fIX,float _fIY,float _fFX,float _fFY,HTEXTURE _hTex,uint _uiBlend,uint _uiColor = 0xffffffff);
	
		/// Returns the sprite rect 
		static void GetBoundingBox(CVector2* _poVX,hgeSprite* _poSprite,float _fX,float _fY,float _fAngle = 0.0f,float _fScale = 1.0f);

	protected:		
		static HGE*		m_pHGE;
		static float    m_fXFact;
		static float    m_fYFact;
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
