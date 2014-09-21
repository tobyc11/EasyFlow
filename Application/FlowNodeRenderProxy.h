#pragma once
#include <wx/wx.h>

class CFlowEditor;
class NNode;

struct SRenderEvtParams
{
	enum ERenderEvents
	{
		RE_MOUSE_OVER = 0,
		RE_LEFT_DOWN,
		RE_LEFT_UP,
		RE_RIGHT_DOWN,
		RE_RIGHT_UP,
		RE_MOUSE_MOVE
	} evt;
	int x;
	int y;
};

class CFlowNodeRenderProxy
{
private:
	CFlowNodeRenderProxy();
public:
	CFlowNodeRenderProxy(CFlowEditor* parent, NNode* node);
	~CFlowNodeRenderProxy();
	void Render();
	void Render(wxDC& dc);
	void SetHighlightPen(wxDC& dc, bool hi);
	bool PointInside(int x, int y);

	void ProcessEvents(SRenderEvtParams params);
	int DeterminePart(int x, int y);

private:
	enum EParts
	{
		PART_UNKNOWN = 0,
		PART_S_LEFT,
		PART_S_RIGHT,
		PART_S_DOWN,
		PART_TITLE,
		PART_BODY
	};

	CFlowEditor* mParent;
	NNode* mNode;

	bool mHighlightLeft;
	bool mHighlightRight;
	bool mHighlightAll;
	wxPoint mMouseWndPos;
};
