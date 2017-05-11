/*
NOTES:
- using Warning Level Level3 instead of 4 due to glm "warning treated as error"
*/

/*
references:
- DirectX book (?) (#.#.#)
- http://www.winprog.org/tutorial/simple_window.html (window creation) (#.#.#)
- http://www.cprogramming.com/tutorial/wgl_wiggle_functions.html (window procedure) (#.#.#)
- http://www.cprogramming.com/tutorial/opengl_introduction.html (OpenGL basics tutorial) (#.#.#)
- bennybox youtube-videos (28.06.2016)
- Jamie King youtube-videos (28.06.2016)
- Tommi code (zinc)
- http://rivermanmedia.com/object-oriented-game-programming-the-scene-system/
- http://gamedev.stackexchange.com/questions/8278/what-should-be-contained-in-a-game-scene-graph - separate graphs for rendering and logic
- https://www.youtube.com/watch?v=4p-E_31XOPM - frustum culling explanation
*/

#define WIN32_LEAN_AND_MEAN // "This syntax prevents Visual C++ from linking modules that you aren't going to need in your application."

#include <windows.h>
#include <windowsx.h>
#include <ctime>
#include "GL/glew.h"
#include "SceneManager.hpp"
#include "Input.hpp"

// global variables
HGLRC g_renderContext;
HDC g_deviceContext;
GLuint g_width;
GLuint g_height;
SceneManager* g_sceneManager;
glm::ivec2 g_oldMousePos;

Key keyFromWPARAM(WPARAM wParam)
{
	return
		wParam == VK_SPACE ? Key_Space :
		//wParam == '\'' ? Key_Apostrophe :
		wParam == ',' ? Key_Comma :
		wParam == '-' ? Key_Minus :
		wParam == '/' ? Key_Slash :
		wParam == '0' ? Key_0 :
		wParam == '1' ? Key_1 :
		wParam == '2' ? Key_2 :
		wParam == '3' ? Key_3 :
		wParam == '4' ? Key_4 :
		wParam == '5' ? Key_5 :
		wParam == '6' ? Key_6 :
		wParam == '7' ? Key_7 :
		wParam == '8' ? Key_8 :
		wParam == '9' ? Key_9 :
		wParam == ';' ? Key_Semicolon :
		wParam == '=' ? Key_Equal :
		wParam == 'A' ? Key_A :
		wParam == 'B' ? Key_B :
		wParam == 'C' ? Key_C :
		wParam == 'D' ? Key_D :
		wParam == 'E' ? Key_E :
		wParam == 'F' ? Key_F :
		wParam == 'G' ? Key_G :
		wParam == 'H' ? Key_H :
		wParam == 'I' ? Key_I :
		wParam == 'J' ? Key_J :
		wParam == 'K' ? Key_K :
		wParam == 'L' ? Key_L :
		wParam == 'M' ? Key_M :
		wParam == 'N' ? Key_N :
		wParam == 'O' ? Key_O :
		wParam == 'P' ? Key_P :
		wParam == 'Q' ? Key_Q :
		wParam == 'R' ? Key_R :
		wParam == 'S' ? Key_S :
		wParam == 'T' ? Key_T :
		wParam == 'U' ? Key_U :
		wParam == 'V' ? Key_V :
		wParam == 'W' ? Key_W :
		wParam == 'X' ? Key_X :
		wParam == 'Y' ? Key_Y :
		wParam == 'Z' ? Key_Z :
		wParam == '{' ? Key_LeftBracket :
		wParam == '\\' ? Key_Backslash :
		wParam == '}' ? Key_RightBracket :
		wParam == '`' ? Key_GraveAccent :
		wParam == VK_ESCAPE ? Key_Escape :
		wParam == VK_RETURN ? Key_Enter :
		wParam == VK_TAB ? Key_Tab :
		wParam == VK_BACK ? Key_Backspace :
		wParam == VK_INSERT ? Key_Insert :
		wParam == VK_DELETE ? Key_Delete :
		wParam == VK_RIGHT ? Key_Right :
		wParam == VK_LEFT ? Key_Left :
		wParam == VK_DOWN ? Key_Down :
		wParam == VK_UP ? Key_Up :
		wParam == VK_SPACE ? Key_PageUp :
		wParam == VK_SPACE ? Key_PageDown :
		wParam == VK_SPACE ? Key_Home :
		wParam == VK_SPACE ? Key_End :
		wParam == VK_SPACE ? Key_CapsLock :
		wParam == VK_SPACE ? Key_ScrollLock :
		wParam == VK_SPACE ? Key_NumLock :
		wParam == VK_SPACE ? Key_PrintScreen :
		wParam == VK_SPACE ? Key_Pause :
		wParam == VK_F1 ? Key_F1 :
		wParam == VK_F2 ? Key_F2 :
		wParam == VK_F3 ? Key_F3 :
		wParam == VK_F4 ? Key_F4 :
		wParam == VK_F5 ? Key_F5 :
		wParam == VK_F6 ? Key_F6 :
		wParam == VK_F7 ? Key_F7 :
		wParam == VK_F8 ? Key_F8 :
		wParam == VK_F9 ? Key_F9 :
		wParam == VK_F10 ? Key_F10 :
		wParam == VK_F11 ? Key_F11 :
		wParam == VK_F12 ? Key_F12 :
		wParam == VK_F13 ? Key_F13 :
		wParam == VK_F14 ? Key_F14 :
		wParam == VK_F15 ? Key_F15 :
		wParam == VK_F16 ? Key_F16 :
		wParam == VK_F17 ? Key_F17 :
		wParam == VK_F18 ? Key_F18 :
		wParam == VK_F19 ? Key_F19 :
		wParam == VK_F20 ? Key_F20 :
		wParam == VK_F21 ? Key_F21 :
		wParam == VK_F22 ? Key_F22 :
		wParam == VK_F23 ? Key_F23 :
		wParam == VK_F24 ? Key_F24 :
		wParam == VK_NUMPAD0 ? Key_Pad0 :
		wParam == VK_NUMPAD1 ? Key_Pad1 :
		wParam == VK_NUMPAD2 ? Key_Pad2 :
		wParam == VK_NUMPAD3 ? Key_Pad3 :
		wParam == VK_NUMPAD4 ? Key_Pad4 :
		wParam == VK_NUMPAD5 ? Key_Pad5 :
		wParam == VK_NUMPAD6 ? Key_Pad6 :
		wParam == VK_NUMPAD7 ? Key_Pad7 :
		wParam == VK_NUMPAD8 ? Key_Pad8 :
		wParam == VK_NUMPAD9 ? Key_Pad9 :
		wParam == VK_DECIMAL ? Key_PadDecimal :
		wParam == VK_DIVIDE ? Key_PadDivide :
		wParam == VK_MULTIPLY ? Key_PadMultiply :
		wParam == VK_SUBTRACT ? Key_PadSubtract :
		wParam == VK_ADD ? Key_PadAdd :
		wParam == VK_RETURN ? Key_PadEnter :
		wParam == VK_SPACE ? Key_PadEqual :
		wParam == VK_LSHIFT ? Key_LeftShift :
		wParam == VK_CONTROL ? Key_LeftControl :
		wParam == VK_MENU ? Key_LeftAlt :
		//wParam == VK_SPACE ? Key_LeftSuper :
		wParam == VK_RSHIFT ? Key_RightShift :
		wParam == VK_CONTROL ? Key_RightControl :
		wParam == VK_MENU ? Key_RightAlt :
		//wParam == VK_SPACE ? Key_RightSuper :
		wParam == VK_MENU ? Key_Menu :
		Key_Unknown;
}

// window events
LRESULT onResizeWindow(int width, int height)
{
	g_width = width;
	g_height = height;
	glViewport(0, 0, width, height);
	return 0;
}
LRESULT onMouseMovement(int x, int y)
{
	glm::ivec2 pos = glm::ivec2(x, y);
	g_sceneManager->input(Input(MouseMovementInput(pos - g_oldMousePos, pos)));
	g_oldMousePos = pos;
	return 0;
}
LRESULT onKeyDown(char key)
{
	g_sceneManager->input(Input(KeyboardInput(keyFromWPARAM(key), KeyState_Pressed)));
	return 0;
}
LRESULT onKeyUp(char key)
{
	g_sceneManager->input(Input(KeyboardInput(keyFromWPARAM(key), KeyState_Released)));
	return 0;
}
LRESULT onCloseWindow()
{
	PostQuitMessage(0);
	g_sceneManager->quit();
	return 0;
}
LRESULT onMouseLeftButtonDown(unsigned int x, unsigned int y)
{
	g_sceneManager->input(Input(MouseButtonInput(MouseButton_Left, MouseButtonState_Down, glm::ivec2(x, y))));
	return 0;
}
LRESULT onMouseLeftButtonUp(unsigned int x, unsigned int y)
{
	g_sceneManager->input(Input(MouseButtonInput(MouseButton_Left, MouseButtonState_Up, glm::ivec2(x, y))));
	return 0;
}
LRESULT onMouseMiddleButtonDown(unsigned int x, unsigned int y)
{
	g_sceneManager->input(Input(MouseButtonInput(MouseButton_Middle, MouseButtonState_Down, glm::ivec2(x, y))));
	return 0;
}
LRESULT onMouseMiddleButtonUp(unsigned int x, unsigned int y)
{
	g_sceneManager->input(Input(MouseButtonInput(MouseButton_Middle, MouseButtonState_Up, glm::ivec2(x, y))));
	return 0;
}
LRESULT onMouseRightButtonDown(unsigned int x, unsigned int y)
{
	g_sceneManager->input(Input(MouseButtonInput(MouseButton_Right, MouseButtonState_Down, glm::ivec2(x, y))));
	return 0;
}
LRESULT onMouseRightButtonUp(unsigned int x, unsigned int y)
{
	g_sceneManager->input(Input(MouseButtonInput(MouseButton_Right, MouseButtonState_Up, glm::ivec2(x, y))));
	return 0;
}

// window procedure
LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wParameter, LPARAM lParameter)
{
	return
		message == WM_DESTROY || message == WM_CLOSE ? onCloseWindow() :
		message == WM_SIZE ? onResizeWindow(LOWORD(lParameter), HIWORD(lParameter)) :
		message == WM_MOUSEMOVE ? onMouseMovement(GET_X_LPARAM(lParameter), GET_Y_LPARAM(lParameter)) :
		message == WM_KEYDOWN ? onKeyDown((char)wParameter) :
		message == WM_KEYUP ? onKeyUp((char)wParameter) :
		message == WM_LBUTTONDOWN ? onMouseLeftButtonDown(GET_X_LPARAM(lParameter), GET_Y_LPARAM(lParameter)) :
		message == WM_LBUTTONUP ? onMouseLeftButtonUp(GET_X_LPARAM(lParameter), GET_Y_LPARAM(lParameter)) :
		message == WM_MBUTTONDOWN ? onMouseMiddleButtonDown(GET_X_LPARAM(lParameter), GET_Y_LPARAM(lParameter)) :
		message == WM_MBUTTONUP ? onMouseMiddleButtonUp(GET_X_LPARAM(lParameter), GET_Y_LPARAM(lParameter)) :
		message == WM_RBUTTONDOWN ? onMouseRightButtonDown(GET_X_LPARAM(lParameter), GET_Y_LPARAM(lParameter)) :
		message == WM_RBUTTONUP ? onMouseRightButtonUp(GET_X_LPARAM(lParameter), GET_Y_LPARAM(lParameter)) :
		DefWindowProc(window, message, wParameter, lParameter);
}

// wrappers
BOOL setupPixelFormat(HDC deviceContext)
{
	// describe pixel format
	static PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize				= sizeof(PIXELFORMATDESCRIPTOR);	//size of structure
	pfd.nVersion			= 1;										//default version
	pfd.dwFlags				= PFD_DRAW_TO_WINDOW					//window drawing support
								| PFD_SUPPORT_OPENGL					//.
								| PFD_DOUBLEBUFFER;					//.
	pfd.iPixelType			= PFD_TYPE_RGBA;						//RGBA color mode
	pfd.cColorBits			= 32;										//32 bit color mode
	pfd.cRedBits			= 0;										//ignore color bits
	pfd.cRedShift			= 0;										//.
	pfd.cGreenBits			= 0;										//.
	pfd.cGreenShift		= 0;										//.
	pfd.cBlueBits			= 0;										//.
	pfd.cBlueShift			= 0;										//.
	pfd.cAlphaBits			= 0;										//no alpha buffer
	pfd.cAlphaShift		= 0;										//ignore shift bit
	pfd.cAccumBits			= 0;										//no accumulation buffer
	pfd.cAccumRedBits		= 0;										//ignore accumulation bits
	pfd.cAccumGreenBits	= 0;										//.
	pfd.cAccumBlueBits	= 0;										//.
	pfd.cAccumAlphaBits	= 0;										//.
	pfd.cDepthBits			= 16;										//16 bit z-buffer size
	pfd.cStencilBits		= 0;										//no stencil buffer
	pfd.cAuxBuffers		= 0;										//no aux buffer
	pfd.iLayerType			= PFD_MAIN_PLANE;						//main drawing plane
	pfd.bReserved			= 0;										//reserved
	pfd.dwLayerMask		= 0;										//layer masks ignored
	pfd.dwVisibleMask		= 0;										//.
	pfd.dwDamageMask		= 0;										//.
	
	// choose best matching format
	int index = ChoosePixelFormat(deviceContext, &pfd);

	// set the pixel format to the device context
	return SetPixelFormat(deviceContext, index, &pfd);
}
HWND createWindow(HINSTANCE instance, int width, int height, const char* title)
{
	// setup window class
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = (LPCWSTR)"my awesome window class";
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register window class
	if (RegisterClassEx(&windowClass) == NULL) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return nullptr;
	}
	else {
		// register window-class
		HWND window = CreateWindowEx(
			WS_EX_CLIENTEDGE,           // extended style
			windowClass.lpszClassName,
			(LPCWSTR)title,             // title
			WS_OVERLAPPEDWINDOW,        // style
			CW_USEDEFAULT,              // x position
			CW_USEDEFAULT,              // y position
			width,
			height,
			NULL,
			NULL,
			instance,
			NULL
			);
		if (window == NULL) {
			MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
			return nullptr;
		}
		else{
			return window;
		}
	}
}

// MAIN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	(void)previousInstance;
	(void)commandLine;

	// CREATE WINDOW
	HWND window = createWindow(instance, 1600, 900, "my windo");
	ShowWindow(window, showCommand);

	// SETUP AND INITIALIZE OPENGL
	g_deviceContext = GetDC(window);                      // get the device context for the window
	setupPixelFormat(g_deviceContext);                    // setup pixel format for render context
	g_renderContext = wglCreateContext(g_deviceContext);  // create rendering context
	wglMakeCurrent(g_deviceContext, g_renderContext);     // make rendering context to current
	glewInit();                                           // initialize opengl

	// INITIALIZE SCENES
	g_sceneManager = new SceneManager();

	// HANDLE MAIN LOOP
	float oldTime = (float)clock() * 0.001f;
	MSG msg = { 0 };
	bool isRunning = true;
	while (isRunning)
	{
		while (PeekMessage(&msg, window, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isRunning = false;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		float currentTime = (float)clock() * 0.001f;
		float deltaTime = currentTime - oldTime;
		oldTime = currentTime;

		g_sceneManager->update(deltaTime);
		g_sceneManager->draw();
		SwapBuffers(g_deviceContext);

		if (g_sceneManager->isQuitRequested())
			isRunning = false;

		Sleep(5);
	}
	
	// DEINITIALIZE
	delete g_sceneManager;

	wglMakeCurrent(g_deviceContext, NULL);  // deselect rendering context
	wglDeleteContext(g_renderContext);      // delete rendering context

	return msg.wParam;
}