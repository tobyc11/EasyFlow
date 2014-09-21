#include "FlowEditor.h"
#include "FlowGraph.h"
#include "MainFrame.h"
#include "NNode.h"

BEGIN_EVENT_TABLE(CFlowEditor, wxPanel)
	EVT_PAINT(CFlowEditor::OnPaint)
	EVT_MOTION(CFlowEditor::OnMouseMove)
END_EVENT_TABLE()

CFlowEditor::CFlowEditor()
{

}

CFlowEditor::CFlowEditor(wxWindow *parent, wxWindowID winid)
	: wxPanel(parent, winid)
{
	CreateControls();
	mCurrStr = wxString();
	//mRenderLock = 0;
}

CFlowEditor::~CFlowEditor()
{

}

void CFlowEditor::CreateControls()
{
	SetBackgroundColour(wxColour(128, 128, 128));
}

#define GETMF() CMainFrame* mf = (CMainFrame*)this->GetParent()->GetParent();

void CFlowEditor::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void CFlowEditor::OnMouseMove(wxMouseEvent& evt)
{
	GETMF();
	CFlowGraph* fg = mf->GetFlowGraph();
	NNode* sn = fg->GetSpawningNode();
	if (sn)
	{
		mMX = evt.GetX();
		mMY = evt.GetY();
		mCurrStr = sn->GetName().c_str();
		wxClientDC dc(this);
		Render(dc);
	}
}

void CFlowEditor::Render(wxDC& dc)
{
	GETMF();
	CFlowGraph* fg = mf->GetFlowGraph();

	dc.Clear();
	// Draw existing graph

	NNode* sn = fg->GetSpawningNode();
	if (sn)
	{
		wxString a;
		a = wxString("Current spawning node: ") + mCurrStr;
		dc.DrawText(a, mMX, mMY);
	}
}
