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
char* tempcodes=(char*)malloc(sizeof(char)*10); //暂存剪贴板文本信息的变量
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
	
	//初始化下拉框
	m_type_select.AddString("C");
	m_type_select.AddString("C++");
	m_type_select.AddString("JAVA");
	m_type_select.AddString("PHP");
	m_type_select.SetCurSel(0);
	m_codes="在这里粘贴您的代码...";
	m_info="在这里添加代码的描述信息...";
	m_Status="正在连接服务器...";
	m_pass_title="您也可以加密分享";
	UpdateData(FALSE);
	if(!TestNetLink())
	{	//如果服务器未连接通

		m_Status="连接服务器失败！";
	}
	else
		m_Status="成功连接服务器...";
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
		m_Status="服务器无响应...";
		UpdateData(FALSE);
		int	select=MessageBox("服务器当前无响应!\n  请检查网络连接或者与我们联系。\n您是否愿意反馈信息给我们？","操作提示",MB_YESNO+MB_ICONINFORMATION);
		if(select==IDYES)
			ShellExecute(NULL,"open","http://mail.qq.com/cgi-bin/qm_share?t=qm_mailme&email=HyomKicvLSYuX25uMXxwcg",NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		if(m_username=="")
			MessageBox("用户名不能为空","操作提示",MB_OK+MB_ICONINFORMATION);
		else if((strcmp(radio,"private")==0)&&(m_password=="")) //如果代码为私有类型但密码为空
		{
			MessageBox("对于私密分享请输入代码查看密码!","操作提示",MB_OK+MB_ICONINFORMATION);
		}
		else if(m_codes=="")
		{
			MessageBox("请录入需要发布的代码","操作提示",MB_OK+MB_ICONINFORMATION);
		}
		else if(m_info=="")
		{
			int select= MessageBox("您没有输入关于这段代码的备注。\n  是否继续提交操作？","操作提示",MB_YESNO+MB_ICONQUESTION);
			if(select==IDYES)
			{
				//调用发送报文的函数
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
			m_Status="后台正在处理信息...";
			UpdateData(FALSE);
			putcodes(m_username.GetBuffer(m_username.GetLength()),radio,m_password.GetBuffer(m_password.GetLength()),m_info.GetBuffer(m_info.GetLength()),language,m_codes.GetBuffer(m_codes.GetLength()));
			m_Status="后台数据处理完毕!";
			UpdateData(FALSE);
		}
	}
}

void CCodesPasteDlg::OnSTATIChelp_click() 
{
	// TODO: Add your control notification handler code here
	char* info="尊敬的用户:\n  您在分享代码时请注意以下几点。\n    1.代码只会暂存5个月;\n    2.我们不承担一切责任;\n    3.最终解释权归开发者。";
	MessageBox(info,"使用须知",MB_OK+MB_ICONINFORMATION);
}

void CCodesPasteDlg::OnPrivate_click() 
{
	// TODO: Add your control notification handler code here
	m_password_ctl.EnableWindow(TRUE);
	GetDlgItem(pass_title)->SetWindowText("请输入分享密码:");
	UpdateData(true);
	strcpy(radio,"private");
	UpdateData(false);
}

void CCodesPasteDlg::OnPublic_click() 
{
	// TODO: Add your control notification handler code here
	m_password_ctl.EnableWindow(FALSE);
	m_pass_title="您也可以加密分享";
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
	if(m_info=="在这里添加代码的描述信息...")
	{
		m_info="";
		UpdateData(FALSE);
	}
	if(m_info==""&&m_codes!="在这里粘贴您的代码...")
	{
		m_Status="请输入有关于这段代码的描述!";
		UpdateData(FALSE);
	}
}

void CCodesPasteDlg::OnSetfocusCodes() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_codes=="在这里粘贴您的代码...")
	{
		m_codes="";
		UpdateData(FALSE);
	}
	if(m_codes=="")
	{
		m_Status="请录入需要分享的代码!";
		UpdateData(FALSE);
	}
}

void CCodesPasteDlg::OnKillfocusCodes() //失去焦点时激发获取剪贴板信息的功能
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//更新控件变量的内容
	//获取剪贴板内容
	HANDLE info=GetClipData(CF_TEXT); //获取文本类型
	if(info)
	{
		char* WordsOfClip=(char*)GlobalLock(info);//获取剪贴板信息
		if(strlen(WordsOfClip)>60)
			if(strcmp(WordsOfClip,tempcodes)!=0) //如果剪贴板代码与tempcodes不同
			{
				int select=MessageBox("检测到系统剪贴板中有新内容！\n您是否需要自动更新代码?","操作提示",MB_YESNO+MB_ICONQUESTION);
				tempcodes=(char*)realloc(tempcodes,strlen(WordsOfClip)+5);//对于tempcodes的内存空间进行重新分配
				if(select==IDYES)//如果选择了yes
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
			GlobalUnlock(info); //对剪贴板进行解锁
		}	
}

void CCodesPasteDlg::OnSetfocusName() 
{
	// TODO: Add your control notification handler code here
}
