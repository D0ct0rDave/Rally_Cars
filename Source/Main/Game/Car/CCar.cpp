//-----------------------------------------------------------------------------
#include "CCar.h"
#include "Game/Utils/CCollisionMgr.h"
#include "Game/Utils/CRender.h"
#include "Game/Utils/CDebug.h"

#include <stdlib.h>
#include <stdio.h>
//-----------------------------------------------------------------------------
const float CAR_SCALE = 0.2;

const float SHADOW_OFS_X = -5.0f; // 1.6f;
const float SHADOW_OFS_Y = -5.0f; // 1.2f;

//-----------------------------------------------------------------------------
CCar::CCar()
{
	m_oPos.x = 0.0f;
	m_oPos.y = 0.0f;
	m_oPivot.x = 0.0f;
	m_oPivot.y = 0.0f;
	
	m_bBrake = false;
	m_bAccel = false;
	m_bLeft  = false;
	m_bRight = false;
	
	m_uiNumLaps = 0;
}
//-----------------------------------------------------------------------------
CCar::~CCar()
{

}
//-----------------------------------------------------------------------------
/// Computes the reflection vector from an incident vector and a normal
CVector2 CCar_oComputeReflectedDir(const CVector2& _oDir,const CVector2& _oNormal)
{
	// Ecuación de la reflexión de la luz incidente sobre una superficie. ("l" sale  en la dirección de la normal)
	// r = 2*(n.l)*n - l			<---- l es la dirección de un rayo de luz con el mismo sentido de la normal.
	// r = 2*(n.(-1*d))*n - (-1*d)	<---- d siempre va en sentido opuesto a n (venimos de una colision)
	// r = -2*(n.d)*n + d
	// r = d - 2*(n.d)*n
	CVector2 oR = _oDir - (2.0f*_oNormal.Dot( &_oDir ))*_oNormal;
	oR.Normalize();
 
	return ( oR );
}
//-----------------------------------------------------------------------------
float fLerp(float _fA,float _fB,float _fFact)
{
	// return ( _fA * _fFact + _fB(1.0f - _fFact) );
	return ( (_fB - _fA)*_fFact + _fA );
}
//-----------------------------------------------------------------------------
void CCar_CollisionCallback(CCar* _poCar,CSegment* _poSegment,uint _uiIdx,float _fFrameFactor)
{
	//
	switch (_poSegment->m_uiFlags)
	{
		// Normal segment (delimiter)
		case 0:
		{
			CSegment oMovement(_poCar->m_oOldPos,_poCar->m_oPos);

			// Non ridgid impact: Collisions loses energy
			_poCar->m_oBounceDir   = CCar_oComputeReflectedDir(oMovement.m_oDir,_poSegment->m_oNormal);
			_poCar->m_fBounceSpeed = _poCar->m_fOldSpeed * _poCar->m_fRestitutionFact;
			_poCar->m_fSpeed       = 0.0f;

			// Compute correct angle
			_poCar->m_fAngle = fLerp(_poCar->m_fOldAngle,_poCar->m_fAngle,_fFrameFactor);

			// Compute correct position
			_poCar->m_oPos.x = fLerp(_poCar->m_oOldPos.x,_poCar->m_oPos.x,_fFrameFactor);
			_poCar->m_oPos.y = fLerp(_poCar->m_oOldPos.y,_poCar->m_oPos.y,_fFrameFactor);
			
			CDebug::AddInfo(*_poSegment,2.0f);
		}
		break;
		
		case 1:
		{
			if (_uiIdx != 0)
				return;
		
			// goal
			CSegment oMovement(_poCar->m_oOldPos,_poCar->m_oPos);

			// Non ridgid impact: Collisions loses energy
			float fD = oMovement.m_oDir.Dot(&_poSegment->m_oNormal);
			
			if (fD >0.0f)
			{
				// vuelta ++;
				_poCar->m_uiNumLaps++;	
			}
			else
			{
				_poCar->m_uiNumLaps--;
			}
			
			
			char szStr[256];
			sprintf(szStr,"Vuelta %d",_poCar->m_uiNumLaps);
			CDebug::AddInfo(szStr,4,344,10.0f);
		}
		break;

		/*
		case 1:
		break;
		*/
	}
}
//-----------------------------------------------------------------------------
bool CCar::bInit(HGE *_pHGE,char* _szFilename)
{
	char szFilename[1024];

	// Take a copy of the engine object
	m_pHGE = _pHGE;

	// --------------------------------
	// Cars properties: Should come from an ini file
	// --------------------------------
	m_fScale = CAR_SCALE;

	m_oPivot.x = 50;
	m_oPivot.y = 100;

	m_fAccel = 1.0f;
	m_fBrake = -5.0f;
	m_fDecel = -1.0f;

	m_fMaxSpeed = 10.0f;

	m_fRestitutionFact = 0.5f;

	m_fSpinF = 1.15f;

	m_fSpeed = 0.0f;
	
	m_oPos.x = 360;
	m_oPos.y = 180;
	
	m_fAngle = 0.0f;

	// Collision response
	m_oBounceDir.x = 0.0f;
	m_oBounceDir.y = 0.0f;
	
	m_fBounceSpeed = 0.0f;

	// Load the surface texture
	sprintf(szFilename,"%s/car.tga",_szFilename);		
	m_poTexture	= m_pHGE->Texture_Load(szFilename);	

	sprintf(szFilename,"%s/shadow.tga",_szFilename);		
	m_poSTexture	= m_pHGE->Texture_Load(szFilename);	

	// Create the sprite
	uint uiWidth  = m_pHGE->Texture_GetWidth(m_poTexture,true);
	uint uiHeight = m_pHGE->Texture_GetHeight(m_poTexture,true);

	m_poSprite = new hgeSprite(m_poTexture, 0, 0, uiWidth, uiHeight);
	m_poSprite->SetColor(0xffffffff);
	m_poSprite->SetHotSpot(m_oPivot.x,m_oPivot.y);
	m_poSprite->SetBlendMode(BLEND_ALPHABLEND);

	// Create and set up a particle system
	m_poPST = m_pHGE->Texture_Load("data/fx/smoke.tga");	
	
	m_poPSS =new hgeSprite(m_poPST, 0, 0, 64, 64);
	m_poPSS->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	m_poPSS->SetHotSpot(32,32);

	m_poPSys =new hgeParticleSystem("data/fx/particle9.psi",m_poPSS);
	// m_poPSys =new hgeParticleSystem(&PSI);
	m_poPSys->Fire();
	// m_poPSys->info.fSizeStart *= 0.5f;
	// m_poPSys->info.fSizeEnd   *= 0.5f;

	m_fEmissorOfs = uiWidth * CAR_SCALE * 0.8f;

	// Add car to the collision manager
	CCollisionMgr::AddCar(this,CCar_CollisionCallback);
	
	return(true);
}
//-----------------------------------------------------------------------------
// Descomponemos el movimiento del coche en 2 fuerzas
// la del propio coche (motor / frenos)
// la de una colision previa
// la suma de las 2 fuerzas determinan el movimiento del coche en el actual frame
//-----------------------------------------------------------------------------
void CCar::Update(float _fDeltaT)
{
	// Store old values
	m_oOldPos   = m_oPos;
	m_fOldSpeed = m_fSpeed;
	m_fOldAngle = m_fAngle;
	
	// Control movement
	float fAccel = 0.0f;
	if (( m_bBrake) && (! m_bAccel)) fAccel += m_fBrake;
	if ((!m_bBrake) && (  m_bAccel)) fAccel += m_fAccel;

	float fSpeed  = m_fSpeed;
	
	// When no brake and no accel is used
	if ((! m_bBrake) && (! m_bAccel))
	{
		const float fFrictionThreshold = 0.01f;
		
		// Positive speed 
		if (fSpeed > 0.0f)
		{
			if (fSpeed > fFrictionThreshold)
				fAccel += m_fDecel;
			else
				fSpeed = 0.0f;
		}

		// Negative speed ( backwards )
	else if (fSpeed < 0.0f)
		{
			if (fSpeed < -fFrictionThreshold)
				fAccel -= m_fDecel;
			else
				fSpeed = 0.0f;
		}
	}

	fSpeed = fSpeed + fAccel * _fDeltaT;
	if (fSpeed > m_fMaxSpeed) fSpeed = m_fMaxSpeed;
	if (fSpeed < (-m_fMaxSpeed*0.1f)) fSpeed = -m_fMaxSpeed*0.1f;
	
	// Collision speed
	if (m_fBounceSpeed >= 0.0f)
	{
		m_fBounceSpeed += m_fDecel*_fDeltaT;
		if (m_fBounceSpeed < 0.0f) m_fBounceSpeed = 0.0f;
	}

	// Control direction
	float fAngle = m_fAngle;
	
	if (m_bLeft)
	{
			/*
		if (fSpeed > 0.0f)
			fAngle -= m_fSpinF*_fDeltaT;
   else if (fSpeed < 0.0f)
			*/
			fAngle -= m_fSpinF*_fDeltaT;
	}

	if (m_bRight)
	{
		/*
		if (fSpeed < 0.0f)
			fAngle -= m_fSpinF*_fDeltaT;
   else if (fSpeed > 0.0f)
		*/
			fAngle += m_fSpinF*_fDeltaT;
	}
	
	// Check new step direction
	CVector2 oDir;
	oDir.x = -1.0f;
	oDir.y = 0.0f;
	
	oDir.Rotate(fAngle);

	// New position
	CVector2 oPos = m_oPos + oDir*fSpeed + m_oBounceDir*m_fBounceSpeed;
	

	// Update particle system
	CVector2 oPSPos;
	oPSPos = m_oPos - (oDir * m_fEmissorOfs);

	m_poPSys->info.nEmission = (int)10*fabs(m_fSpeed);
	m_poPSys->MoveTo(oPSPos.x,oPSPos.y);
	m_poPSys->Update(_fDeltaT);


	// Set candidate to final values
	m_fSpeed = fSpeed;
	m_fAngle = fAngle;
	m_oPos   = oPos;


#ifdef _DEBUG

	// Debug info
	CSegment oS;
	oS.m_oA.x = 100;
	oS.m_oA.y = 100;
	
	oS.m_oB = oS.m_oA + (oDir * m_fSpeed * 5.0f);
	CDebug::AddInfo(oS,1.0f);

#endif

}
//-----------------------------------------------------------------------------
void CCar::Render()
{
	// Render car shadow texture
	m_poSprite->SetTexture(m_poSTexture);
	m_poSprite->SetZ(0.25f);
	m_poSprite->SetColor(0x80ffffff);

	CRender::RenderSprite(m_poSprite,m_oPos.x+SHADOW_OFS_X,m_oPos.y+SHADOW_OFS_Y,m_fAngle,m_fScale);

	// Render particle systems
	m_poPSys->Render();

	// Render Car
	m_poSprite->SetTexture(m_poTexture);
	m_poSprite->SetZ(0.5f);
	m_poSprite->SetColor(0xffffffff);

	CRender::RenderSprite(m_poSprite,m_oPos.x,m_oPos.y,m_fAngle,m_fScale);
}
//-----------------------------------------------------------------------------