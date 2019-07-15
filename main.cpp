#include "stdafx.h"
#include "Game2.h"

#include "debug_new/debug_new.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, int nCmdShow)
{
	MGame2* Game2 = new MGame2;
	if(!Game2->Initialize(hInstance))
	{
		MessageBox(NULL, "Sorry. Some error(s) ocurred. See log for details", "Error", 0);
		SendMessage(Game2->GetHWND(), WM_CLOSE, 0, 0);
		if(Game2) delete Game2;
		LogFile.close();
		return 0;
	}
	Game2->Run();
	if(Game2) delete Game2;
	LogFile<<"Closing application"<<endl;
	LogFile.close();
	
	return 0;
}
