// llkDlg.h : header file
//

#if !defined(AFX_LLKDLG_H__4AA58293_6D9F_492E_8578_83A0B717F6C5__INCLUDED_)
#define AFX_LLKDLG_H__4AA58293_6D9F_492E_8578_83A0B717F6C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLlkDlg dialog

class CLlkDlg : public CDialog
{
// Construction
public:
	CLlkDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLlkDlg)
	enum { IDD = IDD_LLK_DIALOG };
	CButton	m_ctl_checkspeed;
	CSliderCtrl	m_ctl_speed;
	int		m_SeatNum;
	CString	m_chess_data;
	CString	m_news;
	BOOL	m_autostart;
	BOOL	m_autoplay;
	int		m_speed;
	BOOL	m_checkspeed;
	BOOL	m_cleartime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLlkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLlkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void onStartGame();
	afx_msg void onGetSeat();
	afx_msg void OnGetseatNum();
	afx_msg void OnGetSeatNum();
	afx_msg void OnGetChess();
	afx_msg void OnClickOne();
	afx_msg void OnClearAll();
	afx_msg void OnAutoStart();
	afx_msg void OnAutoPlay();
	afx_msg void OnMedifySpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckSpeed();
	afx_msg void OnClearTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKDLG_H__4AA58293_6D9F_492E_8578_83A0B717F6C5__INCLUDED_)
