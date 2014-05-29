#include "stdafx.h"

LPCTSTR GameName = "QQ游戏 - 连连看角色版";
HWND gameh;
DWORD ProcessId;
HANDLE ProcessH;
RECT r1;

void StartGame()
{
	POINT p;
	gameh = ::FindWindow(NULL,GameName);
	SetWindowPos(gameh,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); //让窗口置顶
	Sleep(1000);
	::GetWindowRect(gameh,&r1);
	GetCursorPos(&p);
	SetCursorPos(r1.left + 678,r1.top + 572);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

	Sleep(60);
	SetCursorPos(p.x,p.y);
}

char chess_data[11][19]; // [y][x]
void UpDataCress()
{
     gameh = ::FindWindow(NULL,GameName);
 	 ::GetWindowThreadProcessId(gameh,&ProcessId);
	 ProcessH = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessId);
	 DWORD bybead;
	 LPCVOID pbase = (LPCVOID)0x0012A480;
	 LPVOID nbeffuer = (LPVOID)&chess_data;
	 ::ReadProcessMemory(ProcessH,pbase,nbeffuer,11*19,&bybead);
}
int checklink(POINT a,POINT b)
{
	POINT c;
	if(a.x == b.x && a.y == b.y) return 1;

	else if(a.x == b.x)
	{ 
		if(a.y > b.y) { c = a; a = b; b = c; }

		for(int i=a.y+1;i<b.y;i++)
			if(chess_data[i][a.x] != 0)
				return 0;
        return 1;
	}

	else if(a.y == b.y)
	{
		if(a.x > b.x) { c = a; a = b; b = c; }

		for(int i=a.x+1;i<b.x;i++)
			if(chess_data[a.y][i] != 0)
				return 0;
        return 1;
	}
	
}
int check(POINT a,POINT b)
{
	POINT c,d;
	if( (a.x == b.x || a.y == b.y) && checklink(a,b) ) return 1;
    
	for(int x=0;x<19;x++)
	{ 
		c.x = x; c.y = a.y;
		d.x = x; d.y = b.y;
		if( (chess_data[c.y][c.x] == 0  || c.x == a.x) && (chess_data[d.y][d.x] == 0 || d.x == b.x) &&
			checklink(c,a) && checklink(d,b) && checklink(c,d) )
			return 1;
	}
    for(int y=0;y<11;y++)
	{
		c.x = a.x; c.y = y;
		d.x = b.x; d.y = y;
		if( (chess_data[c.y][c.x] == 0 || c.y == a.y) && (chess_data[d.y][d.x] == 0 || d.y == b.y) &&
			checklink(c,a) && checklink(d,b) && checklink(c,d) )
			return 1;
	}
	
	return 0;
}
void click2p(POINT a,POINT b)
{
     int x=26,y=196,xn=31,yn=34;
	 HWND hwnd=FindWindow(NULL,GameName);
     SendMessage(hwnd,WM_LBUTTONDOWN,0,( (a.y*yn+y)<<16 ) + x+a.x*xn);//
     SendMessage(hwnd,WM_LBUTTONUP  ,0,( (a.y*yn+y)<<16 ) + x+a.x*xn);//
     Sleep(1);
	 SendMessage(hwnd,WM_LBUTTONDOWN,0,( (b.y*yn+y)<<16 ) + x+b.x*xn);//
     SendMessage(hwnd,WM_LBUTTONUP  ,0,( (b.y*yn+y)<<16 ) + x+b.x*xn);//
}
int ClearPair()
{
	 POINT a,b;
	 UpDataCress();
	 for(int y1=0;y1<11;y1++)
	    for(int x1=0;x1<19;x1++)
		{  
			for(int y2 = y1;y2<11;y2++)
				for(int x2 = 0;x2<19;x2++)
					if((x1!=x2 || y1!=y2) && chess_data[y1][x1] == chess_data[y2][x2] && 
					   chess_data[y2][x2] != 0)
					{ 
						a.x = x1; a.y = y1;
					    b.x = x2; b.y = y2;
					    if( check(a,b) )  
						{ 
						   click2p(a,b);
                           return 1;
						}
					}			
		}

     return 0;
}
int ClearTime()
{
	gameh = ::FindWindow(NULL,GameName);
//	AfxMessageBox("ok1");
	if(gameh == 0) return 0;
 	::GetWindowThreadProcessId(gameh,&ProcessId);
	ProcessH = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessId);

	byte acode[6]={0x90,0x90,0x90,0x90,0x90,0x90};
	long bywritesize;
	WriteProcessMemory(ProcessH,(LPVOID)(0x0041d8ad),(LPVOID)(acode),6,(LPDWORD)(&bywritesize));
    return 1;
}
int RcoveryTime()
{
	gameh = ::FindWindow(NULL,GameName);
//	AfxMessageBox("ok1");
	if(gameh == 0) return 0;
 	::GetWindowThreadProcessId(gameh,&ProcessId);
	ProcessH = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessId);


	byte oldcode[6]={0xFF,0x8E,0xD8,0x49,0x00,0x00};
	long bywritesize;
	WriteProcessMemory(ProcessH,(LPVOID)(0x0041d8ad),(LPVOID)(oldcode),6,(LPDWORD)(&bywritesize));
	return 1;
}