//-----------------------------------------------------------------------------
/*! \class CCurve
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CCurveH
#define CCurveH
//-----------------------------------------------------------------------------
#include <math.h>
//-----------------------------------------------------------------------------
class CCurve
{
	public: 
		///
		CCurve() : m_fMin(0.0f), m_fMax(0.0f) {};

		/// 
		CCurve(float _fMin,float _fMax)
		{
			Init(_fMin,_fMax);
		}
		
		///
		virtual void Init(float _fMin,float _fMax)
		{
			m_fMin = _fMin;
			m_fMax = _fMax;
			
		}

		virtual float fValue(float _fFact) = 0;

	protected:
		float m_fMin;
		float m_fMax;
};

class CCurveLerp : public CCurve
{
	public:

		virtual float fValue(float _fFact)
		{
				if (_fFact<=m_fMin) return(m_fMin); 
		   else if (_fFact>=m_fMax) return(m_fMax); 
		   else	
			    return( (_fFact - m_fMin) / (m_fMax - m_fMin) );
		}
};

class CCurveSinLerp: public CCurve
{
	public:

		virtual float fValue(float _fFact)
		{
				if (_fFact<=m_fMin) return(m_fMin); 
		   else if (_fFact>=m_fMax) return(m_fMax); 
		   else	
		   {
				const float _PI2_ = 1.5707963267948966192313216916395f;

				float fFact = (_fFact - m_fMin) / (m_fMax - m_fMin);
			    return( (m_fMax-m_fMin)*sinf(_PI2_*fFact) + m_fMin );
		   }
		}
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
