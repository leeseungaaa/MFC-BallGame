
// BallGameView.h: CBallGameView 클래스의 인터페이스
//

#pragma once


class CBallGameView : public CView
{
protected: // serialization에서만 만들어집니다.
	CBallGameView();
	DECLARE_DYNCREATE(CBallGameView)

// 특성입니다.
public:
	CBallGameDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CBallGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	int m_Count;
	CPoint m_ptCircle;
	int m_xStep; // 공이 움직이는 속도
	int m_yStep;
	int m_WinRight; // 뷰영역 오른쪽 경계
	int m_WinBottom; //뷰영역 아래쪽 경계
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnBallgameStart();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CPoint m_Board;
	int m_boardStep;
	int m_Where;
	int start_time;
	int current_time;
	int time_result;
};

#ifndef _DEBUG  // BallGameView.cpp의 디버그 버전
inline CBallGameDoc* CBallGameView::GetDocument() const
   { return reinterpret_cast<CBallGameDoc*>(m_pDocument); }
#endif

