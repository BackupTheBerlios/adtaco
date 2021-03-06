// $Id: ProcessesView.cpp,v 1.2 2008/04/26 22:08:25 gerrit-albrecht Exp $
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
#include "ProcessesView.h"

IMPLEMENT_DYNCREATE(CProcessesView, MTreeListView)

BEGIN_MESSAGE_MAP(CProcessesView, MTreeListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

CProcessesView::CProcessesView()
{
#ifndef _WIN32_WCE
  EnableActiveAccessibility();
#endif
}

CProcessesView::~CProcessesView()
{
}

#ifdef _DEBUG
void CProcessesView::AssertValid() const
{
  MTreeListView::AssertValid();
}

#ifndef _WIN32_WCE
void CProcessesView::Dump(CDumpContext& dc) const
{
  MTreeListView::Dump(dc);
}
#endif
#endif

int CProcessesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (MTreeListView::OnCreate(lpCreateStruct) == -1)
    return -1;

#if 0
  CTreeCtrl &tree = this->GetTreeCtrl();

  tree.ModifyStyleEx(0, TVS_HASBUTTONS | TVS_FULLROWSELECT | /*TVS_HASLINES |*/ TVS_DISABLEDRAGDROP);
  tree.ModifyStyle(WS_BORDER, WS_TABSTOP);

  HTREEITEM item = tree.InsertItem(_T("Test"));
  item = tree.InsertItem(_T("Test 2"), item);
  item = tree.InsertItem(_T("Test 3"), item);

  item = tree.InsertItem(_T("Test"));

  //tree.Expand(..)
  tree.Invalidate();
#endif

  return 0;
}
