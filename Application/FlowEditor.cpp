#include <Main\Common.h>
#include "FlowEditor.h"
#include "FlowGraph.h"
#include "MainFrame.h"
#include "NNode.h"
#include "FlowNodeRenderProxy.h"
#include "NodePropertyController.h"

BEGIN_EVENT_TABLE(CFlowEditor, wxPanel)
	EVT_PAINT(CFlowEditor::OnPaint)
	EVT_MOTION(CFlowEditor::OnMouseMove)
	EVT_LEFT_DOWN(CFlowEditor::OnLeftDown)
	EVT_LEFT_UP(CFlowEditor::OnLeftUp)
	EVT_RIGHT_DOWN(CFlowEditor::OnRightDown)
	EVT_RIGHT_UP(CFlowEditor::OnRightUp)
END_EVENT_TABLE()

CFlowEditor::CFlowEditor()
{
	gEnv->FlowEditor = this;
}

CFlowEditor::CFlowEditor(wxWindow *parent, wxWindowID winid)
	: wxPanel(parent, winid)
{
	gEnv->FlowEditor = this;
	CreateControls();
	mCurrStr = wxString();
	mOX = mOY = 0;
	mDragging = false;
	mCurrWire = 0;
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

	// Dispatch events to node proxies
	SRenderEvtParams params;
	params.evt = SRenderEvtParams::RE_MOUSE_OVER;
	params.x = evt.GetX();
	params.y = evt.GetY();
	for (TFlowNodeNPList::iterator iter = mNodeProxy.begin();
		iter != mNodeProxy.end();
		iter++)
	{
		if ((*iter)->PointInside(params.x, params.y))
			(*iter)->ProcessEvents(params);
		else
		{
			params.evt = SRenderEvtParams::RE_MOUSE_MOVE;
			(*iter)->ProcessEvents(params);
			params.evt = SRenderEvtParams::RE_MOUSE_OVER;
		}
	}

	// Handle wire
	SWire* tempWire;
	if (tempWire = GetTempWire())
	{
		tempWire->toPos = WindowToWorld(wxPoint(evt.GetX(), evt.GetY()));
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

// Process event when left mouse buttton is pressed
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

	// Dispatch events to node proxies
	SRenderEvtParams params;
	params.evt = SRenderEvtParams::RE_LEFT_DOWN;
	params.x = evt.GetX();
	params.y = evt.GetY();
	for (TFlowNodeNPList::iterator iter = mNodeProxy.begin();
		iter != mNodeProxy.end();
		iter++)
	{
		if ((*iter)->PointInside(params.x, params.y))
		{
			(*iter)->ProcessEvents(params);

			// By the way select this, tell NodePropController
			if (!GetTempWire())
			{
				gEnv->PropCtrl->SetTargetNode((*iter)->GetNNode());
				gEnv->PropCtrl->UpdatePropertiesFromTarget();
			}
		}
	}
}

void CFlowEditor::OnLeftUp(wxMouseEvent& evt)
{
	// Dispatch events to node proxies
	SRenderEvtParams params;
	params.evt = SRenderEvtParams::RE_LEFT_UP;
	params.x = evt.GetX();
	params.y = evt.GetY();
	for (TFlowNodeNPList::iterator iter = mNodeProxy.begin();
		iter != mNodeProxy.end();
		iter++)
	{
		if ((*iter)->PointInside(params.x, params.y))
			(*iter)->ProcessEvents(params);
	}

	if (GetTempWire())
	{
		CancelTempWire();
		Render(wxClientDC(this));
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
	dc.SetBrush(wxBrush(wxColor(255, 0, 0)));
	dc.DrawCircle(WorldToWindow(wxPoint(0, 0)), 10);
	//Draw nodes
	for (TFlowNodeNPList::iterator iter = mNodeProxy.begin();
		iter != mNodeProxy.end();
		iter++)
	{
		(*iter)->Render();
	}
	//Draw wires
	for (TWireList::iterator iter = mWires.begin();
		iter != mWires.end();
		iter++)
	{
		(*iter)->Render(wxClientDC(this), this);
	}

	NNode* sn = fg->GetSpawningNode();
	if (sn)
	{
		dc.DrawText(mCurrStr, mMX, mMY);
	}

	if (mCurrWire)
	{
		mCurrWire->Render(wxClientDC(this), this);
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

SWire* CFlowEditor::AddWire(CFlowNodeRenderProxy* left, CFlowNodeRenderProxy* right)
{
	//Unusable
	SWire* wire = new SWire();
	if (left)
	{
		wire->from = left;
		//wire->frPos = left->
	}
	if (right)
	{
		wire->to = right;
	}
	return wire;
}

SWire* CFlowEditor::AddWire(SWire* w)
{
	this->mWires.push_back(w);
	return w;
}

SWire* CFlowEditor::SpawnTempWire(CFlowNodeRenderProxy* fromleft, CFlowNodeRenderProxy* fromright)
{
	this->mCurrWire = new SWire();
	mCurrWire->from = fromleft;
	mCurrWire->to = fromright;
	return mCurrWire;
}

void CFlowEditor::CancelTempWire()
{
	delete mCurrWire;
	mCurrWire = 0;
}

void CFlowEditor::FinishTempWire()
{
	if (mCurrWire)
	{
		// Linked to itself?
		if (mCurrWire->from == mCurrWire->to)
		{
			CancelTempWire();
			return;
		}

		// Test if there is already wires linked to point
		for (TWireList::iterator iter = mWires.begin();
			iter != mWires.end();
			iter++)
		{
			if ((*iter)->from == mCurrWire->from)
			{
				// Handle form same socket
			}
			if ((*iter)->to == mCurrWire->to)
			{
				// Handle to same socket
			}
		}

		// Update the underlying CFlowGraph
		NNode *manleft = mCurrWire->from->GetNNode();
		manleft->SetSibling(mCurrWire->frSkt, mCurrWire->to->GetNNode());
		NNode *manright = mCurrWire->to->GetNNode();
		manright->SetSibling(mCurrWire->toSkt, mCurrWire->from->GetNNode());
		mCurrWire = 0;
	}
}

SWire* CFlowEditor::GetTempWire()
{
	return mCurrWire;
}
