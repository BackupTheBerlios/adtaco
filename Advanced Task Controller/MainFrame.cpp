// $Id: MainFrame.cpp,v 1.3 2008/04/26 22:08:25 gerrit-albrecht Exp $
//
// Advanced Task Controller
// Copyright (C) 2006 by Gerrit M. Albrecht
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#include "StdAfx.h"
#include "AdvancedTaskController.h"
#include "MainFrame.h"
#include "InfoView.h"
#include "ProcessesView.h"

#include <Miraledon/ProcessInformation.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	// Globale Hilfebefehle
	ON_COMMAND(ID_HELP_FINDER, &CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, &CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, &CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, &CFrameWnd::OnHelpFinder)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_OPTIONS, &CMainFrame::OnViewOptions)
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

static UINT indicators[] =
{
  ID_SEPARATOR,           // Statusleistenanzeige
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};

// CMainFrame-Erstellung/Zerstörung

CMainFrame::CMainFrame()
{
  EnableActiveAccessibility();

  m_splitter_created = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  // Ansicht erstellen, um den Clientbereich des Rahmens zu belegen
//	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
//		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) {
//		TRACE0("Fehler beim Erstellen des Ansichtsfensters.\n");
//		return -1;
//	}
	
  if (! m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP |
                              CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
      ! m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
    TRACE0("Fehler beim Erstellen der Symbolleiste.\n");
    return -1;                                             // Fehler beim Erstellen.
  }

  if (! m_wndStatusBar.Create(this) ||
      ! m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
    TRACE0("Fehler beim Erstellen der Statusleiste.\n");
    return -1;                                             // Fehler beim Erstellen.
  }

  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);              // Die Systemleiste ist andockbar.
  EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar);

  SetIcon(theApp.LoadIcon(IDR_MAINFRAME), TRUE);           // Set big icon.
  SetIcon(theApp.LoadIcon(IDR_MAINFRAME), FALSE);          // Set small icon.

  return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  if (! CFrameWnd::PreCreateWindow(cs))
    return FALSE;

  LPWINDOWPLACEMENT lpwp;
  UINT dwSize;

  if (theApp.GetProfileBinary(TEXT("WindowPlacement"), TEXT("MainFrame"), (LPBYTE *) &lpwp, &dwSize)) {
    cs.x = lpwp->rcNormalPosition.left;
    cs.y = lpwp->rcNormalPosition.top;
    cs.cx = lpwp->rcNormalPosition.right  - lpwp->rcNormalPosition.left;
    cs.cy = lpwp->rcNormalPosition.bottom - lpwp->rcNormalPosition.top;

    // The following correction is needed when the taskbar is
    // at the left or top and it is not "auto-hidden".

	RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    int l = cs.x + workArea.left;
    int t = cs.y + workArea.top;

    // Make sure the window is not completely out of sight.

	int max_x = GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXICON);
	int max_y = GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYICON);

	cs.x = min(l, max_x);
    cs.y = min(t, max_y);

	delete [] lpwp;
  }

  cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
  cs.lpszClass = AfxRegisterWndClass(0);

  return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
  CFrameWnd::Dump(dc);
}
#endif

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
  //m_wndView.SetFocus();   // Fokus an das Ansichtsfenster weitergeben.
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// Ansichtsfenster erhält ersten Eindruck vom Befehl
//	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
//		return TRUE;

  // Andernfalls die Standardbehandlung durchführen.
  return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnClose()
{
  WINDOWPLACEMENT wp;
  int t, b, x;

  ZeroMemory(&wp, sizeof(wp));
  wp.length = sizeof(wp);

  if (GetWindowPlacement(&wp)) {
    if (IsIconic())                                // Never restore to iconic state.
      wp.showCmd = SW_SHOW;

    if ((wp.flags & WPF_RESTORETOMAXIMIZED) != 0)  // If max and maybe iconic.
      wp.showCmd = SW_SHOWMAXIMIZED;               // Restore maximized state.

    theApp.WriteProfileBinary(_T("WindowPlacement"), _T("MainFrame"), (LPBYTE) &wp, sizeof(wp));

    m_splitter.GetRowInfo(0, t, x);
    m_splitter.GetRowInfo(1, b, x);
	theApp.WriteProfileInt(_T("Positions"), _T("SplitterHeightRowTop"),    t);
	theApp.WriteProfileInt(_T("Positions"), _T("SplitterHeightRowBottom"), b);

    SaveBarState(_T("Settings"));
  }

  CFrameWnd::OnClose();
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
  m_splitter_created = m_splitter.CreateStatic(this, 2, 1);
  if (! m_splitter_created) {
    theApp.ShowErrorMessage(IDS_ERROR_NO_SPLITTER);
    return FALSE;
  }

  m_splitter.CreateView(0, 0, RUNTIME_CLASS(CProcessesView), CSize(0, 0), pContext);
  m_splitter.CreateView(1, 0, RUNTIME_CLASS(CInfoView),      CSize(0, 0), pContext);

  // If there is a stored splitter position, use it.

  UINT t, b;
  t = theApp.GetProfileInt(_T("Positions"), _T("SplitterHeightRowTop"),    0);
  b = theApp.GetProfileInt(_T("Positions"), _T("SplitterHeightRowBottom"), 0);
  TRACE("Loaded Splitter Positions: Top %d Bottom %d\n", t, b);

  if (t && b) {
    m_splitter.SetRowInfo(0, t, 0);
    m_splitter.SetRowInfo(1, b, 0);
  } else {
    CRect rect;
    GetWindowRect(&rect);

    m_splitter.SetRowInfo(0, rect.Height()/2, 0);
    m_splitter.SetRowInfo(1, rect.Height()/2, 0);
  }
  m_splitter.RecalcLayout();

  return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
  CFrameWnd::OnSize(nType, cx, cy);

  CRect rect;
  GetWindowRect(&rect);

  // Calculate a percent value for the splitter and set
  // it's panes height according to it.

  if (m_splitter_created) {                                // Set in OnCreateClient().
    int curT, curB, minT, minB;

    m_splitter.GetRowInfo(0, curT, minT);
    m_splitter.GetRowInfo(1, curB, minB);

	//m_splitter.SetRowInfo(0, rect.Height()/2, 10);
    //m_splitter.SetRowInfo(1, rect.Height()/2, 10);
    m_splitter.RecalcLayout();
 }
}

BOOL CALLBACK MyProcessEnumerator(DWORD dwPID, WORD wTask, LPCTSTR szProcess, LPARAM lParam)
{
  if (wTask == 0)
    TRACE(_T("%5u   %s\n"), dwPID, szProcess);
  else
    TRACE(_T("  %5u %s\n"), wTask, szProcess);

  return TRUE;
}

void CMainFrame::OnViewOptions()
{
  MProcessInformation pi;

  pi.EnumProcs32((PROCENUMPROC) MyProcessEnumerator, (LPARAM) this);
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
  UNUSED_ALWAYS(pDC);

  return TRUE; //CFrameWnd::OnEraseBkgnd(pDC);
}
