// $Id: AdvancedTaskController.cpp,v 1.1 2006/01/20 15:17:00 gerrit-albrecht Exp $
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
#include "AboutDialog.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAdvancedTaskController

BEGIN_MESSAGE_MAP(CAdvancedTaskController, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CAdvancedTaskController::OnAppAbout)
END_MESSAGE_MAP()

// Das einzige CAdvancedTaskController-Objekt

CAdvancedTaskController theApp;

// CAdvancedTaskController-Erstellung

CAdvancedTaskController::CAdvancedTaskController()
{
	EnableHtmlHelp();

	// TODO: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}

// CAdvancedTaskController-Initialisierung

BOOL CAdvancedTaskController::InitInstance()
{
  // InitCommonControlsEx() ist für Windows XP erforderlich, wenn ein Anwendungsmanifest
  // die Verwendung von ComCtl32.dll Version 6 oder höher zum Aktivieren
  // von visuellen Stilen angibt. Ansonsten treten beim Erstellen von Fenstern Fehler auf.

  INITCOMMONCONTROLSEX InitCtrls;
  InitCtrls.dwSize = sizeof(InitCtrls);

  // Legen Sie dies fest, um alle allgemeinen Steuerelementklassen einzubeziehen,
  // die Sie in Ihrer Anwendung verwenden möchten.

  InitCtrls.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&InitCtrls);

  CWinApp::InitInstance();

  if (! AfxOleInit()) {                        // OLE-Bibliotheken initialisieren.
    AfxMessageBox(IDP_OLE_INIT_FAILED);
    return FALSE;
  }

  AfxEnableControlContainer();

  SetRegistryKey(_T("G.A.S.I."));  // Registrierungsschlüssel, unter dem die Einstellungen gespeichert werden.

  // Dieser Code erstellt ein neues Rahmenfensterobjekt und legt dieses
  // als Hauptfensterobjekt der Anwendung fest, um das Hauptfenster zu erstellen.

  CMainFrame *pFrame = new CMainFrame;
  if (! pFrame)
    return FALSE;
  m_pMainWnd = pFrame;

  // Rahmen mit Ressourcen erstellen und laden
  pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

  // Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
  pFrame->ShowWindow(SW_SHOW);
  pFrame->UpdateWindow();

  // Rufen Sie DragAcceptFiles nur auf, wenn eine Suffix vorhanden ist.
  // In einer SDI-Anwendung ist dies nach ProcessShellCommand erforderlich.

  return TRUE;
}

void CAdvancedTaskController::ShowErrorMessage(UINT ids)
{
  AfxMessageBox(ids, MB_ICONEXCLAMATION | MB_OK);
}

void CAdvancedTaskController::SetStatusBarText (CString &s)
{
  CMainFrame *mf = (CMainFrame *) GetMainWnd();   // Im Child: GetParentFrame();
  CStatusBar &sb = mf->GetStatusBar();
  CStatusBarCtrl &sbc = sb.GetStatusBarCtrl();

  sb.SetPaneText(1, s);

  /*
  HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE
								((m_bPortOK)? (IDI_CONNECT_CLOSE):(IDI_CONNECT_OPEN)),
								RT_GROUP_ICON);
	HICON hConnectIcon = (HICON)LoadImage(hInst,
								MAKEINTRESOURCE((m_bPortOK)? (IDI_CONNECT_CLOSE):(IDI_CONNECT_OPEN)),
								IMAGE_ICON,26,16, LR_DEFAULTCOLOR);
	pStatusBarCtrl.SetIcon(3, hConnectIcon )
  */
}

// Anwendungsbefehl zum Ausführen des Dialogfelds.

void CAdvancedTaskController::OnAppAbout()
{
  CAboutDialog dialog;

  dialog.DoModal();
}
