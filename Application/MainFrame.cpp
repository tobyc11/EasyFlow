#include <Main\Common.h>
#include "MainFrame.h"
#include "ToolBox.h"
#include "FlowEditor.h"
#include "FlowGraph.h"
#include <wx/aboutdlg.h>
// #include <dwmapi.h>
#include <Main\XPM\ico.xpm>
#include <Main\XPM\ICO_NEW.xpm>
#include <Main\XPM\ICO_SAVE.xpm>
#include <Main\XPM\ICO_TIP.xpm>
#include <Main\XPM\Lite-Icon-icon.xpm>

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, CMainFrame::OnQuit)
	EVT_MENU(wxID_ABOUT, CMainFrame::OnAbout)
	EVT_RIBBONTOOLBAR_CLICKED(wxID_ABOUT, CMainFrame::OnRibbonAbout)
	EVT_RIBBONTOOLBAR_CLICKED(wxID_HELP_INDEX, CMainFrame::OnRibbonTips)
END_EVENT_TABLE()

CMainFrame::CMainFrame()
	: wxFrame(NULL, wxID_ANY, "myFlow", wxDefaultPosition, wxDefaultSize)
{
	SetIcon(wxIcon(tip_xpm));
	Maximize(true);
	CreateControls();
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::CreateControls()
{
	// Start creating main UI
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	mMenubar = new wxMenuBar;
	wxMenu* file = new wxMenu;
	file->Append(wxID_EXIT, wxT("&Quit"));
	mMenubar->Append(file, wxT("&File"));
	wxMenu* help = new wxMenu;
	help->Append(wxID_ABOUT, wxT("&About"));
	mMenubar->Append(help, wxT("&Help"));
	SetMenuBar(mMenubar);

	mStatusbar = CreateStatusBar();
	mStatusbar->SetStatusText("Ready");

	mRibbon = new wxRibbonBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxRIBBON_BAR_DEFAULT_STYLE);
	mRibbon->SetTabCtrlMargins(10, 20);
	{
		wxRibbonPage* rpage = new wxRibbonPage(mRibbon, -1, "Common");
		wxRibbonPanel* rpanel = new wxRibbonPanel(rpage);
		wxRibbonToolBar* rtoolbar = new wxRibbonToolBar(rpanel);
		rtoolbar->AddTool(wxID_NEW, ICO_NEW, "New");
		rtoolbar->AddTool(wxID_SAVE, ICO_SAVE, "Save");
		rtoolbar->AddTool(wxID_HELP_INDEX, ICO_TIP, "Tips");
		rtoolbar->AddTool(wxID_ABOUT, tip_xpm, "About");
		//rtoolbar->SetRows(2, 2);

		rpanel = new wxRibbonPanel(rpage);
		rtoolbar = new wxRibbonToolBar(rpanel);
		rtoolbar->AddTool(wxID_OK, Lite_Icon_icon, "Generate");
		//rtoolbar->SetRows(2, 3);
	}
	{
		wxRibbonPage* rpage = new wxRibbonPage(mRibbon, -1, "Node");
		wxRibbonPanel* rpanel = new wxRibbonPanel(rpage);
		wxRibbonPanel* rpanel2 = new wxRibbonPanel(rpage);
	}
	mRibbon->Realise();

	wxPanel* midpanel = new wxPanel(this, wxID_ANY);
	midpanel->SetBackgroundColour(wxColour(216, 236, 255));
	{
		CToolBox* toolbox = new CToolBox(midpanel, wxID_ANY);
		mFlowEditor = new CFlowEditor(midpanel, wxID_ANY);
		wxSizer* midsizer = new wxBoxSizer(wxHORIZONTAL);
		midsizer->Add(toolbox, 0, wxEXPAND | wxALL, 10);
		midsizer->Add(mFlowEditor, 1, wxEXPAND | wxALL, 10);
		midpanel->SetSizer(midsizer);
	}

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(mRibbon, 0, wxEXPAND);
	sizer->Add(midpanel, 1, wxEXPAND);
	SetSizer(sizer);

	//Connect(wxEVT_PAINT, wxPaintEventHandler(CMainFrame::OnPaint));

	mFlowGraph = new CFlowGraph();
	mFlowGraph->BindEditor(mFlowEditor);
}

void CMainFrame::OnPaint(wxPaintEvent& evt)
{
}

void CMainFrame::OnQuit(wxCommandEvent& evt)
{
	this->Close();
}

void CMainFrame::OnAbout(wxCommandEvent& evt)
{
	wxAboutDialogInfo aboutInfo;
	aboutInfo.SetName(_(APP_NAME));
	aboutInfo.SetVersion(_(APP_VERSION));
	aboutInfo.SetDescription(_("Rethinking Programming!"));
	aboutInfo.SetCopyright("(C) 2014 Toby Chen");
	aboutInfo.SetWebSite("http://www.ncchristian.org");
	aboutInfo.AddDeveloper("Toby Chen");
	aboutInfo.SetLicence(_("Source code is available in GPLv3\nhttps://github.com/cyj0912/EasyFlow"));
	wxAboutBox(aboutInfo);
}

void CMainFrame::OnRibbonAbout(wxRibbonToolBarEvent& evt)
{
	OnAbout(static_cast<wxCommandEvent>(0));
}

void CMainFrame::OnRibbonTips(wxRibbonToolBarEvent& evt)
{
	mStatusbar->SetStatusText(_("Nothing yet..."));
}

CFlowGraph* CMainFrame::GetFlowGraph()
{
	return mFlowGraph;
}

void CMainFrame::PaintFlowEditor()
{
	wxClientDC dc(mFlowEditor);
	mFlowEditor->Render(dc);
}
