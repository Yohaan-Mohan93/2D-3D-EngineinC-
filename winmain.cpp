/******************************************************************************************************************************************************************************************
File Name:  winmain.cpp
Author(s):  Yohaan Mohan
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/

#include "Advanced2D.h"

//macro to read the key states
#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000)?1:0)

HINSTANCE g_hInstance;
HWND g_hWnd;
int g_nCmdShow;

//declare global engine object
GAM200::Engine *g_engine;

bool gameover;

//window event callback function
LRESULT WINAPI WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		 case WM_QUIT:
		 case WM_CLOSE:
		 case WM_DESTROY:
			 gameover = true;
			 break;
	   }
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	srand((unsigned int)time(NULL));
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;
	DWORD dwStyle, dwExStyle;
	RECT windowRect;
	int screenHeight, screenWidth;

	//create the game object
	g_engine = new GAM200::Engine();
	
	//let main program have a crack at things before window is created
	if (!game_preload()) {
		MessageBox(g_hWnd, "Error in game preload!", "Error", MB_OK);
		return 0; 
	}
	
	//get window caption string from engine
	char title[255];
	sprintf(title, "%s", g_engine->getAppTitle().c_str());

	//set window dimensions
	windowRect.left = (long)0;
	windowRect.right = (long)g_engine->getScreenWidth();
	windowRect.top = (long)0;
	windowRect.bottom = (long)g_engine->getScreenHeight();


   //create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX); 

	//fill the struct with info
	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WinProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = NULL;
	wc.hCursor	   = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = title;
	wc.hIconSm	   = NULL;

	//set up the window with the class info
	RegisterClassEx(&wc);

	//set up the screen in windowed or fullscreen mode?
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop,&desktop);


	screenWidth  = desktop.bottom;
	screenHeight = desktop.right;


	if(g_engine->getFullscreen()) 
	{
	   DEVMODE dm;
	   memset(&dm, 0, sizeof(dm));
	   dm.dmSize = sizeof(dm);
	   dm.dmPelsWidth = screenWidth;
	   dm.dmPelsHeight = screenHeight;
	   dm.dmBitsPerPel = g_engine->getColorDepth();
	   dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	   if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) 
	   {
		  //MessageBox(NULL, "Display mode failed", NULL, MB_OK);
		  g_engine->setFullscreen(false);
	   }

	   g_engine->setScreenHeight(screenHeight);
	   g_engine->setScreenWidth(screenWidth);

		dwStyle = WS_POPUP;
		dwExStyle = WS_EX_APPWINDOW;
		ShowCursor(TRUE);
	}
	else 
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	}

	//adjust window to true requested size
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	//create the program window
	g_hWnd = CreateWindowEx( 0,
	   title,								 //window class
	   title,								 //title bar
	   dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,	  
	   0, 0,											 //x,y coordinate
	   windowRect.right - windowRect.left,			   //width of the window
	   windowRect.bottom - windowRect.top,			   //height of the window
	   0,											 //parent window
	   0,											 //menu
	   g_hInstance,									  //application instance
	   0);											//window parameters

	//was there an error creating the window?
	if (!g_hWnd) 	
	{
		MessageBox(g_hWnd, "Error creating program window!", "Error", MB_OK);
		return 0; 
	}

	//display the window
	ShowWindow(g_hWnd, g_nCmdShow);
	SetForegroundWindow(g_hWnd);
	SetFocus(g_hWnd);
	UpdateWindow(g_hWnd);


	//initialize the engine
	g_engine->setWindowHandle(g_hWnd);
	if (!g_engine->Init(g_engine->getScreenWidth(), g_engine->getScreenHeight(), g_engine->getColorDepth(), g_engine->getFullscreen())) 	{
		MessageBox(g_hWnd, "Error initializing the engine", "Error", MB_OK);
		return 0;
	}

	// main message loop
	gameover = false;
	while (!gameover)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		g_engine->Update();
	}

   if (g_engine->getFullscreen()) {
	  ShowCursor(TRUE);
   }

	game_end();

	delete g_engine;

	return 1;
}
