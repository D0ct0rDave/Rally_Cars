//-----------------------------------------------------------------------------
/*! \class CMap
 *  \brief 
 *  \author David M&aacute;rquez de la Cruz
 *  \version 1.5
 *  \date 1999-2009
 *  \par Copyright (c) 1999 David M&aacute;rquez de la Cruz
 *  \par License Rally
 */
//-----------------------------------------------------------------------------
#ifndef CMapH
#define CMapH
//-----------------------------------------------------------------------------
#include <hge.h>
#include <vector>
//-----------------------------------------------------------------------------
typedef HTEXTURE  CTexture;

//-----------------------------------------------------------------------------
class CMap
{
	public:
	
		CMap();
		~CMap();

		/// This functions load the map and intializes this class members
		bool bInit(HGE *_pHGE,char* _szFilename);
		
		/// Think function in case it's needed
		void Update(float _fDeltaT);
		
		/// Render function for the map
		void Render();

		/// The surface properties of the circuit
		HTEXTURE m_poSurfaceMap;

		/// The image data that contains the surface properties
		uint* m_puiSurface;
		
		/// Surface dimensions	
		uint  m_uiTX;
		uint  m_uiTY;
		
		/// Factors to convert between world coordinates and surface coordinates
		float m_fXFact;
		float m_fYFact;
	
		/// X Sectors
		uint m_uiXSectors;
		
		/// Y Sectors
		uint m_uiYSectors;
		
		/// The sectors that form the complete map
		HTEXTURE* m_poSectors;
		
		/// The whole map as a unique big texture
		HTEXTURE m_poGlobalMap;
		
		HGE*		m_pHGE;
	
	//
	protected:

		void ComputeCollisionSegments();
	
	public:
		std::vector<CSegment> m_oSegLst;

};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
