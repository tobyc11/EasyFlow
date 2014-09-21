#pragma once
#include <wx/wx.h>

class CFlowEditor : public wxPanel
{
public:
	CFlowEditor();
	CFlowEditor(wxWindow *parent, wxWindowID winid = wxID_ANY);
	~CFlowEditor();
	void CreateControls();

	void OnPaint(wxPaintEvent& evt);
	void OnMouseMove(wxMouseEvent& evt);

	void Render(wxDC& dc);

private:
	int mMX, mMY;
	wxString mCurrStr;
	DECLARE_EVENT_TABLE();
};
