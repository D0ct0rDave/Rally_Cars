//-----------------------------------------------------------------------------
/*! \class CCar
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CCarH
#define CCarH

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
//-----------------------------------------------------------------------------
typedef HTEXTURE  CTexture;
//-----------------------------------------------------------------------------
class CCar
{
	public:
	
		CCar();
		~CCar();

		/// This functions load the car data and intializes this class members
		bool bInit(HGE *_pHGE,char* _szFilename);

		/// Think function in case it's needed
		virtual void Update(float _fDeltaT);

		/// Render function for the car
		void Render();

		/// The GE interface
		HGE*		m_pHGE;
		
		/// The sprite information for this car
		HTEXTURE	m_poTexture;
		HTEXTURE	m_poSTexture;
		hgeSprite*	m_poSprite;
		

		// --------------------------------
		/// Static properties: Cars physic properties
		// --------------------------------
		
		/// Car pivot: rotation point of the car
		CVector2	m_oPivot;				
		
		///
		float		m_fAccel;
		float		m_fBrake;
		float		m_fDecel;
		
		float		m_fMaxSpeed;
		float		m_fRestitutionFact;
		
		float		m_fSpinF;
	
		/// Current car scale
		float		m_fScale;
	
		// --------------------------------
		/// Runtime properties: Current properties 
		// --------------------------------

		/// car orientation
		float		m_fAngle;

		/// World coordinates
		CVector2	m_oPos;

		/// Current Speed Magnitude
		float		m_fSpeed;

		/// External force product of previous collision response
		CVector2	m_oBounceDir;

		/// Current collision response magnitude
		float		m_fBounceSpeed;

		// --------------------------------
		/// Runtime properties: Old (previous frame) properties
		// --------------------------------

		/// Car orientation
		float		m_fOldAngle;

		/// World coordinates
		CVector2	m_oOldPos;

		/// Current Speed Magnitude
		float		m_fOldSpeed;

		// --------------------------------
		/// Current active controls
		// --------------------------------
		bool m_bBrake;
		bool m_bAccel;
		bool m_bLeft;
		bool m_bRight;
		
		// --------------------------------
		// Game properties
		// --------------------------------
		uint m_uiNumLaps;

		// --------------------------------
		// Particle system
		// --------------------------------
		HTEXTURE			m_poPST;
		hgeSprite*			m_poPSS;
		hgeParticleSystem*	m_poPSys;
		
		float				m_fEmissorOfs;
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
