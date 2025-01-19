
/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut03 - Using helper classes
*/

//-----------------------------------------------------------------------------
// Copy the files "particles.png", "menu.wav",
// "font1.fnt", "font1.png" and "trail.psi" from
// the folder "precompiled" to the folder with
// executable file. Also copy hge.dll and bass.dll
// to the same folder.


#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgeparticle.h"

#include "game/cgame.h" 
//-----------------------------------------------------------------------------

// Pointer to the HGE interface.
// Helper classes require this to work.
HGE *hge=0;


// Pointers to the HGE objects we will use
hgeSprite*			spr;
hgeSprite*			spt;
hgeFont*			fnt;
hgeParticleSystem*	par;

// Handles for HGE resourcces
HTEXTURE			tex;
HEFFECT				snd;

// Some "gameplay" variables
float x=100.0f, y=100.0f;
float dx=0.0f, dy=0.0f;

const float speed=90;
const float friction=0.98f;


//-----------------------------------------------------------------------------
// Play sound effect
void boom()
{
	int pan=int((x-400)/4);
	float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
	hge->Effect_PlayEx(snd,100,pan,pitch);
}
//-----------------------------------------------------------------------------
bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();

	// Process keys
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	
	//
	CGame::Update(dt);

	return false;
}
//-----------------------------------------------------------------------------
bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
		
		CGame::Render();
		
		par->Render();
		spr->Render(x, y);
		fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", hge->Timer_GetDelta(), hge->Timer_GetFPS());
		
	hge->Gfx_EndScene();

	return false;
}
//-----------------------------------------------------------------------------
bool MAIN_bInit()
{
	// Load sound and texture
	snd=hge->Effect_Load("menu.wav");
	tex=hge->Texture_Load("particles.png");
	if(!snd || !tex)
	{
		// If one of the data files is not found, display
		// an error message and shutdown.
		// MessageBox(NULL, "Can't load one of the following files:\nMENU.WAV, PARTICLES.PNG, FONT1.FNT, FONT1.PNG, TRAIL.PSI", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		hge->System_Shutdown();
		hge->Release();
		return 0;
	}

	// Create and set up a sprite
	spr=new hgeSprite(tex, 96, 64, 32, 32);
	spr->SetColor(0xFFFFA000);
	spr->SetHotSpot(16,16);

	// Load a font
	fnt=new hgeFont("font1.fnt");

	// Create and set up a particle system
	spt=new hgeSprite(tex, 32, 32, 32, 32);
	spt->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	spt->SetHotSpot(16,16);
	par=new hgeParticleSystem("trail.psi",spt);
	par->Fire();
	
	CGame::Init(hge);
	
	return(true);
}
//-----------------------------------------------------------------------------
void MAIN_Finish()
{
	CGame::Finish();
	
	// Delete created objects and free loaded resources
		delete par;
		delete fnt;
		delete spt;
		delete spr;
		hge->Texture_Free(tex);
		hge->Effect_Free(snd);
}
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	char szDir[1024];
	GetCurrentDirectory(1024,szDir);
	
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "rally.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Rally Cars");
	hge->System_SetState(HGE_FPS, 30);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 640);
	hge->System_SetState(HGE_SCREENHEIGHT, 480);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate())
	{
		MAIN_bInit();

			// Let's rock now!
			hge->System_Start();

		MAIN_Finish();
	}

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
//-----------------------------------------------------------------------------
