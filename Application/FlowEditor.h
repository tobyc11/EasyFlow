#pragma once
#include <wx/wx.h>
#include <list>

class CFlowNodeRenderProxy;
class CFlowEditor : public wxPanel
{
public:
	CFlowEditor();
	CFlowEditor(wxWindow *parent, wxWindowID winid = wxID_ANY);
	~CFlowEditor();
	void CreateControls();

	void OnPaint(wxPaintEvent& evt);
	void OnMouseMove(wxMouseEvent& evt);
	void OnLeftDown(wxMouseEvent& evt);
	void OnRightDown(wxMouseEvent& evt);
	void OnRightUp(wxMouseEvent& evt);

	void Render(wxDC& dc);
	const wxPoint& GetOrigin();
	wxPoint WindowToWorld(wxPoint& p);
	wxPoint WorldToWindow(wxPoint& p);

private:
	typedef std::list<CFlowNodeRenderProxy*> TFlowNodeNPList;
	int mMX, mMY;
	int mOX, mOY;
	int mDragOX, mDragOY, mSaveDragOX, mSaveDragOY;
	bool mDragging;
	wxPoint mOrigin;
	wxString mCurrStr;
	TFlowNodeNPList mNodeProxy;
	DECLARE_EVENT_TABLE();
};
