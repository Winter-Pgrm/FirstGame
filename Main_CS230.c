// ---------------------------------------------------------------------------
// Project Name		:	Simple Demo
// File Name		:	Main.cpp
// Author			:	Antoine Abi Chacra
// Creation Date	:	2012/01/11
// Purpose			:	main entry point2 for the test program
// History			:
// - 2012/01/11		:	- initial implementation
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"

// ---------------------------------------------------------------------------

// Libraries
#pragma comment (lib, "Alpha_Engine.lib")

// ---------------------------------------------------------------------------
// globals

int gGameRunning = 1;
int inthesky = 0;
float maxhieght = 0.0f;
LRESULT CALLBACK MyWinCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp) ;


// ---------------------------------------------------------------------------
// Static function protoypes

// ---------------------------------------------------------------------------
// main


int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	// Variable declaration
	unsigned char colors[16];				// 2x2 image
	float obj1X = 0.0f, obj1Y = 0.0f;		// Position variables for object 1
	float obj2X = 0.0f, obj2Y = 0.0f;		// Position variables for object 2
	float obj1texX = 0, obj1texY = 0;		// Texture variables for object 1's texture
	int counter = 0;						// Counter to swap textures
	AEGfxVertexList*	pMesh1;				// Pointer to Mesh (Model)
	AEGfxVertexList*	pMesh2;				// Pointer to Mesh (Model)
	AEGfxVertexList*	pMeshLine;			// Pointer to Mesh (Model)
	AEGfxTexture *pTex1;					// Pointer to Texture (Image)
	AEGfxTexture *pTex2;					// Pointer to Texture (Image)
	char strBuffer[256];					// Character buffer used to print text
	float camX, camY;						// Used to temporary store camera position
	float camZoom;							// USed to temporary store the camera zoom value
	s32 sx, sy;
	float x, y;
	float alpha = 1.0f;



	// Initialize the system 
	AESysInitInfo sysInitInfo;
	sysInitInfo.mCreateWindow			= 1;
	sysInitInfo.mWindowHandle			= NULL;
	sysInitInfo.mAppInstance			= instanceH;
	sysInitInfo.mShow					= show;
	sysInitInfo.mWinWidth				= 1280; 
	sysInitInfo.mWinHeight				= 800;
	sysInitInfo.mCreateConsole			= 1;
	sysInitInfo.mMaxFrameRate			= 60;
	sysInitInfo.mpWinCallBack			= NULL;
	sysInitInfo.mClassStyle				= CS_HREDRAW | CS_VREDRAW;											
	sysInitInfo.mWindowStyle			= WS_OVERLAPPEDWINDOW;
	sysInitInfo.mHandleWindowMessages	= 1;



	if(0 == AESysInit (&sysInitInfo))
		printf("System Init Failed!\n");


	// Changing the window title
	AESysSetWindowTitle("testing!");

	// reset the system modules
	AESysReset();


	//if(AllocConsole())
	//{
	//	FILE* file;
	//
	//	freopen_s(&file, "CONOUT$", "wt", stdout);
	//	freopen_s(&file, "CONOUT$", "wt", stderr);
	//	freopen_s(&file, "CONOUT$", "wt", stdin);

	//	SetConsoleTitle("Alpha Engine - Console");
	//}

	////////////////////////////////
	// Creating the objects (Shapes)


	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// 1 triangle at a time
	// X, Y, Color, texU, texV
	AEGfxTriAdd(
		-25.5f, -25.5f, 0xFFFF0000, 0.0f, 0.0f, 
		25.5f,  0.0f, 0xFFFF0000, 0.0f, 0.0f,
		-25.5f,  25.5f, 0xFFFF0000, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1

	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles

	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f, 
		40.0f,  -30.0f, 0x00FFFF00, 1.0f, 1.0f,
		-30.0f,  30.0f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f, 
		40.0f,  30.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-30.0f,  30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");

		
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 5 vertices

	
	AEGfxVertexAdd(-2000.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(1000.0f, 000.0f, 0xFFFFFFFF, 0.0f, 30.0f);


	pMeshLine = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshLine, "Failed to create mesh 2!!");


	// Creating the objects (Shapes)
	////////////////////////////////

	////////////////////////////
	// Loading textures (images)

	// Texture 1: From file
	pTex1 = AEGfxTextureLoad("PlanetTexture.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");




	// Texture 2: From memory
	// RGBA format
	colors[0] = 255;	colors[1] = 0;		colors[2] = 0;		colors[3] = 255;
	colors[4] = 0;		colors[5] = 255;	colors[6] = 0;		colors[7] = 255;
	colors[8] = 0;		colors[9] = 0;		colors[10] = 255;	colors[11] = 255;	
	colors[12] = 255;	colors[13] = 255;	colors[14] = 255;	colors[15] = 255;				

	pTex2 = AEGfxTextureLoadFromMemory(colors, 2, 2);
	AE_ASSERT_MESG(pTex2, "Failed to create texture2!!");

	// Loading a textures (images)
	//////////////////////////////

	
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);


	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		///////////////////
		// Game loop update
		
		
		// Object Control
		if (obj1Y != 0.0f && inthesky == 1 || obj1Y == 30.0f && maxhieght == 30.0f)
		{

			obj1Y -= 1.0f;
			if (obj1Y == 0.0f && maxhieght == 30.0f)
			{
				inthesky = 0;
				maxhieght = 0;

			}
		}
		 if (AEInputCheckCurr(VK_UP) && maxhieght < 30.0f)
		{
			obj1Y += 2.0f;
			maxhieght += .5f;
			inthesky = 1;

		}
		else
			if (AEInputCheckCurr(VK_DOWN))
			{
				if (obj1Y != 0.0f)
					
				obj1Y -= 3.0f;
			}
		if (AEInputCheckCurr(VK_LEFT))
			obj1X -= 3.0f;
		else
		if (AEInputCheckCurr(VK_RIGHT))
			obj1X += 3.0f;
		

		
		//printf("X = %f, Y = %f\n", obj1X, obj1Y);


		// Texture offset
		if (AEInputCheckCurr('L'))
			obj1texX += 0.01f;
	

		if (AEInputCheckCurr('R'))
		{

			obj1X = 0.0f;
			obj1Y = 0.0f;
		}
		else
			if (AEInputCheckCurr('V'))
			{
				obj1Y = -3.0f;
			}
			


		// Move the camera
		AEGfxGetCamPosition(&camX, &camY);
		
			AEGfxSetCamPosition(obj1X, obj1Y );
		
			AEGfxSetCamPosition(obj1X, obj1Y );

	
			AEGfxSetCamPosition(obj1X, obj1Y);
	
			AEGfxSetCamPosition(obj1X , obj1Y);



		// Alpha value
		if (AEInputCheckCurr('Z'))
			alpha -= 0.01f;
		else
		if (AEInputCheckCurr('X'))
			alpha += 0.01f;

		alpha = AEClamp(alpha, 0.0f, 1.0f);


		// Blending mode
		if (AEInputCheckCurr('1'))
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		else
		if (AEInputCheckCurr('2'))
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		else
		if (AEInputCheckCurr('3'))
			AEGfxSetBlendMode(AE_GFX_BM_ADD);


		// Texture mode
		if (AEInputCheckCurr('9'))
			AEGfxSetTextureMode(AE_GFX_TM_PRECISE);
		else
		if (AEInputCheckCurr('0'))
			AEGfxSetTextureMode(AE_GFX_TM_AVERAGE);
		

		// Game loop update
		///////////////////


		//////////////////
		// Game loop draw

		//printf("MinX: %f | MaxX: %f | MinY: %f | MaxY: %f\n", AEGfxGetWinMinX(), AEGfxGetWinMaxX(), AEGfxGetWinMinY(), AEGfxGetWinMaxY());
		//printf("BLA BLA BLA BLA BLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		{
			//double ft = AEFrameRateControllerGetFrameTime();
			//if(ft > 0.0168)
				//printf("FrameTime %f\n", AEFrameRateControllerGetFrameTime());
		}
		AEInputGetCursorPosition(&sx, &sy);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(0, 0);
		if (AEInputCheckCurr('G'))
		{

			
			AEGfxLine(obj1X, obj1Y, 0, 0, 1, 1, 1, sx-630, -sy + 400 , 0, 0, 1, 0, 1);


			

		}

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(0.0f, 0.0f);
		AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);
		// Drawing object 1
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		//AEGfxSetWorldOriginMode(AE_WOM_TOP_LEFT);
		// Set poisition for object 1
		//AEGfxSetPosition(obj1X, obj1Y);
		AEGfxSetFullTransformWithZOrder(obj1X, obj1Y, 0.0f, 0.0f, 1.0f, 1.0f);
		// No texture for object 1
		AEGfxTextureSet(NULL, 0, 0);
		// Drawing the mesh (list of triangles)
		AEGfxSetTransparency(alpha);
		//AEGfxSetViewportPositionAndDimensions(100, 100, 400, 300);
		AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);


		


		AEGfxConvertScreenCoordinatesToWorld(sx, sy, &x, &y);
		obj2X = x;
		obj2Y = y;
	
		// Drawing object 2 - NO TINT
		// Set poisition for object 2
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		//AEGfxSetPosition(100.0f, -60.0f);
		AEGfxSetFullTransformWithZOrder(-360.0f, 360.0f, -10.0f, 0.0f, 1.0f, 1.0f);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Set texture for object 2
		++counter;
		if(counter < 120)
			AEGfxTextureSet(pTex1, obj1texX, obj1texY);		// Same object, different texture
		else
		if(counter < 240)
			AEGfxTextureSet(pTex2, obj1texX, obj1texY);		// Same object, different texture
		else
		{
			AEGfxTextureSet(pTex1, obj1texX, obj1texY);		// Same object, different texture
			counter = 0;
		}

		AEGfxSetTransparency(alpha);

		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);

		// Drawing object 2 - BLUE TINT
		// Set poisition for object 2
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(100.0f, 60.0f);
		AEGfxSetTintColor(0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxSetFullTransformWithZOrder(obj2X, obj2Y, 10.0f, 0.0f, 1.0f, 1.0f);
		// Set texture for object 2
		++counter;
		if(counter < 120)
			AEGfxTextureSet(pTex1, obj1texX, obj1texY);		// Same object, different texture
		else
		if(counter < 240)
			AEGfxTextureSet(pTex2, obj1texX, obj1texY);		// Same object, different texture
		else
		{
			AEGfxTextureSet(pTex1, obj1texX, obj1texY);		// Same object, different texture
			counter = 0;
		}

		AEGfxSetTransparency(alpha);

		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
		//


		// Game loop draw
		//////////////////

		// Informing the system about the loop's end
		AESysFrameEnd();

		AESysPrintf("%s\n", "Using AESysPrintf\n");

		// check if forcing the application to quit
		if (AEInputCheckTriggered(VK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// Freeing the objects and textures
	AEGfxMeshFree(pMesh1);
	AEGfxMeshFree(pMesh2);

	AEGfxTextureUnload(pTex1);
	AEGfxTextureUnload(pTex2);

	

	// free the system
	AESysExit();
}

// ---------------------------------------------------------------------------

LRESULT CALLBACK MyWinCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp) 
{
	HDC dc;   
	PAINTSTRUCT ps;

	switch (msg)
	{
	// when the window is created
	case WM_CREATE:
		printf("My own code in window create message!\n");
		break;

	// when the rectangle is drawn
	case WM_PAINT:
		dc = BeginPaint(hWin, &ps);

		// Cleans up the painting process
		EndPaint(hWin, &ps);
		break;

	// When it's time for the window to go away
	case WM_DESTROY:
		//PostQuitMessage(0);
		//gAESysWinExists = false;
		break;

	// called any time the window is moved
	case WM_MOVE:
		// Invalidate the rect to force a redraw
		InvalidateRect(hWin, NULL, FALSE);
		break;

	case WM_ACTIVATE:
		// DO NOT REMOVE THIS
		// *(AESysGetAppActive()) = (LOWORD(wp) == WA_INACTIVE) ? 0 : 1;
		break;

	default:
		return DefWindowProc(hWin, msg, wp, lp);
	}

	return 0;
}


// ---------------------------------------------------------------------------
// Static functions implementation

// ---------------------------------------------------------------------------


