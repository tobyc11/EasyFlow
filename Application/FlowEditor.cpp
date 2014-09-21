#include "FlowEditor.h"
#include "FlowGraph.h"
#include "MainFrame.h"
#include "NNode.h"
#include "FlowNodeRenderProxy.h"

BEGIN_EVENT_TABLE(CFlowEditor, wxPanel)
	EVT_PAINT(CFlowEditor::OnPaint)
	EVT_MOTION(CFlowEditor::OnMouseMove)
	EVT_LEFT_DOWN(CFlowEditor::OnLeftDown)
	EVT_RIGHT_DOWN(CFlowEditor::OnRightDown)
	EVT_RIGHT_UP(CFlowEditor::OnRightUp)
END_EVENT_TABLE()

CFlowEditor::CFlowEditor()
{

}

CFlowEditor::CFlowEditor(wxWindow *parent, wxWindowID winid)
	: wxPanel(parent, winid)
{
	CreateControls();
	mCurrStr = wxString();
	mOX = mOY = 0;
	mDragging = false;
	//mRenderLock = 0;
}

CFlowEditor::~CFlowEditor()
{

}

void CFlowEditor::CreateControls()
{
	SetBackgroundColour(wxColour(200, 200, 200));
}

#define GETMF() CMainFrame* mf = (CMainFrame*)this->GetParent()->GetParent();

void CFlowEditor::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void CFlowEditor::OnMouseMove(wxMouseEvent& evt)
{
	if (mDragging)
	{
		mOX = mSaveDragOX + mDragOX - evt.GetX();
		mOY = mSaveDragOY + mDragOY - evt.GetY();
		wxClientDC dc(this);
		Render(dc);
	}

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
		wxPoint wndPos(evt.GetX(), evt.GetY());
		wndPos = WindowToWorld(wndPos);
		flowGraph->GetSpawningNode()->SetPosition(wndPos.x, wndPos.y);
		mNodeProxy.push_back(
			new CFlowNodeRenderProxy(
			this, flowGraph->GetSpawningNode()
			));
		flowGraph->SpawnNode(flowGraph->GetSpawningNode());
		mf->PaintFlowEditor();
		return;
	}
}

void CFlowEditor::OnRightDown(wxMouseEvent& evt)
{
	GETMF();
	CFlowGraph* flowGraph = mf->GetFlowGraph();
	mDragOX = evt.GetX();
	mDragOY = evt.GetY();
	mSaveDragOX = mOX; mSaveDragOY = mOY;
	mDragging = true;
	if (flowGraph->GetSpawningNode())
	{
		return;
	}
}

void CFlowEditor::OnRightUp(wxMouseEvent& evt)
{
	GETMF();
	CFlowGraph* flowGraph = mf->GetFlowGraph();
	mDragging = false;
	if (flowGraph->GetSpawningNode())
	{
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

const wxPoint& CFlowEditor::GetOrigin()
{
	return mOrigin = wxPoint(mOX, mOY);
}

wxPoint CFlowEditor::WindowToWorld(wxPoint& p)
{
	return wxPoint(p.x + mOX, p.y + mOY);
}

wxPoint CFlowEditor::WorldToWindow(wxPoint& p)
{
	return wxPoint(p.x - mOX, p.y - mOY);
}
