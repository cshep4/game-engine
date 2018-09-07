#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <Commdlg.h>
#include <gl/glut.h>

#include "OpenGL.h"
#include "timer.h"
#include "resource.h"

bool exiting = false;
long windowWidth = 1024;
long windowHeight = 768;
long windowBits = 32;
bool fullscreen = false;
HDC hDC;

OpenGL *openGLRender = NULL;
CHiResTimer *g_hiResTimer = NULL;

void SetupPixelFormat(HDC hDC)
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{	
		sizeof(PIXELFORMATDESCRIPTOR),	// size
			1,							// version
			PFD_SUPPORT_OPENGL |		// OpenGL window
			PFD_DRAW_TO_WINDOW |		// render to window
			PFD_DOUBLEBUFFER,			// support double-buffering
			PFD_TYPE_RGBA,				// color type
			32,							// prefered color depth
			0, 0, 0, 0, 0, 0,			// color bits (ignored)
			0,							// no alpha buffer
			0,							// alpha bits (ignored)
			0,							// no accumulation buffer
			0, 0, 0, 0,					// accum bits (ignored)
			16,							// depth buffer
			0,							// no stencil buffer
			0,							// no auxiliary buffers
			PFD_MAIN_PLANE,				// main layer
			0,							// reserved
			0, 0, 0,					// no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static HGLRC hRC;
	int height, width;
	int fwKeys;
	LPARAM keyData, menuClick;
	COLORREF clrRedish = RGB(255, 25, 2);
	PAINTSTRUCT ps;
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	// dispatch messages
	switch (uMsg)
	{	
	case WM_COMMAND:
		menuClick = LOWORD(wParam);
		switch (menuClick)
		{
			case ID_FILE_LOADFILE: // load in new level file
				ZeroMemory(&ofn, sizeof(ofn));

				ofn.lStructSize = sizeof(ofn); // Set up the open file dialog
				ofn.hwndOwner = hWnd;
				ofn.lpstrFilter = "XML Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
				ofn.lpstrFile = szFileName;
				ofn.nMaxFile = MAX_PATH;
				ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				ofn.lpstrDefExt = "xml";
				if(GetOpenFileName(&ofn))
				{
					openGLRender->setFileName(szFileName); // set the file name for new file
				}
				openGLRender->loadNewFile();
				break;
			case ID_FILE_EXIT: // exit the program
				PostQuitMessage(0);
				break;
			case ID_LIGHTS_LIGHTS_ON: // turn lights on
				openGLRender->enableLights();
				break;
			case ID_LIGHTS_LIGHTS_OFF: // turn lights off
				openGLRender->disableLights();
				break;
			case ID_CAMERA_CHARACTERCAMERA: // switch to character camera
				openGLRender->setCharacterCamera();
				break;
			case ID_CAMERA_PANCAMERA: // pan camera
				openGLRender->setPanCamera();
				break;
		}
		break;
	case WM_CREATE:			// window creation
		hDC = GetDC(hWnd);
		SetupPixelFormat(hDC);
		//SetupPalette();
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		break;

	case WM_DESTROY:			// window destroy
	case WM_QUIT:
	case WM_CLOSE:					// windows is closing

		// deselect rendering context and delete it
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);

		// send WM_QUIT to message queue
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		height = HIWORD(lParam);		// retrieve width and height
		width = LOWORD(lParam);

		openGLRender->setupProjection(width, height);

		break;

	case WM_ACTIVATEAPP:		// activate app
		break;

	case WM_PAINT:				// paint
		hDC = BeginPaint(hWnd, &ps);
		SetTextColor(hDC,RGB(255,255,255));
		openGLRender->printTextToScreen(hDC, hWnd);
        //TextOut(hDc, 70, 50, szMessage, strlen(szMessage));
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:		// left mouse button
		break;

	case WM_RBUTTONDOWN:		// right mouse button
		break;

	case WM_MOUSEMOVE:			// mouse movement
		break;

	case WM_LBUTTONUP:			// left button release
		break;

	case WM_RBUTTONUP:			// right button release
		break;

	case WM_KEYDOWN:
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 

		switch(fwKeys)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:// set corresponding key boolean to be true, so can be used in openGL		
			openGLRender->setLeftPressed(true);
			break;
		case VK_RIGHT:
			openGLRender->setRightPressed(true);
			break;
		case VK_UP:
			openGLRender->setUpPressed(true);
			break;
		case VK_DOWN:
			openGLRender->setDownPressed(true);
			break;
		case VK_SHIFT:
			//switch between cameras
			openGLRender->switchCamera();
			break;
		case VK_SPACE:
			openGLRender->splashScreen = false;
			break;
		case 0x41: // A
			openGLRender->setAPressed(true);
			break;
		case 0x44: // D
			openGLRender->setDPressed(true);
			break;
		case 0x53: // S
			openGLRender->setSPressed(true);
			break;
		case 0x57: // W
			openGLRender->setWPressed(true);
			break;
		case 0x4C: // L
			//enable/disable lights
			openGLRender->toggleLights();
			break;
		case 0x4D: // M
			//enable/disable mouse camera movement
			openGLRender->setMouseMove(!openGLRender->getMouseMove());
			ShowCursor(!openGLRender->getMouseMove());
		default:
			break;
		}
		break;
	case WM_KEYUP:
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 

		switch(fwKeys)
		{
		case VK_LEFT:// set corresponding key boolean to be false, so can stop being used in openGL	
			openGLRender->setLeftPressed(false);
			break;
		case VK_RIGHT:
			openGLRender->setRightPressed(false);
			break;
		case VK_UP:
			openGLRender->setUpPressed(false);
			break;
		case VK_DOWN:
			openGLRender->setDownPressed(false);
			break;
		case 0x41: // A
			openGLRender->setAPressed(false);
			break;
		case 0x44: // D
			openGLRender->setDPressed(false);
			break;
		case 0x53: // S
			openGLRender->setSPressed(false);
			break;
		case 0x57: // W
			openGLRender->setWPressed(false);
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;		// window class
	HWND	   hwnd;			// window handle
	MSG		   msg;				// message
	DWORD	   dwExStyle;		// Window Extended Style
	DWORD	   dwStyle;			// Window Style
	RECT	   windowRect;

	openGLRender = new OpenGL;
	g_hiResTimer = new CHiResTimer;

	ShowCursor(false);

	windowRect.left=(long)0;						// Set Left Value To 0
	windowRect.right=(long)windowWidth;	// Set Right Value To Requested Width
	windowRect.top=(long)0;							// Set Top Value To 0
	windowRect.bottom=(long)windowHeight;	// Set Bottom Value To Requested Height

	// fill out the window class structure
	windowClass.cbSize			= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc		= MainWindowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	// default icon
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);		// default arrow
	windowClass.hbrBackground	= NULL;								// don't need background
	windowClass.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);		// menu
	windowClass.lpszClassName	= "GLClass";
	windowClass.hIconSm			= LoadIcon(NULL, IDI_WINLOGO);		// windows logo small icon

	// register the windows class
	if (!RegisterClassEx(&windowClass))
		return 0;

	if (fullscreen)								// fullscreen?
	{
		DEVMODE dmScreenSettings;					// device mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);	
		dmScreenSettings.dmPelsWidth = windowWidth;			// screen width
		dmScreenSettings.dmPelsHeight = windowHeight;			// screen height
		dmScreenSettings.dmBitsPerPel = windowBits;				// bits per pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// 
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// setting display mode failed, switch to windowed
			MessageBox(NULL, "Display mode failed", NULL, MB_OK);
			fullscreen = FALSE;	
		}
	}

	if (fullscreen)								// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;					// Window Extended Style
		dwStyle=WS_POPUP;						// Windows Style
		ShowCursor(FALSE);						// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// class registered, so now create our window
	hwnd = CreateWindowEx(NULL,									// extended style
		"GLClass",							// class name
		"Game Engine",	// app name
		dwStyle | WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,								// x,y coordinate
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, // width, height
		NULL,								// handle to parent
		NULL,								// handle to menu
		hInstance,							// application instance
		NULL);								// no extra params

	hDC = GetDC(hwnd);

	// check if window creation failed (hwnd would equal NULL)
	if (!hwnd)
		return 0;

	HMENU hMenu = LoadMenu(hInstance, windowClass.lpszMenuName);
	ShowWindow(hwnd, SW_SHOW);			// display the window
	UpdateWindow(hwnd);					// update the window

	openGLRender->init();
	g_hiResTimer->Init();

	while (!exiting)
	{
		//openGLRender->printTextToScreen(hDC, hwnd);
		if (openGLRender->getMouseMove())// check if move is used for camera movement
		{
			openGLRender->mouseMove(windowWidth, windowHeight);// mouse camera movement
		}
		openGLRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));//draw scene
		openGLRender->Render();
		SwapBuffers(hDC);
		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				exiting = true;
				break;
			}

			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}

	delete openGLRender;

	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);						// Show Mouse Pointer
	}

	return (int)msg.wParam;
}