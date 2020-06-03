
// ThreadsSynchroDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ThreadsSynchro.h"
#include "ThreadsSynchroDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CThreadsSynchroDlg dialog



CThreadsSynchroDlg::CThreadsSynchroDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREADSSYNCHRO_DIALOG, pParent)
	, text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadsSynchroDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TEXT, textControl);
	DDX_Text(pDX, IDC_TEXT, text);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadsSynchroDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_TEXT, &CThreadsSynchroDlg::OnEnChangeText)
END_MESSAGE_MAP()


// CThreadsSynchroDlg message handlers

BOOL CThreadsSynchroDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: Add extra initialization here
	event[0] = CreateEvent(NULL, TRUE, TRUE, L"FirstStep");
	event[1] = CreateEvent(NULL, FALSE, FALSE, L"box");


	if (WaitForSingleObject(event[0], 0) == WAIT_OBJECT_0)
	{
		ResetEvent(event[0]);
		SetWindowText(_T("���������"));
		SetDlgItemTextW(IDC_NUMER, _T("���������"));
		active = true;
		
	}
	else
	{
		GetDlgItem(IDC_TEXT)->EnableWindow(0);
		SetWindowText(_T("��������"));
		SetDlgItemTextW(IDC_NUMER, _T("���������"));
		active = false;
		hThread = CreateThread(NULL, 0, thread, this, 0, &dwThread);
	}
	UpdateData(false);
	hObject = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 2048, TEXT("File_mapping"));
	if (hObject != NULL)
	{
		lp_BaseAddress = MapViewOfFile(hObject, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	}	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreadsSynchroDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CThreadsSynchroDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CThreadsSynchroDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThreadsSynchroDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (active)
		SetEvent(event[0]);
	else
	{
		TerminateThread(hThread, 0);
		CloseHandle(hThread);
	}
	UnmapViewOfFile(lp_BaseAddress);		// ���������� �� �������� �������� ������� ��������� �����������
	CloseHandle(hObject);
	CDialogEx::OnClose();
}


void CThreadsSynchroDlg::OnEnChangeText()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if (active)
		if (lp_BaseAddress != NULL)
			GetDlgItem(IDC_TEXT)->GetWindowText((PTSTR)lp_BaseAddress, 2048);
	PulseEvent(event[1]);

}
