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

	void Render(wxDC& dc);

private:
	typedef std::list<CFlowNodeRenderProxy*> TFlowNodeNPList;
	int mMX, mMY;
	wxString mCurrStr;
	TFlowNodeNPList mNodeProxy;
	DECLARE_EVENT_TABLE();
};
