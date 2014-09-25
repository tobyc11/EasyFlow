/*
This file is part of EasyFlow.

EasyFlow is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

EasyFlow is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with EasyFlow. If not, see <http://www.gnu.org/licenses/>.

Author: Toby Chen @ 2014
*/

#pragma once
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/toolbar.h>
#include <wx/ribbon/page.h>

class CFlowGraph;
class CFlowEditor;
class wxRibbonBar;
class wxMenuBar;
class CMainFrame : public wxFrame
{
public:
	CMainFrame();
	~CMainFrame();
	void CreateControls();

	void OnClose(wxCloseEvent& evt);
	void OnPaint(wxPaintEvent& evt);
	void OnQuit(wxCommandEvent& evt);
	void OnAbout(wxCommandEvent& evt);
	void OnRibbonAbout(wxRibbonToolBarEvent& evt);
	void OnRibbonGenerate(wxRibbonToolBarEvent& evt);
	void OnRibbonDump(wxRibbonToolBarEvent& evt);
	void OnRibbonSaveProp(wxRibbonToolBarEvent& evt);

	CFlowGraph* GetFlowGraph();
	void PaintFlowEditor();

	wxStatusBar* mStatusbar;

	wxRibbonPage* mPropertyPage;
	wxRibbonPanel* mPropertyPanel;

private:
	CFlowGraph* mFlowGraph;
	CFlowEditor* mFlowEditor;
	wxRibbonBar* mRibbon;
	wxMenuBar* mMenubar;
	DECLARE_EVENT_TABLE();
};
