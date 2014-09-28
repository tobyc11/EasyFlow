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

#include "FlowNodeRenderProxy.h"
#include "NNode.h"
#include "FlowEditor.h"
#include "NodePropertyAccessor.h"

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
	mHighlightRight2 = false;

	CNodePropertyAccessor propAcc;
	propAcc.SetTargetNode(node);
	std::string& cflag = propAcc.GetPropertyValue("CFlag");
	if (cflag != "E")
		mHasLeft = true;
	else
		mHasLeft = false;

	std::string& rflag = propAcc.GetPropertyValue("RFlag");
	if (rflag == "RR")
		mHasRight2 = true;
	else
		mHasRight2 = false;

	mHasRight = true;
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

	dc.SetBrush(wxBrush(wxColor(128, 240, 200)));
	// Draw left socket
	if (mHasLeft)
	{
		SetHighlightPen(dc, mHighlightLeft || mHighlightAll);
		dc.DrawCircle(mParent->WorldToWindow(
			wxPoint(mNode->GetX(), mNode->GetY() + 38)), 10);
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	}

	// Draw right socket
	if (mHasRight)
	{
		SetHighlightPen(dc, mHighlightRight || mHighlightAll);
		dc.DrawCircle(mParent->WorldToWindow(
			wxPoint(mNode->GetX() + 100, mNode->GetY() + 38)), 10);
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	}

	// Draw right socket 2 if present
	if (mHasRight2)
	{
		SetHighlightPen(dc, mHighlightRight2 || mHighlightAll);
		dc.DrawCircle(mParent->WorldToWindow(
			GetSocketCenter(NNode::NS_RIGHT2)), 10);
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	}

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
	SWire* existWire;
	SWire* tWire;
	CFlowNodeRenderProxy* theOtherNode;
	switch (DeterminePart(params.x, params.y))
	{
	case PART_S_LEFT:
		if (!mHasLeft)
			break;
		if (existWire = mParent->FindWire(this, NNode::NS_LEFT))
		{
			theOtherNode = existWire->to == this ? existWire->from : existWire->to;
			tWire = mParent->SpawnTempWire(theOtherNode);
			tWire->frSkt = existWire->to == this ? existWire->frSkt : existWire->toSkt;
			tWire->UpdatePosition();
			mParent->EraseWire(existWire);
		}
		break;
	case PART_S_RIGHT:
		tWire = mParent->SpawnTempWire(this);
		tWire->frPos = wxPoint(mNode->GetX() + 100, mNode->GetY() + 38);
		tWire->frSkt = NNode::NS_RIGHT;
		tWire->toPos = wxPoint(0, 0);
		break;
	case PART_S_RIGHT2:
		if (mHasRight2)
		{
			tWire = mParent->SpawnTempWire(this);
			tWire->frSkt = NNode::NS_RIGHT2;
			tWire->UpdatePosition();
		}
		break;
	case PART_BODY:
		mParent->Grab(this, params.x, params.y);
		break;
	default:
		break;
	}
	return;

LEFT_UP:
	switch (DeterminePart(params.x, params.y))
	{
	case PART_S_LEFT:
		if (!mHasLeft)
			break;
		if (tWire = mParent->GetTempWire())
		{
			tWire->to = this;
			tWire->toPos = wxPoint(mNode->GetX(), mNode->GetY() + 38);
			tWire->toSkt = NNode::NS_LEFT;
			mParent->FinishTempWire();
			// mParent->AddWire(tWire); Already done by FinishTempWire()
			mParent->Render(wxClientDC(mParent));
		}
		break;
	case PART_S_RIGHT:
		break;
	case PART_BODY:
		mParent->StopGrabbing();
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
	case PART_S_RIGHT2:
		if (!mHighlightRight2)
		{
			mHighlightRight2 = true;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightRight2 = true;
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
		if (mHighlightRight || mHighlightLeft || mHighlightRight2 || mHighlightAll)
		{
			mHighlightLeft = mHighlightRight = mHighlightRight2 = mHighlightAll = false;
			mParent->Render(wxClientDC(mParent));
		}
		else
			mHighlightLeft = mHighlightRight = mHighlightRight2 = mHighlightAll = false;
		break;
	}
	return;
}

int CFlowNodeRenderProxy::DeterminePart(int x, int y)
{
	wxPoint worldPos = mParent->WindowToWorld(wxPoint(x, y));
	wxPoint testc(GetSocketCenter(NNode::NS_LEFT));
	if (worldPos.x >= testc.x - 10 && worldPos.x <= testc.x + 10
		&& worldPos.y >= testc.y - 10 && worldPos.y <= testc.y + 10)
	{
		return PART_S_LEFT;
	}
	testc = GetSocketCenter(NNode::NS_RIGHT);
	if (worldPos.x >= testc.x - 10 && worldPos.x <= testc.x + 10
		&& worldPos.y >= testc.y - 10 && worldPos.y <= testc.y + 10)
	{
		return PART_S_RIGHT;
	}
	testc = GetSocketCenter(NNode::NS_RIGHT2);
	if (worldPos.x >= testc.x - 10 && worldPos.x <= testc.x + 10
		&& worldPos.y >= testc.y - 10 && worldPos.y <= testc.y + 10)
	{
		return PART_S_RIGHT2;
	}
	if (PointInside(x, y))
		return PART_BODY;
	return PART_UNKNOWN;
}

wxPoint CFlowNodeRenderProxy::GetSocketCenter(int NNodeSocket)
{
	switch (NNodeSocket)
	{
	case NNode::NS_LEFT:
		return wxPoint(mNode->GetX(), mNode->GetY() + 38);
		break;
	case NNode::NS_RIGHT:
		return wxPoint(mNode->GetX() + 100, mNode->GetY() + 38);
		break;
	case NNode::NS_RIGHT2:
		return wxPoint(mNode->GetX() + 100, mNode->GetY() + 58);
		break;
	case NNode::NS_DOWN:
		return wxPoint(mNode->GetX() + 50, mNode->GetY() + 100);
		break;
	default:
		break;
	}
	return wxPoint(0, 0);
}
