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
	void OnRibbonTips(wxRibbonToolBarEvent& evt);
	void OnRibbonDump(wxRibbonToolBarEvent& evt);

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
