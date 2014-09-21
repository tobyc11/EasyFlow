#include "FlowNodeRenderProxy.h"
#include "NNode.h"

CFlowNodeRenderProxy::CFlowNodeRenderProxy()
{
	// Forbidden
}

CFlowNodeRenderProxy::CFlowNodeRenderProxy(wxWindow* parent, NNode* node)
{
	mParent = (wxFrame*)parent;
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
	dc.SetBrush(wxBrush(wxColor(128, 200, 233)));
	dc.DrawRectangle(mNode->GetX(), mNode->GetY(), 100, 100);
	dc.DrawText(mNode->GetName().c_str(), mNode->GetX() + 4, mNode->GetY());
	dc.DrawText(mNode->GetType()->mName, mNode->GetX() + 4, mNode->GetY() + 14);
}
