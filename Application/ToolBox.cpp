/*
This file is part of EasyFlow.

EasyFlow is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

EasyFlow is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with EasyFlow. If not, see <http://www.gnu.org/licenses/>.

Author: Toby Chen @ 2014
*/

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
