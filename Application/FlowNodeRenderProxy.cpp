#include "FlowNodeRenderProxy.h"
#include "NNode.h"
#include "FlowEditor.h"

CFlowNodeRenderProxy::CFlowNodeRenderProxy()
{
	// Forbidden
}

CFlowNodeRenderProxy::CFlowNodeRenderProxy(CFlowEditor* parent, NNode* node)
{
	mParent = parent;
	mNode = node;
	mHighlightLeft = false;
	mHighlightRight = false;
	mHighlightAll = false;
}

CFlowNodeRenderProxy::~CFlowNodeRenderProxy()
{

}

NNode* CFlowNodeRenderProxy::GetNNode()
{
	return mNode;
}

void CFlowNodeRenderProxy::Render()
{
	Render(wxClientDC(mParent));
}

void CFlowNodeRenderProxy::Render(wxDC& dc)
{
	//dc.SetBackground(wxBrush(wxColor(128, 200, 233)));
	//dc.Clear();
	const wxPoint& origin = mParent->GetOrigin();
	dc.SetBrush(wxBrush(wxColor(128, 240, 255)));
	SetHighlightPen(dc, mHighlightAll);
	dc.DrawRectangle(mNode->GetX() - origin.x,
		mNode->GetY() - origin.y, 100, 100);
	dc.DrawText(mNode->GetName().c_str(),
		mNode->GetX() + 4 - origin.x, mNode->GetY() - origin.y);
	dc.DrawText(mNode->GetType()->mName,
		mNode->GetX() + 4 - origin.x, mNode->GetY() + 14 - origin.y);
	dc.DrawLine(mNode->GetX() - origin.x, mNode->GetY() + 28 - origin.y,
		mNode->GetX() + 100 - origin.x, mNode->GetY() + 28 - origin.y);

	// Draw left socket
	dc.SetBrush(wxBrush(wxColor(128, 240, 200)));
	SetHighlightPen(dc, mHighlightLeft || mHighlightAll);
	dc.DrawCircle(mParent->WorldToWindow(
		wxPoint(mNode->GetX(), mNode->GetY() + 38)), 10);
	dc.SetBrush(wxBrush(wxColor(128, 240, 200)));

	// Draw right socket
	SetHighlightPen(dc, mHighlightRight || mHighlightAll);
	dc.DrawCircle(mParent->WorldToWindow(
		wxPoint(mNode->GetX() + 100, mNode->GetY() + 38)), 10);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
}

void CFlowNodeRenderProxy::SetHighlightPen(wxDC& dc, bool hi)
{
	if (hi)
		dc.SetPen(wxPen(wxColor(255, 255, 0), 5));
	else
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
}

bool CFlowNodeRenderProxy::PointInside(int x, int y)
{
	wxPoint worldPos = mParent->WindowToWorld(wxPoint(x, y));
	if (worldPos.x >= mNode->GetX() - 10 && worldPos.x <= mNode->GetX() + 110
		&& worldPos.y >= mNode->GetY() && worldPos.y <= mNode->GetY() + 100)
	{
		return true;
	}
	return false;
}

void CFlowNodeRenderProxy::ProcessEvents(SRenderEvtParams params)
{
	switch (params.evt)
	{
	case SRenderEvtParams::RE_LEFT_DOWN:
		goto LEFT_DOWN;
	case SRenderEvtParams::RE_LEFT_UP:
		goto LEFT_UP;
	case SRenderEvtParams::RE_MOUSE_OVER: //Same as MouseOver
	case SRenderEvtParams::RE_MOUSE_MOVE:
		goto MOUSE_OVER;
	default:
		return;
	}

LEFT_DOWN:
	SWire* tWire;
	switch (DeterminePart(params.x, params.y))
	{
	case PART_S_LEFT:
		break;
	case PART_S_RIGHT:
		tWire = mParent->SpawnTempWire(this);
		tWire->frPos = wxPoint(mNode->GetX() + 100, mNode->GetY() + 38);
		tWire->frSkt = NNode::NS_RIGHT;
		tWire->toPos = wxPoint(0, 0);
		break;
	default:
		break;
	}
	return;

LEFT_UP:
	switch (DeterminePart(params.x, params.y))
	{
	case PART_S_LEFT:
		if (tWire = mParent->GetTempWire())
		{
			tWire->to = this;
			tWire->toPos = wxPoint(mNode->GetX(), mNode->GetY() + 38);
			tWire->toSkt = NNode::NS_LEFT;
			mParent->FinishTempWire();
			mParent->AddWire(tWire);
			mParent->Render(wxClientDC(mParent));
		}
		break;
	case PART_S_RIGHT:
		break;
	default:
		break;
	}
	return;

MOUSE_OVER:
	mMouseWndPos = wxPoint(params.x, params.y);
	switch (DeterminePart(mMouseWndPos.x, mMouseWndPos.y))
	{
	case PART_S_LEFT:
		if (!mHighlightLeft)
		{
			mHighlightLeft = true;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightLeft = true;
		if (mHighlightAll)
		{
			mHighlightAll = false;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightAll = false;
		break;
	case PART_S_RIGHT:
		if (!mHighlightRight)
		{
			mHighlightRight = true;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightRight = true;
		if (mHighlightAll)
		{
			mHighlightAll = false;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightAll = false;
		break;
	case PART_BODY:
		if (!mHighlightAll)
		{
			mHighlightAll = true;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightAll = true;
		break;
	default:
		if (mHighlightRight || mHighlightLeft || mHighlightAll)
		{
			mHighlightLeft = mHighlightRight = mHighlightAll = false;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightLeft = mHighlightRight = mHighlightAll = false;
		break;
	}
	return;
}

int CFlowNodeRenderProxy::DeterminePart(int x, int y)
{
	wxPoint worldPos = mParent->WindowToWorld(wxPoint(x, y));
	wxPoint testc(mNode->GetX(), mNode->GetY() + 38);
	if (worldPos.x >= testc.x - 10 && worldPos.x <= testc.x + 10
		&& worldPos.y >= testc.y - 10 && worldPos.y <= testc.y + 10)
	{
		return PART_S_LEFT;
	}
	testc = wxPoint(mNode->GetX() + 100, mNode->GetY() + 38);
	if (worldPos.x >= testc.x - 10 && worldPos.x <= testc.x + 10
		&& worldPos.y >= testc.y - 10 && worldPos.y <= testc.y + 10)
	{
		return PART_S_RIGHT;
	}
	if (PointInside(x, y))
		return PART_BODY;
	return PART_UNKNOWN;
}
