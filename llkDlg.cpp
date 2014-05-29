// llkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "llk.h"
#include "llkDlg.h"
#include "Gameproc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLlkDlg dialog

CLlkDlg::CLlkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLlkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLlkDlg)
	m_SeatNum = 0;
	m_chess_data = _T("");
	m_news = _T("");
	m_autostart = FALSE;
	m_autoplay = FALSE;
	m_speed = 0;
	m_checkspeed = FALSE;
	m_cleartime = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLlkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLlkDlg)
	DDX_Control(pDX, IDC_CHECK3, m_ctl_checkspeed);
	DDX_Control(pDX, IDC_SLIDER1, m_ctl_speed);
	DDX_Text(pDX, IDC_EDIT1, m_SeatNum);
//	DDX_Text(pDX, IDC_EDIT2, m_chess_data);
//	DDX_Text(pDX, IDC_EDIT3, m_news);
	DDX_Check(pDX, IDC_CHECK1, m_autostart);
	DDX_Check(pDX, IDC_CHECK2, m_autoplay);
	DDX_Slider(pDX, IDC_SLIDER1, m_speed);
	DDX_Check(pDX, IDC_CHECK3, m_checkspeed);
	DDX_Check(pDX, IDC_CLEAR, m_cleartime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLlkDlg, CDialog)
	//{{AFX_MSG_MAP(CLlkDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, OnGetSeatNum)
//	ON_BN_CLICKED(IDC_GET_CHESS, OnGetChess)
	ON_BN_CLICKED(IDC_BUTTON2, OnClickOne)
	ON_BN_CLICKED(IDC_Clear_All, OnClearAll)
	ON_BN_CLICKED(IDC_CHECK1, OnAutoStart)
	ON_BN_CLICKED(IDC_CHECK2, OnAutoPlay)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheckSpeed)
	ON_BN_CLICKED(IDC_CLEAR, OnClearTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLlkDlg message handlers

BOOL CLlkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	this->m_SeatNum = 1000; 
	UpdateData(false);
    this->m_ctl_speed.SetRange(0,10000);
	this->m_ctl_speed.SetTicFreq(1000);
	this->m_ctl_speed.SetPos(1000);
	this->m_ctl_checkspeed.SetCheck(1);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLlkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLlkDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLlkDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLlkDlg::OnGetseatNum() 
{
	// TODO: Add your control notification handler code here
	
}

void CLlkDlg::OnGetSeatNum() 
{
	 HWND gameh = ::FindWindow(NULL,GameName);
	 DWORD ProcessId;
	 ::GetWindowThreadProcessId(gameh,&ProcessId);
	 HANDLE ProcessH = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessId);
	 DWORD bybead;
	 LPCVOID pbase = (LPCVOID)0x00B6B4F4;
	 LPVOID nbeffuer = (LPVOID)&m_SeatNum;
     ::ReadProcessMemory(ProcessH,pbase,nbeffuer,1,&bybead);
	 UpdateData(false);
}
void CLlkDlg::OnGetChess() 
{
	 HWND gameh = ::FindWindow(NULL,GameName);
	 DWORD ProcessId;
	 ::GetWindowThreadProcessId(gameh,&ProcessId);
	 HANDLE ProcessH = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessId);
	 DWORD bybead;
	 LPCVOID pbase = (LPCVOID)0x0012A480;
	 LPVOID nbeffuer = (LPVOID)&chess_data;
	 ::ReadProcessMemory(ProcessH,pbase,nbeffuer,11*19,&bybead);
     char sh[2]="";
	 m_chess_data = "";
	 for(long y=0;y<11;y++)
	 {  
		 for(long x=0;x<19;x++)
		 { 
			 memset(sh,0,sizeof(sh));
			 itoa(chess_data[y][x],sh,16);
			 m_chess_data += sh;
			 m_chess_data += ",";
		 }
		 m_chess_data += "\r\n";
	 }
	 UpdateData(false);
}

void CLlkDlg::OnClickOne() 
{
	 
	 if(ClearPair() == 1) m_news = "成功!";
	 else m_news = "失败!";
	 UpdateData(false);
}

void CLlkDlg::OnClearAll() 
{
     while(ClearPair() == 1) ;	
}

//////////////
VOID CALLBACK playproc(
  HWND hwnd,     // handle of window for timer messages
  UINT uMsg,     // WM_TIMER message
  UINT idEvent,  // timer identifier
  DWORD dwTime   // current system time
)
{
 	ClearPair();
}

///////////
VOID CALLBACK startproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
	INT flag,readsize;

//	AfxMessageBox("OK1");

    gameh = ::FindWindow(NULL,GameName);
 	::GetWindowThreadProcessId(gameh,&ProcessId);
	ProcessH = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessId);
	if (gameh==0) { /*AfxMessageBox("未成功读出数据");*/return;  }
   
	//AfxMessageBox("OK2");

	::ReadProcessMemory(ProcessH,(LPCVOID)(0x01C461C8),(LPVOID)(&flag),4,(LPDWORD)(&readsize));
	if(readsize == 0) { AfxMessageBox("未成功读出数据"); return;}
	//AfxMessageBox("读出数据");
	if(flag == 0)
 	    StartGame(); //自动开局
	//AfxMessageBox("成功"); 
}
///////////
 const playid = 111,startid=112;

void CLlkDlg::OnAutoStart() 
{
	UpdateData(true);
	if(m_autostart)	
	{
        //AfxMessageBox("ok1");
		SetTimer(startid,3000,&startproc);
	}
	else 
	{
		KillTimer(startid);
	}
}

long t=1000;
void CLlkDlg::OnAutoPlay() 
{
	
	UpdateData(true);
	printf("%d\n",t);
	if(m_autoplay)
	{   
		SetTimer(playid,t,&playproc);
	}
	else
	{
		KillTimer(playid);
	}
}
void CLlkDlg::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	t  = m_ctl_speed.GetPos();
	m_SeatNum = t;
    if(m_autoplay)
	{
		KillTimer(playid);
		SetTimer(playid,t,&playproc);
	}
	UpdateData(false);
	*pResult = 0;
}

void CLlkDlg::OnCheckSpeed() 
{
	UpdateData(true);
	::EnableWindow(m_ctl_speed.m_hWnd,m_checkspeed);
}

void CLlkDlg::OnClearTime() 
{
	// AfxMessageBox("ok0");
	 UpdateData(true);
	 if(m_cleartime) 
	 {
		 //AfxMessageBox("ok2");
		 ClearTime();
	 }
	 else
	 {
		 RcoveryTime();
	 }
	
}
