// $Id: InfoView.cpp,v 1.1 2006/01/20 15:17:00 gerrit-albrecht Exp $
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
//
// This class implements the view area below the splitter bar.
// It manages the tab bar buttons and shows/hides other views.
// It's a kind of a tab view class.

#include "StdAfx.h"
#include "InfoView.h"

IMPLEMENT_DYNCREATE(CInfoView, CView)

BEGIN_MESSAGE_MAP(CInfoView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CInfoView::CInfoView()
{
#ifndef _WIN32_WCE
  EnableActiveAccessibility();
#endif
}

CInfoView::~CInfoView()
{
}

// CInfoView drawing

void CInfoView::OnDraw(CDC* pDC)
{
  CDocument* pDoc = GetDocument();

  // TODO: add draw code here
}


// CInfoView diagnostics

#ifdef _DEBUG
void CInfoView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif

int CInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;

  m_tabs.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0);
  m_tabs.InsertItem(0, _T("Threads"));
  m_tabs.InsertItem(1, _T("Heaps"));
  m_tabs.InsertItem(2, _T("Files"));
  m_tabs.InsertItem(3, _T("DLLs"));
  m_tabs.SetCurSel(0);

  return 0;
}

void CInfoView::AddTab(int pos, LPWSTR name)
{
  TCITEM tci;

  tci.mask = TCIF_TEXT;
  tci.pszText = name;

  m_tabs.InsertItem(pos, &tci);
}

void CInfoView::OnSize(UINT nType, int cx, int cy)
{
  CView::OnSize(nType, cx, cy);

  m_tabs.MoveWindow(1, 1, cx, cy);
}

BOOL CInfoView::OnEraseBkgnd(CDC* pDC)
{
  UNUSED_ALWAYS(pDC);

  return CView::OnEraseBkgnd(pDC);  // Sonst hab' ich einen Pixel Müll drin. Warum?
}
