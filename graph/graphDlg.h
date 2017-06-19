
// graphDlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include <list>
#include "afxwin.h"
class node
{
public:
	CPoint o;
	double r;
	int v;
	int dir;
};

// CgraphDlg �Ի���
class CgraphDlg : public CDialogEx
{
// ����
public:
	CgraphDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;


	// my variables
	COLORREF background = RGB(255, 255, 255);
	COLORREF red = RGB(255, 0, 0);
	COLORREF black = RGB(0, 0, 0);
	COLORREF white = RGB(255, 255, 255);
	const int down = 100;
	const int side = 20;
	const int flush = 50;
	const int create = 200;
	int score = 0;
	// end variables

	// my function
	void printBox();
	void clearBox();
	std::list<node> point1;
	std::list<node> point3;
	// end function


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
