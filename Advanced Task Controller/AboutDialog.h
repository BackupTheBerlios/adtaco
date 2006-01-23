// $Id: AboutDialog.h,v 1.2 2006/01/23 12:58:27 gerrit-albrecht Exp $
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

#pragma once

#ifndef __AFXWIN_H__
	#error "\"StdAfx.h\" vor dieser Datei für PCH einschließen"
#endif

#include "Resource.h"                                      // Hauptsymbole.

class CAboutDialog : public CDialog
{
  public:
    CAboutDialog();

    enum { IDD = IDD_ABOUT };                              // Dialogfelddaten.

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);       // DDX/DDV-Unterstützung.

  protected:
    DECLARE_MESSAGE_MAP()
};
