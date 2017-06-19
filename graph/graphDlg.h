
// graphDlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include <list>
#include "afxwin.h"
class node		// circle
{
public:
	CPoint o;	// circle o
	double r;	// radio
	int v;		// move up  speed
	int dir;	// move left or right or not, -1/0/1 is left/not/right    
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
	COLORREF background = RGB(255, 255, 255);		// init background color
	COLORREF red = RGB(255, 0, 0);
	COLORREF black = RGB(0, 0, 0);
	COLORREF white = RGB(255, 255, 255);
	const int down = 100;							// distance to the bottom
	const int side = 20;							// distance to left, top, right
	const int flush = 50;							// move up per flush ms
	const int create = 200;							// create a bubble per create ms

	std::list<node> point1;							// circle, score 1
	std::list<node> point3;							// circle, score 3

	int score = 0;
	// end variables

	// my function
	void printBox();								// print the game area box
	void clearBox();								// clear the area

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
