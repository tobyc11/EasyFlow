#pragma once
#include <wx/wx.h>
#include <list>

class CFlowNodeRenderProxy;
struct SWire;

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
	void OnLeftUp(wxMouseEvent& evt);
	void OnRightDown(wxMouseEvent& evt);
	void OnRightUp(wxMouseEvent& evt);

	void Render(wxDC& dc);
	const wxPoint& GetOrigin();
	wxPoint WindowToWorld(wxPoint& p);
	wxPoint WorldToWindow(wxPoint& p);

	SWire* AddWire(CFlowNodeRenderProxy* left, CFlowNodeRenderProxy* right);
	SWire* AddWire(SWire*);
	SWire* SpawnTempWire(CFlowNodeRenderProxy* fromleft, CFlowNodeRenderProxy* fromright = 0);
	void CancelTempWire();
	void FinishTempWire(); // Caution: May cause memory leak
	SWire* GetTempWire();

private:
	typedef std::list<CFlowNodeRenderProxy*> TFlowNodeNPList;
	typedef std::list<SWire*> TWireList;
	int mMX, mMY;
	int mOX, mOY;
	int mDragOX, mDragOY, mSaveDragOX, mSaveDragOY;
	bool mDragging;
	wxPoint mOrigin;
	wxString mCurrStr;
	TFlowNodeNPList mNodeProxy;
	TWireList mWires;
	SWire* mCurrWire;
	DECLARE_EVENT_TABLE();
};

struct SWire
{
	CFlowNodeRenderProxy* from;
	CFlowNodeRenderProxy* to;
	wxPoint frPos;
	wxPoint toPos;
	int frSkt, toSkt;
	inline SWire()
	{
		from = 0;
		to = 0;
		frSkt = 0;
		toSkt = 0;
	}

	inline void Render(wxDC& dc, CFlowEditor* ed)
	{
		wxPoint frw = ed->WorldToWindow(frPos);
		wxPoint tow = ed->WorldToWindow(toPos);
		dc.DrawLine(frw, tow);
	}
};
