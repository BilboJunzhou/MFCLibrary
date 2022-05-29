
// MFCLibraryDlg.h: 头文件
//

#pragma once
#include "TabSheet.h"
#include "CDialog1.h"
#include "CDialog2.h"
#include "CDialog3.h"
#include "CDialog4.h"

// CMFCLibraryDlg 对话框
class CMFCLibraryDlg : public CDialogEx
{
// 构造
public:
	CMFCLibraryDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLIBRARY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabSheet m_tab;
	CDialog1 dlg1;
	CDialog2 dlg2;
	CDialog3 dlg3;
	CDialog4 dlg4;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
