//-----------------------------------------------------------------------------
/*! \class CDebug
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CDebugH
#define CDebugH
//-----------------------------------------------------------------------------
#include <hge.h>
//-----------------------------------------------------------------------------
class CDebug
{
	public:

		/// This function load the map and intializes this class members
		static void Init(HGE *_pHGE);

		/// Should be called once per frame, before calling any AddInfo function
		static void NewFrame();

		/// Updates the debug info state
		static void Update(float _fDeltaT);

		/// Renders all the retained debug info in the current frame
		static void Render();

		/// Adds debug information to display
		static void AddInfo(const CSegment& _oSeg,float _fTime = 0.0f);
		static void AddInfo(const CVector2& _oVector,float _fTime = 0.0f);
		static void AddInfo(char* _szStr,uint _uiX,uint _uiY,float _fTime = 0.0f);

	protected:

		static HGE*		m_pHGE;
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
