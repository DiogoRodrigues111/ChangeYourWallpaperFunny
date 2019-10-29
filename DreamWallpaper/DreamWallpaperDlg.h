
// DreamWallpaperDlg.h: arquivo de cabeçalho
//

#pragma once


// caixa de diálogo CDreamWallpaperDlg
class CDreamWallpaperDlg : public CDialogEx
{
// Construção
public:
	CDreamWallpaperDlg(CWnd* pParent = nullptr);	// construtor padrão

// Janela de Dados
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DREAMWALLPAPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Suporte DDX/DDV


// Implementação
protected:
	HICON m_hIcon;

	// Funções geradas de mapa de mensagens
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_OpenFileSystem;
	afx_msg void OnBnClickedButton1();	
	INT SetBackground(LPCWSTR string);
	CString GetBackground();
	BOOL SetOptions();
	HRESULT IdwGetOptions();
	HRESULT hr;
};
