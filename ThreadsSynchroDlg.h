
// ThreadsSynchroDlg.h : header file
//

#pragma once


// CThreadsSynchroDlg dialog
class CThreadsSynchroDlg : public CDialogEx
{
// Construction
public:
	CThreadsSynchroDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREADSSYNCHRO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HANDLE hThread;
	DWORD dwThread;
	friend DWORD WINAPI thread(PVOID t);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit textControl;
	CString text;
	bool active;
	HANDLE event[2];
	HANDLE  hObject;
	PVOID lp_BaseAddress;

	void Write_mess();
	void Read_mess();
	afx_msg void OnEnChangetext();
	afx_msg void OnClose();
	afx_msg void OnEnChangeText();
};
