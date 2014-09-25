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

#include "Common.h"
#include "MainFrame.h"
#include "ToolBox.h"
#include "FlowEditor.h"
#include "FlowGraph.h"
#include "NodePropertyUI.h"
#include <wx/aboutdlg.h>

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
	EVT_CLOSE(CMainFrame::OnClose)
	EVT_MENU(wxID_EXIT, CMainFrame::OnQuit)
	EVT_MENU(wxID_ABOUT, CMainFrame::OnAbout)
	EVT_RIBBONTOOLBAR_CLICKED(wxID_ABOUT, CMainFrame::OnRibbonAbout)
	EVT_RIBBONTOOLBAR_CLICKED(wxID_EXECUTE, CMainFrame::OnRibbonDump)
	EVT_RIBBONTOOLBAR_CLICKED(wxID_SAVEAS, CMainFrame::OnRibbonSaveProp)
	EVT_RIBBONTOOLBAR_CLICKED(wxID_OK, CMainFrame::OnRibbonGenerate)
END_EVENT_TABLE()

CMainFrame::CMainFrame()
	: wxFrame(NULL, wxID_ANY, "myFlow", wxDefaultPosition, wxDefaultSize)
{
	wxInitAllImageHandlers();
	gEnv->MainFrame = this;
	mPropertyPanel = 0;
	SetIcon(wxIcon(wxString("App.png"), wxBITMAP_TYPE_PNG));
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
		wxBitmap iconNew(wxString("New.png"), wxBITMAP_TYPE_PNG);
		wxBitmap iconOpen(wxString("Open.png"), wxBITMAP_TYPE_PNG);
		wxBitmap iconSave(wxString("Save.png"), wxBITMAP_TYPE_PNG);
		wxBitmap iconAbout(wxString("About.png"), wxBITMAP_TYPE_PNG);
		wxBitmap iconDump(wxString("Dump.png"), wxBITMAP_TYPE_PNG);
		wxBitmap iconGen(wxString("Generate.png"), wxBITMAP_TYPE_PNG);
		wxBitmap iconSaveProp(wxString("SaveProp.png"), wxBITMAP_TYPE_PNG);

		wxRibbonPage* rpage = new wxRibbonPage(mRibbon, -1, "Common");
		mPropertyPage = rpage;
		wxRibbonPanel* rpanel = new wxRibbonPanel(rpage, wxID_ANY, "Common");
		wxRibbonToolBar* rtoolbar = new wxRibbonToolBar(rpanel);
		rtoolbar->AddTool(wxID_NEW, iconNew, "New");
		rtoolbar->AddTool(wxID_OPEN, iconOpen, "Open");
		rtoolbar->AddTool(wxID_SAVE, iconSave, "Save");
		rtoolbar->AddTool(wxID_ABOUT, iconAbout, "About");
		//rtoolbar->SetRows(2, 2);


		rpanel = new wxRibbonPanel(rpage, wxID_ANY, "Program");
		rtoolbar = new wxRibbonToolBar(rpanel);
		rtoolbar->AddTool(wxID_OK, iconGen, "Generate");
		rtoolbar->AddTool(wxID_EXECUTE, iconDump, "Dump Graph Info");
		rtoolbar->AddTool(wxID_SAVEAS, iconSaveProp, "Save Properties");
		//rtoolbar->SetRows(2, 3);
	}
	{
		wxRibbonPage* rpage = new wxRibbonPage(mRibbon, wxID_ANY, "About");
		wxRibbonPanel* rpanel = new wxRibbonPanel(rpage, wxID_ANY, "About");
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

	//mOutput = new wxDialog(this, wxID_ANY, "Output");
	//mLog = new wxTextCtrl(mOutput, wxID_ANY, wxEmptyString,
	//	wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE |
	//	wxTE_LEFT | wxTE_BESTWRAP | wxBORDER_NONE);

	mFlowGraph = new CFlowGraph();
	new CNodePropertyUI;
}

void CMainFrame::OnClose(wxCloseEvent& evt)
{
	this->Destroy();
	//mOutput->Destroy();
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
	aboutInfo.SetLicence(wxT("Source code is available in GPLv3\n")
		wxT("https://github.com/cyj0912/EasyFlow"));
	wxAboutBox(aboutInfo);
}

void CMainFrame::OnRibbonAbout(wxRibbonToolBarEvent& evt)
{
	OnAbout(static_cast<wxCommandEvent>(0));
}

void CMainFrame::OnRibbonGenerate(wxRibbonToolBarEvent& evt)
{
	const char* statusText = gEnv->FlowGraph->GenerateCode();
	wxMessageBox(statusText);
}

void CMainFrame::OnRibbonDump(wxRibbonToolBarEvent& evt)
{
	const char* statusText = gEnv->FlowGraph->GetStatus();
	wxMessageBox(statusText);
}

void CMainFrame::OnRibbonSaveProp(wxRibbonToolBarEvent& evt)
{
	gEnv->PropCtrl->UpdateTarget();
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
