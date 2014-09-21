#include "FlowEditor.h"
#include "FlowGraph.h"
#include "MainFrame.h"
#include "NNode.h"
#include "FlowNodeRenderProxy.h"

BEGIN_EVENT_TABLE(CFlowEditor, wxPanel)
	EVT_PAINT(CFlowEditor::OnPaint)
	EVT_MOTION(CFlowEditor::OnMouseMove)
	EVT_LEFT_DOWN(CFlowEditor::OnLeftDown)
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
		return;
	}
}

void CFlowEditor::OnLeftDown(wxMouseEvent& evt)
{
	GETMF();
	CFlowGraph* flowGraph = mf->GetFlowGraph();
	if (flowGraph->GetSpawningNode())
	{
		flowGraph->GetSpawningNode()->SetPosition(evt.GetX(), evt.GetY());
		mNodeProxy.push_back(
			new CFlowNodeRenderProxy(
			this, flowGraph->GetSpawningNode()
			));
		flowGraph->SpawnNode(flowGraph->GetSpawningNode());
		mf->PaintFlowEditor();
		return;
	}
}

void CFlowEditor::Render(wxDC& dc)
{
	GETMF();
	CFlowGraph* fg = mf->GetFlowGraph();

	dc.Clear();
	for (TFlowNodeNPList::iterator iter = mNodeProxy.begin();
		iter != mNodeProxy.end();
		iter++)
	{
		(*iter)->Render();
	}

	NNode* sn = fg->GetSpawningNode();
	if (sn)
	{
		dc.DrawText(mCurrStr, mMX, mMY);
	}
}
