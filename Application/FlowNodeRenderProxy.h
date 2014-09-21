#pragma once
#include <wx/wx.h>

class NNode;
class CFlowNodeRenderProxy
{
private:
	CFlowNodeRenderProxy();
public:
	CFlowNodeRenderProxy(wxWindow* parent, NNode* node);
	~CFlowNodeRenderProxy();
	void Render();
	void Render(wxDC& dc);

private:
	wxFrame* mParent;
	NNode* mNode;
};
