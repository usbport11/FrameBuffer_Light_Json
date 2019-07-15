#ifndef windowH
#define windowH

class MWindow;

typedef void (MWindow::*FrameFunc) ();

class MWindow
{
private:
	const char* sWindowClass;
	const char* sTitle;
	
	string OpenGLVersion;
	string OpenGLVendor;
	string OpenGLRenderer;
	string ShadersVersion;
	
	HINSTANCE m_hInstance;
	SYSTEM_INFO SystemInfo;
	OSVERSIONINFO VersionInfo;
	
	bool MouseInClient;
	
    int SetUpWindow(HWND hWnd);
	int InitGL();
	int CloseGL();
	void ResizeScene(int width, int height);
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void CreateConsole();
	bool SetVSync(bool Enable);
	bool VSyncEnabled;
	
	FrameFunc pFrameUpdateFunc;
	FrameFunc pFrameWaitFunc;
	void FrameUpdateWindowBefore8();
	void FrameUpdateWindowAfter8();
	void FrameWaitVsync();
	void FrameWait();
	
protected:
	bool Exit;
	HDC m_hDC;
	HGLRC m_hGLRC;
	HWND m_hWnd;
	bool WindowInitialized;
	
	int WindowWidth;
    int WindowHeight;
    int HalfWindowSize[2];
    int WindowFix[2];
    
    DWORD CurrTime;
	DWORD DiffTime;
	
	stResolution InitialResolution;
	stResolution CurrentResolution;
	vector<stResolution> Resolutions;
	bool InitResolutions();
	
	bool Fullscreen;
	bool EnterFullscreen();
	bool ExitFullscreen(int Width, int Height);
	bool ChangeWindowSize(int Width, int Height);
	
	//virtual functions
	virtual void OnDraw();
	virtual void OnActivate(WPARAM wParam);
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnClose();
	virtual void OnSize();
	virtual void OnMouseHover(WPARAM wParam, LPARAM lParam);
	virtual void OnMouseLButton(WPARAM wParam, LPARAM lParam);
	
public:
	MWindow();
	~MWindow();
	int CreateMainWindow(HINSTANCE hInstance);
	int CreateMainWindow(HINSTANCE hInstance, int Width, int Height);
	LRESULT CALLBACK WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
	
	void Run();
	HWND GetHWND();
};

#endif
