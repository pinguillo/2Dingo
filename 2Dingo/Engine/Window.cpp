#include "Window.h"

#include "Util\Logger.h"

#include <SDL2\SDL.h>
#include <GLEW\glew.h>

Window::Window()
{
}

Window::~Window()
{
	if (mWindow != nullptr)
	{
		delete mWindow;
	}
}

void Window::Create(const char* windowTitle, int screenWidth, int screenHeight, unsigned int flags)
{
	// Creates the SDL window and crash the program if it fails
	if (createWindow(windowTitle, screenWidth, screenHeight, flags) != 0)
	{
		SDL_Quit();
		Logger::Fatal("SDL window could not be created");
	}
	// Initializes GL and crash the program if it fails
	if(initGL() != 0)
	{
		SDL_Quit();
		Logger::Fatal("Failed to init GL");
	}
}

void Window::Swap()
{
	SDL_GL_SwapWindow(mWindow);
}

void Window::SetTitle(const char* title)
{
	mWindowTitle = title;
}

void Window::SetSize(int width, int height)
{
	SDL_SetWindowSize(mWindow, width, height);
	mWindowWidth = width;
	mWindowHeight = height;
}

void Window::SetSwapInterval(int mode)
{
	if (SDL_GL_SetSwapInterval(mode) == -1)
	{
		Logger::Error("Failed to set SwapInterval to %n ... setting to 1", mode);
	}
}

void Window::SetWidth(int width)
{
	SetSize(width, mWindowHeight);
}

void Window::SetHeight(int height)
{
	SetSize(mWindowWidth, height);
}

int Window::createWindow(const char* windowTitle, int windowWidth, int windowHeight, unsigned int flags)
{
	mWindowWidth = windowWidth;
	mWindowHeight = windowHeight;
	mWindowTitle = windowTitle;

	// Setup window flags
	Uint32 winFlags = SDL_WINDOW_OPENGL;
	if (flags & INVISIBLE) { winFlags |= SDL_WINDOW_HIDDEN; }
	if (flags & FULLSCREEN) { winFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP; }
	if (flags & BORDERLESS) { winFlags |= SDL_WINDOW_BORDERLESS; }

	//Some random gl stuff
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	//Create window
	mWindow = SDL_CreateWindow
	(
		windowTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight,
		winFlags
	);
	if (mWindow == nullptr)
	{
		return -1;
	}
	return 0;
}

int Window::initGL()
{
	//GL context
	SDL_GLContext glContext = SDL_GL_CreateContext(mWindow);
	if (glContext == nullptr)
	{
		Logger::Error("GL context could not be created");
		return -1;
	}

	//Init GLEW
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{ 
		Logger::Error("Could not initialize GLEW");
		return -1;
	}

	setGLAttributes();

	Logger::Info(">>>>> OpenGL version %s",(char*)glGetString(GL_VERSION));
	return 0;
}

void Window::setGLAttributes()
{
	if(SDL_GL_SetSwapInterval(-1) == -1)
	{
		Logger::Error("Failed to set SwapInterval to -1... setting to 1");
		if (SDL_GL_SetSwapInterval(1) == -1)
		{
			Logger::Error("Failed to set SwapInterval to 1... setting to 0 (no vsync)");
			SDL_GL_SetSwapInterval(0);
		}
	}
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
