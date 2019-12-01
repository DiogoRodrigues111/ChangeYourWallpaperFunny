
// DreamWallpaperDlg.cpp: arquivo de implementação
//

#include "pch.h"
#include "framework.h"
#include "DreamWallpaper.h"
#include "DreamWallpaperDlg.h"
#include "afxdialogex.h"

#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Caixa de diálogo CAboutDlg usada para o Sobre o Aplicativo

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Janela de Dados
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Suporte DDX/DDV

// Implementação
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


// caixa de diálogo CDreamWallpaperDlg



CDreamWallpaperDlg::CDreamWallpaperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DREAMWALLPAPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDreamWallpaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_OpenFileSystem);
}

BEGIN_MESSAGE_MAP(CDreamWallpaperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDreamWallpaperDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Manipuladores de mensagens de CDreamWallpaperDlg

BOOL CDreamWallpaperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Adicione o item de menu "Sobre..." ao menu do sistema.

	// IDM_ABOUTBOX deve estar no intervalo de comandos do sistema.
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

	// Defina o ícone para esta caixa de diálogo. A estrutura faz isso automaticamente
	//  quando a janela principal do aplicativo não é uma caixa de diálogo
	SetIcon(m_hIcon, TRUE);			// Definir ícone grande
	SetIcon(m_hIcon, FALSE);		// Definir ícone pequeno

	// TODO: adicione a inicialização extra aqui

	return TRUE;  // retorna TRUE a não ser que você ajuste o foco para um controle
}

void CDreamWallpaperDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Se você adicionar um botão para minimizar à sua caixa de diálogo, será necessário o código abaixo
//  para desenhar o ícone. Para aplicativos MFC usando o modelo de exibição/documento,
//  isso é feito automaticamente para você pela estrutura.

void CDreamWallpaperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexto do dispositivo para pintura

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ícone central no retângulo do cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Desenhar o ícone
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// O sistema chama esta função para obter o cursor a ser exibido enquanto o usuário arrasta
//  a janela minimizada.
HCURSOR CDreamWallpaperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
extern UINT SystemParametersInfo(UINT uiAction, UINT uiParam, LPCWSTR Msg, UINT fWinIni) throw()
{
	CRegKey rKey;
	LPCWSTR GetCurrentFileNameW = _T("");

	rKey.Open(HKEY_LOCAL_MACHINE, _T("Control Panel\\Desktop"));
	rKey.SetValue(HKEY_LOCAL_MACHINE, _T("Control Panel\\Desktop"), GetCurrentFileNameW);
	rKey.Close();

	return 0;
}

INT CDreamWallpaperDlg::SetBackground(LPCWSTR string)
{
	INT s = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, string, 0x02);
	return s;
}

CString CDreamWallpaperDlg::GetBackground()
{
	LPCWSTR string = _T("");
	SystemParametersInfo(SPI_GETDESKWALLPAPER, 300, string, 0);
	return string;
}
*/

BOOL CDreamWallpaperDlg::SetOptions()
{
	return TRUE;
}

HRESULT CDreamWallpaperDlg::IdwGetOptions()
{
	return hr;
}

void CDreamWallpaperDlg::OnBnClickedButton1()
{
	CFileDialog m_FileSystem(TRUE, _T("*.jpg"));
	INT_PTR hResult = m_FileSystem.DoModal();
	PWSTR GetFileNameA;
	TCHAR szFile[260];
	IShellItem* psi = NULL;
	IDesktopWallpaper* pIdw = nullptr;

	hr = CoInitialize(NULL);
	hr = CoCreateInstance(__uuidof(DesktopWallpaper), NULL, CLSCTX_ALL, IID_PPV_ARGS(&pIdw));
	
	psi = m_FileSystem.GetResult();

	hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &GetFileNameA);

	m_FileSystem.m_ofn.lStructSize = sizeof(m_FileSystem);
	m_FileSystem.m_ofn.lpstrFile = szFile;
	m_FileSystem.m_ofn.lpstrFile[0] = '\0';
	m_FileSystem.m_ofn.lpstrFileTitle = 0;
	m_FileSystem.m_ofn.lpstrFilter = _T("Image\0*.jpg\0");
	m_FileSystem.m_ofn.lpstrInitialDir = NULL;
	m_FileSystem.m_ofn.nFilterIndex = 1;

	if (FAILED(hr)) {
		MessageBox(_T("ERR: hr initialized On Button"), _T("WAR: hr"), MB_ICONWARNING | MB_OK);
		return;
	}

	if (SUCCEEDED(hr)) {
		if (hResult == IDOK) {
			pIdw->SetWallpaper(0, GetFileNameA);
		}

		psi->Release();
	}
}
