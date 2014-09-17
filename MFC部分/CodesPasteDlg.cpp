// CodesPasteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CodesPaste.h"
#include "CodesPasteDlg.h"
#include "func.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char radio[100]="public";
char language[100]="";
int selectid=0;
char* tempcodes=(char*)malloc(sizeof(char)*10); //�ݴ�������ı���Ϣ�ı���
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
// CCodesPasteDlg dialog

CCodesPasteDlg::CCodesPasteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCodesPasteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodesPasteDlg)
	m_username = _T("");
	m_password = _T("");
	m_codes = _T("");
	m_info = _T("");
	m_Status = _T("");
	m_pass_title = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodesPasteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodesPasteDlg)
	DDX_Control(pDX, SELECT_CODE_TYPE, m_type_select);
	DDX_Control(pDX, EDIT_PASSWORD, m_password_ctl);
	DDX_Text(pDX, EDIT_NAME, m_username);
	DDX_Text(pDX, EDIT_PASSWORD, m_password);
	DDX_Text(pDX, EDIT_CODES, m_codes);
	DDX_Text(pDX, EDIT_INFO, m_info);
	DDX_Text(pDX, STATIC_STATUS, m_Status);
	DDX_Text(pDX, pass_title, m_pass_title);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCodesPasteDlg, CDialog)
	//{{AFX_MSG_MAP(CCodesPasteDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_PASTE, OnPaste_click)
	ON_BN_CLICKED(IDC_STATIC_help, OnSTATIChelp_click)
	ON_BN_CLICKED(SELECT_PRIVATE, OnPrivate_click)
	ON_BN_CLICKED(SELECT_PUBLIC, OnPublic_click)
	ON_CBN_EDITCHANGE(SELECT_CODE_TYPE, CodeType_OnChange)
	ON_EN_SETFOCUS(EDIT_INFO, OnSetfocusInfo)
	ON_EN_SETFOCUS(EDIT_CODES, OnSetfocusCodes)
	ON_EN_KILLFOCUS(EDIT_CODES, OnKillfocusCodes)
	ON_EN_SETFOCUS(EDIT_NAME, OnSetfocusName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodesPasteDlg message handlers

BOOL CCodesPasteDlg::OnInitDialog()
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
	// TODO: Add extra initialization here

	CheckRadioButton(SELECT_PUBLIC,SELECT_PRIVATE,SELECT_PUBLIC);
	
	//��ʼ��������
	m_type_select.AddString("C");
	m_type_select.AddString("C++");
	m_type_select.AddString("JAVA");
	m_type_select.AddString("PHP");
	m_type_select.SetCurSel(0);
	m_codes="������ճ�����Ĵ���...";
	m_info="��������Ӵ����������Ϣ...";
	m_Status="�������ӷ�����...";
	m_pass_title="��Ҳ���Լ��ܷ���";
	UpdateData(FALSE);
	if(!TestNetLink())
	{	//���������δ����ͨ

		m_Status="���ӷ�����ʧ�ܣ�";
	}
	else
		m_Status="�ɹ����ӷ�����...";
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCodesPasteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCodesPasteDlg::OnPaint() 
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
HCURSOR CCodesPasteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CCodesPasteDlg::OnPaste_click() 
{
	UpdateData(true);
	// TODO: Add your control notification handler code here
	if(!TestNetLink()){
		m_Status="����������Ӧ...";
		UpdateData(FALSE);
		int	select=MessageBox("��������ǰ����Ӧ!\n  �����������ӻ�����������ϵ��\n���Ƿ�Ը�ⷴ����Ϣ�����ǣ�","������ʾ",MB_YESNO+MB_ICONINFORMATION);
		if(select==IDYES)
			ShellExecute(NULL,"open","http://mail.qq.com/cgi-bin/qm_share?t=qm_mailme&email=HyomKicvLSYuX25uMXxwcg",NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		if(m_username=="")
			MessageBox("�û�������Ϊ��","������ʾ",MB_OK+MB_ICONINFORMATION);
		else if((strcmp(radio,"private")==0)&&(m_password=="")) //�������Ϊ˽�����͵�����Ϊ��
		{
			MessageBox("����˽�ܷ������������鿴����!","������ʾ",MB_OK+MB_ICONINFORMATION);
		}
		else if(m_codes=="")
		{
			MessageBox("��¼����Ҫ�����Ĵ���","������ʾ",MB_OK+MB_ICONINFORMATION);
		}
		else if(m_info=="")
		{
			int select= MessageBox("��û�����������δ���ı�ע��\n  �Ƿ�����ύ������","������ʾ",MB_YESNO+MB_ICONQUESTION);
			if(select==IDYES)
			{
				//���÷��ͱ��ĵĺ���
				selectid=m_type_select.GetCurSel();
				m_type_select.GetLBText(selectid,language);
				putcodes(m_username.GetBuffer(m_username.GetLength()),radio,m_password.GetBuffer(m_password.GetLength()),m_info.GetBuffer(m_info.GetLength()),language,m_codes.GetBuffer(m_codes.GetLength()));
				if(m_info=="No More Information About This Codes")
					m_info="";
			}
		}
		else{
			selectid=m_type_select.GetCurSel();
			m_type_select.GetLBText(selectid,language);
			m_Status="��̨���ڴ�����Ϣ...";
			UpdateData(FALSE);
			putcodes(m_username.GetBuffer(m_username.GetLength()),radio,m_password.GetBuffer(m_password.GetLength()),m_info.GetBuffer(m_info.GetLength()),language,m_codes.GetBuffer(m_codes.GetLength()));
			m_Status="��̨���ݴ������!";
			UpdateData(FALSE);
		}
	}
}

void CCodesPasteDlg::OnSTATIChelp_click() 
{
	// TODO: Add your control notification handler code here
	char* info="�𾴵��û�:\n  ���ڷ������ʱ��ע�����¼��㡣\n    1.����ֻ���ݴ�5����;\n    2.���ǲ��е�һ������;\n    3.���ս���Ȩ�鿪���ߡ�";
	MessageBox(info,"ʹ����֪",MB_OK+MB_ICONINFORMATION);
}

void CCodesPasteDlg::OnPrivate_click() 
{
	// TODO: Add your control notification handler code here
	m_password_ctl.EnableWindow(TRUE);
	GetDlgItem(pass_title)->SetWindowText("�������������:");
	UpdateData(true);
	strcpy(radio,"private");
	UpdateData(false);
}

void CCodesPasteDlg::OnPublic_click() 
{
	// TODO: Add your control notification handler code here
	m_password_ctl.EnableWindow(FALSE);
	m_pass_title="��Ҳ���Լ��ܷ���";
	strcpy(radio,"public");
	UpdateData(false);
}

void CCodesPasteDlg::CodeType_OnChange() 
{
	// TODO: Add your control notification handler code here

}

void CCodesPasteDlg::OnSetfocusInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_info=="��������Ӵ����������Ϣ...")
	{
		m_info="";
		UpdateData(FALSE);
	}
	if(m_info==""&&m_codes!="������ճ�����Ĵ���...")
	{
		m_Status="�������й�����δ��������!";
		UpdateData(FALSE);
	}
}

void CCodesPasteDlg::OnSetfocusCodes() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_codes=="������ճ�����Ĵ���...")
	{
		m_codes="";
		UpdateData(FALSE);
	}
	if(m_codes=="")
	{
		m_Status="��¼����Ҫ����Ĵ���!";
		UpdateData(FALSE);
	}
}

void CCodesPasteDlg::OnKillfocusCodes() //ʧȥ����ʱ������ȡ��������Ϣ�Ĺ���
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//���¿ؼ�����������
	//��ȡ����������
	HANDLE info=GetClipData(CF_TEXT); //��ȡ�ı�����
	if(info)
	{
		char* WordsOfClip=(char*)GlobalLock(info);//��ȡ��������Ϣ
		if(strlen(WordsOfClip)>60)
			if(strcmp(WordsOfClip,tempcodes)!=0) //��������������tempcodes��ͬ
			{
				int select=MessageBox("��⵽ϵͳ���������������ݣ�\n���Ƿ���Ҫ�Զ����´���?","������ʾ",MB_YESNO+MB_ICONQUESTION);
				tempcodes=(char*)realloc(tempcodes,strlen(WordsOfClip)+5);//����tempcodes���ڴ�ռ�������·���
				if(select==IDYES)//���ѡ����yes
				{
					strcpy(tempcodes,WordsOfClip);
					m_codes=tempcodes;
					UpdateData(FALSE);
				}
				else
				{
					strcpy(tempcodes,WordsOfClip);
				}
			}
			GlobalUnlock(info); //�Լ�������н���
		}	
}

void CCodesPasteDlg::OnSetfocusName() 
{
	// TODO: Add your control notification handler code here
}
