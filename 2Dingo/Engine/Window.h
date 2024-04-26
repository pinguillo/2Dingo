#pragma once

struct SDL_Window;

enum WindowFlags
{
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLESS = 0x4
};

/// <summary>
/// This class sorta encapsulates the window creation and GL initialization
/// </summary>
class Window
{
public:
	Window();
	~Window();

	// Creates the window and initializes OpenGL
	void Create(const char* windowTitle, int windowWidth, int windowHeight, unsigned int flags);
	// Swaps the GL buffer
	void Swap();

	// Sets the window title
	void SetTitle(const char* title);
	// Sets the window width and keeps the height
	void SetWidth(int width);
	// Sets the window height and keeps the width
	void SetHeight(int height);
	// Sets the window size
	void SetSize(int width, int height);

	//0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync
	void SetSwapInterval(int mode);

	// Returns the window width
	int getWidth() { return mWindowWidth; }
	// Returns the window height
	int getHeight() { return mWindowHeight; }

private:
	// Creates the actual SDL window
	int createWindow(const char* windowTitle, int windowWidth, int windowHeight, unsigned int flags);
	// Inits GL
	int initGL();
	// Sets some OpenGL attributes
	void setGLAttributes();

private:
	SDL_Window* mWindow;

	const char* mWindowTitle = "tittle";
	int mWindowWidth = 640;
	int mWindowHeight = 480;
};