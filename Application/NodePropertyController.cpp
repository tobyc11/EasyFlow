#include <Main/Common.h>
#include "NodePropertyController.h"
#include "MainFrame.h"

CNodePropertyController::CNodePropertyController()
{
	gEnv->PropCtrl = this;
	mTargetNode = 0;
	mOutdated = true;
	DestroyUI();
}

CNodePropertyController::~CNodePropertyController()
{

}

void CNodePropertyController::SetTargetNode(NNode* node)
{
	mTargetNode = node;
	mOutdated = true;
}

void CNodePropertyController::UpdatePropertiesFromTarget()
{
	// You are losing all the changes!!!
	DestroyUI();
	CreateText("asfd");
	mOutdated = false;
}

bool CNodePropertyController::UpdateTarget()
{
	return true;
}

TPropTable& CNodePropertyController::GetAvailableProps()
{
	if (mTargetNode)
	{
		return mTargetNode->mPropTable;
	}
	assert(1); // BUG!!!
	return mTargetNode->mPropTable;
}

std::string& CNodePropertyController::GetPropertyValue(const std::string& name)
{
	if (mTargetNode)
	{
		for (TPropTable::iterator iter = mTargetNode->mPropTable.begin();
			iter != mTargetNode->mPropTable.end(); iter++)
		{
			if (name == (*iter).mName)
			{
				return (*iter).mValue;
			}
		}
	}
	assert(1); // BUUUUGGGGG!!!
	return const_cast<std::string&>(name);
}

bool CNodePropertyController::SetPropertyValue(const std::string& name, const std::string& value)
{
	if (mTargetNode)
	{
		for (TPropTable::iterator iter = mTargetNode->mPropTable.begin();
			iter != mTargetNode->mPropTable.end(); iter++)
		{
			if (name == (*iter).mName)
			{
				(*iter).mValue = value;
				return true;
			}
		}
	}
	return false;
}

// Helpers for GUI (Creating ribbon elements to edit props)
wxTextCtrl* CNodePropertyController::CreateText(const std::string& name)
{
	CreateUIPanel();
	int y = (mRowCount == 0) ? 5 : (mRowCount == 1 ? 25 : 45);
	wxRibbonPanel* panel = gEnv->MainFrame->mPropertyPanel;
	wxStaticText* namelable = new wxStaticText(panel, wxID_ANY, name.c_str(), wxPoint(5, y), wxSize(20, 20));
	wxTextCtrl* control = new wxTextCtrl(panel, wxID_ANY, name.c_str(), wxPoint(30, y), wxSize(70, 20));
	gEnv->MainFrame->mPropertyPage->Realize();
	return 0;
}

wxChoice* CNodePropertyController::CreateChoice(const std::string& name)
{
	CreateUIPanel();
	int y = (mRowCount == 0) ? 5 : (mRowCount == 1 ? 25 : 45);
	return 0;
}

wxCheckBox* CNodePropertyController::CreateCheckBox(const std::string& name, bool default_value)
{
	CreateUIPanel();
	int y = (mRowCount == 0) ? 5 : (mRowCount == 1 ? 25 : 45);
	return 0;
}

void CNodePropertyController::CreateUIPanel()
{
	if (!gEnv->MainFrame->mPropertyPanel)
	{
		wxString name("Property");
		if (mTargetNode)
			name = name + " - " + mTargetNode->GetName().c_str();
		gEnv->MainFrame->mPropertyPanel = new wxRibbonPanel(gEnv->MainFrame->mPropertyPage, wxID_ANY, name);
	}
}

void CNodePropertyController::DestroyUI()
{
	mRowCount = 0;
	mRowXPos[0] = mRowXPos[1] = mRowXPos[2] = 0;
	if (gEnv->MainFrame->mPropertyPanel)
	{
		delete gEnv->MainFrame->mPropertyPanel;
		gEnv->MainFrame->mPropertyPanel = 0;
	}
}
