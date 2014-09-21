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
}

CFlowNodeRenderProxy::~CFlowNodeRenderProxy()
{

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
	dc.DrawRectangle(mNode->GetX() - origin.x,
		mNode->GetY() - origin.y, 100, 100);
	dc.DrawText(mNode->GetName().c_str(),
		mNode->GetX() + 4 - origin.x, mNode->GetY() - origin.y);
	dc.DrawText(mNode->GetType()->mName,
		mNode->GetX() + 4 - origin.x, mNode->GetY() + 14 - origin.y);
	dc.DrawLine(mNode->GetX() - origin.x, mNode->GetY() + 28 - origin.y,
		mNode->GetX() + 100 - origin.x, mNode->GetY() + 28 - origin.y);
}
