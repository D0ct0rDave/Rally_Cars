//-----------------------------------------------------------------------------
#ifndef BasicTypesH
#define BasicTypesH
//-----------------------------------------------------------------------------

#include <hgeVector.h>

typedef unsigned int uint;
typedef hgeVector CVector2;

class CSegment
{	
	public:

		/// Simple constructor with no initialization
		CSegment() {};

		/// Construction with full initialization		
		CSegment(const CVector2& _oA,const CVector2& _oB)
		{
			Init(_oA,_oB);
		}

		/// Full class initialiation
		void Init(const CVector2& _oA,const CVector2& _oB)
		{
			m_oA = _oA;
			m_oB = _oB;
			
			// Compute segment direction
			m_oBA  = m_oB - m_oA;
			
			// Segment length
			m_fLen = m_oBA.Length();

			// Normalized direction
			if (m_fLen > 0.0f) m_oDir = m_oBA * (1.0f / m_fLen);

			// Compute segment normal
			m_oNormal.y = m_oDir .x;
			m_oNormal.x = -1.0f * m_oDir .y;
		}
		
		/// Partial initialization of the class
		void PartialInit(const CVector2& _oA,const CVector2& _oB)
		{
			m_oA = _oA;
			m_oB = _oB;
		}

	public:
	
		CVector2 m_oA;
		CVector2 m_oB;
		CVector2 m_oBA;
		float    m_fLen;
		CVector2 m_oDir;
		CVector2 m_oNormal;

		uint	 m_uiFlags;

};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
