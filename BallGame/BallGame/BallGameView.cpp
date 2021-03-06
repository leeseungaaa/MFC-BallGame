
// BallGameView.cpp: CBallGameView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BallGame.h"
#endif

#include "BallGameDoc.h"
#include "BallGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBallGameView

IMPLEMENT_DYNCREATE(CBallGameView, CView)

BEGIN_MESSAGE_MAP(CBallGameView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_COMMAND(ID_BALLGAME_START, &CBallGameView::OnBallgameStart)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CBallGameView 생성/소멸

CBallGameView::CBallGameView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	m_ptCircle = CPoint(100, 100);// 원 시작좌표 (시작위치)
	m_Board = CPoint(300, 500);

	m_xStep = 10; // 공이 얼만큼씩 움직이는지 설정해놓음. 높아질수록 빠른 것.
	m_yStep = 10;
}

CBallGameView::~CBallGameView()
{
}

BOOL CBallGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBallGameView 그리기

void CBallGameView::OnDraw(CDC* pDC)
{
	CBallGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	pDC->Ellipse(m_ptCircle.x - 30, m_ptCircle.y - 30,
		m_ptCircle.x + 30, m_ptCircle.y + 30);  // 공크기

	pDC->Rectangle(m_Board.x - 50, m_Board.y - 1,
		m_Board.x + 50, m_Board.y + 1
	);

}


// CBallGameView 인쇄

BOOL CBallGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBallGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBallGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBallGameView 진단

#ifdef _DEBUG
void CBallGameView::AssertValid() const
{
	CView::AssertValid();
}

void CBallGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBallGameDoc* CBallGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBallGameDoc)));
	return (CBallGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CBallGameView 메시지 처리기


//void CBallGameView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	//타이머를 작동시킴 마우스좌표와 원의 중심 좌표를 가지고 타이머 신호에 따라
//	// 이동할 단위 거리를 구함.
//
//	
//
//
//	CView::OnLButtonDown(nFlags, point);
//}


void CBallGameView::OnTimer(UINT_PTR nIDEvent) // 경계만나면 튕겨나가기
{ // 경계 + 보드
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	
	current_time = GetTickCount();

	m_ptCircle.x += m_xStep;
	m_ptCircle.y += m_yStep;

	if (m_ptCircle.x - 30 < 0 || m_ptCircle.x + 30 > m_WinRight) {
		m_ptCircle.x -= m_xStep;
		m_xStep *= -1;
	}
	

	if ((m_ptCircle.y + 30 )== (m_Board.y-1)) { // 보드에 닿으면 튕겨지기
		if (m_Board.x - 50 <= m_ptCircle.x && m_ptCircle.x <= m_Board.x + 50) {
			m_ptCircle.y -= m_yStep;
			m_yStep *= -1;
		}
	}

	if (m_ptCircle.y - 30 < 0) {
		m_ptCircle.y -= m_yStep;
		m_yStep *= -1;
	}


	if ( m_ptCircle.y + 30 > m_WinBottom) {
		//게임 종료
		time_result = current_time - start_time;
		KillTimer(1);
		AfxMessageBox(_T("게임 실패"));
	
	}

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CBallGameView::OnSize(UINT nType, int cx, int cy)
{ // 경계 영역 설정
	CView::OnSize(nType, cx, cy);

	m_WinRight = cx;
	m_WinBottom = cy;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CBallGameView::OnBallgameStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 게임시작 눌러야 시작.
	m_ptCircle = CPoint(100, 100);
	start_time = GetTickCount();
	SetTimer(1, 100, NULL);
}



void CBallGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nChar) // 보드 좌우로 움직이기.
	{
	case VK_RIGHT:
		m_Board.x += 10;
		break;

	case VK_LEFT:
		m_Board.x -= 10;
		break;
	}


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
