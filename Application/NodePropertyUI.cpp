#include "Common.h"
#include "NodePropertyUI.h"
#include "MainFrame.h"

CNodePropertyUI::CNodePropertyUI()
{
	gEnv->PropCtrl = this;
	mTargetNode = 0;
}

CNodePropertyUI::~CNodePropertyUI()
{

}

void CNodePropertyUI::UpdatePropertiesFromTarget()
{
	CreateUI();
}

bool CNodePropertyUI::UpdateTarget()
{
	if (mTargetNode)
	{
		mTargetNode->SetName(mNameCtrl->GetValue().ToStdString());
		for (TPropTable::iterator iter = mTargetNode->mPropTable.begin();
			iter != mTargetNode->mPropTable.end(); iter++)
		{
			if ((*iter).mType == std::string("T"))
			{
				wxTextCtrl* control = (wxTextCtrl*)FindInControlList((*iter).mName);
				(*iter).mValue = control->GetValue().ToStdString();
			}
			else if ((*iter).mType == std::string("D"))
			{
				// UNIMPLEMENTED!!!!!!!!!
			}
			else if ((*iter).mType == std::string("C"))
			{
				wxCheckBox* control = (wxCheckBox*)FindInControlList((*iter).mName);
				if (control->GetValue())
					(*iter).mValue = std::string("T");
				else
					(*iter).mValue = std::string("F");
			}
		}

		// Repaint the whole thing
		gEnv->MainFrame->PaintFlowEditor();
		CreateUI();
		return true;
	}
	return false;
}

// Helpers for GUI (Creating ribbon elements to edit props)
void CNodePropertyUI::CreateUI()
{
	// mHasUI = true;
	DestroyUI();
	if (mTargetNode)
	{
		mNameCtrl = CreateText("Name");
		mNameCtrl->SetValue(mTargetNode->GetName().c_str());
		mCtrlList.clear();
		for (TPropTable::iterator iter = mTargetNode->mPropTable.begin();
			iter != mTargetNode->mPropTable.end(); iter++)
		{
			if ((*iter).mType == std::string("T"))
			{
				wxTextCtrl* control = CreateText((*iter).mName);
				control->SetValue((*iter).mValue);
				
				TControlPair tCtrlPair;
				tCtrlPair.first = (*iter).mName;
				tCtrlPair.second = control;
				mCtrlList.push_back(tCtrlPair);
			}
			else if ((*iter).mType == std::string("D"))
			{
				// UNIMPLEMENTED!!!!!!!!!
				//wxTextCtrl* control = CreateText((*iter).mName);
				//control->SetValue((*iter).mValue);
			}
			else if ((*iter).mType == std::string("C"))
			{
				wxCheckBox* control = CreateCheckBox((*iter).mName);
				if ((*iter).mValue == std::string("T"))
					control->SetValue(true);
				else
					control->SetValue(false);

				TControlPair tCtrlPair;
				tCtrlPair.first = (*iter).mName;
				tCtrlPair.second = control;
				mCtrlList.push_back(tCtrlPair);
			}
		}
	}
	gEnv->MainFrame->mPropertyPage->Realize();
}

wxTextCtrl* CNodePropertyUI::CreateText(const std::string& name)
{
	CreateUIPanel();
	wxRibbonPanel* panel = gEnv->MainFrame->mPropertyPanel;
	wxStaticText* namelable = new wxStaticText(panel, wxID_ANY, wxString(name.c_str()) + wxString(": "));
	wxTextCtrl* control = new wxTextCtrl(panel, wxID_ANY);
	wxSizer* bundle = new wxBoxSizer(wxHORIZONTAL);
	bundle->Add(namelable);
	bundle->Add(control);
	mPropPanelSizer->Add(bundle);
	return control;
}

wxChoice* CNodePropertyUI::CreateChoice(const std::string& name)
{
	CreateUIPanel();
	wxRibbonPanel* panel = gEnv->MainFrame->mPropertyPanel;
	wxStaticText* namelable = new wxStaticText(panel, wxID_ANY, wxString(name.c_str()) + wxString(": "));
	wxChoice* control = new wxChoice(panel, wxID_ANY);
	wxSizer* bundle = new wxBoxSizer(wxHORIZONTAL);
	bundle->Add(namelable);
	bundle->Add(control);
	mPropPanelSizer->Add(bundle);
	return control;
}

wxCheckBox* CNodePropertyUI::CreateCheckBox(const std::string& name, bool default_value)
{
	CreateUIPanel();
	wxRibbonPanel* panel = gEnv->MainFrame->mPropertyPanel;
	wxCheckBox* control = new wxCheckBox(panel, wxID_ANY, wxString(name.c_str()));
	mPropPanelSizer->Add(control, 0);
	return control;
}

void CNodePropertyUI::CreateUIPanel()
{
	if (!gEnv->MainFrame->mPropertyPanel)
	{
		wxString name("Property");
		if (mTargetNode)
			name = name + " - " + mTargetNode->GetName().c_str();
		gEnv->MainFrame->mPropertyPanel = new wxRibbonPanel(gEnv->MainFrame->mPropertyPage, wxID_ANY, name);
		mPropPanelSizer = new wxBoxSizer(wxVERTICAL);
		gEnv->MainFrame->mPropertyPanel->SetSizer(mPropPanelSizer);
	}
}

void CNodePropertyUI::DestroyUI()
{
	if (gEnv->MainFrame->mPropertyPanel)
	{
		delete gEnv->MainFrame->mPropertyPanel;
		gEnv->MainFrame->mPropertyPanel = 0;
	}
}

void* CNodePropertyUI::FindInControlList(const std::string& propname)
{
	for (TControlList::iterator iter = mCtrlList.begin();
		iter != mCtrlList.end(); iter++)
	{
		if (propname == (*iter).first)
			return (*iter).second;
	}
	return 0;
}

