#pragma once
#include <wx/wx.h>

class wxCommandLinkButton;
class CToolBox : public wxPanel
{
public:
	CToolBox(wxWindow *parent, wxWindowID winid = wxID_ANY);
	~CToolBox();
	void CreateControls();
	void OnNodeButton(wxCommandEvent& evt);
	void OnLeftDown(wxMouseEvent& evt);

private:
	CToolBox();
	int mNodeCount;
	wxCommandLinkButton* mNodes[256];
	DECLARE_EVENT_TABLE();
};
