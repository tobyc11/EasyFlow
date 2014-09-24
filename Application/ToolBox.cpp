#include "Common.h"
#include "ToolBox.h"
#include "MainFrame.h"
#include "FlowGraph.h"
#include <wx/commandlinkbutton.h>
#include "NInterface.h"

BEGIN_EVENT_TABLE(CToolBox, wxPanel)
	EVT_BUTTON(wxID_ANY, CToolBox::OnNodeButton)
	EVT_LEFT_DOWN(CToolBox::OnLeftDown)
END_EVENT_TABLE()

CToolBox::CToolBox()
{
	gEnv->ToolBox = this;
	// CreateControls();
}

CToolBox::CToolBox(wxWindow *parent, wxWindowID winid)
	: wxPanel(parent, winid)
{
	gEnv->ToolBox = this;
	CreateControls();
}

CToolBox::~CToolBox()
{

}

void CToolBox::CreateControls()
{
	SetBackgroundColour(wxColour(255, 255, 255));
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	mNodeCount = 0;
	UNodeRegister* currReg = UNodeRegister::sRegisterLink;
	while (currReg != 0)
	{
		mNodes[mNodeCount] = new wxCommandLinkButton(this, currReg->mID, currReg->mName, currReg->mDesc);
		sizer->Add(mNodes[mNodeCount]);
		currReg = currReg->mNext;
		mNodeCount++;
	}
	SetSizer(sizer);
}

#define GETMF() CMainFrame* mf = (CMainFrame*)this->GetParent()->GetParent();

void CToolBox::OnNodeButton(wxCommandEvent& evt)
{
	int id = evt.GetId();
	GETMF();
	mf->GetFlowGraph()->StartSpawnNode(id);
}

void CToolBox::OnLeftDown(wxMouseEvent& evt)
{
	GETMF();
	mf->GetFlowGraph()->CancelSpawnNode();
	mf->PaintFlowEditor();
}
