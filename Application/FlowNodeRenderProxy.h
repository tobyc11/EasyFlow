#pragma once
#include <wx/wx.h>

class CFlowEditor;
class NNode;
class CFlowNodeRenderProxy
{
private:
	CFlowNodeRenderProxy();
public:
	CFlowNodeRenderProxy(CFlowEditor* parent, NNode* node);
	~CFlowNodeRenderProxy();
	void Render();
	void Render(wxDC& dc);
	bool PointInside(int x, int y);

private:
	CFlowEditor* mParent;
	NNode* mNode;
};
