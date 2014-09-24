#pragma once
#include "wx/wx.h"
#include "NodePropertyAccessor.h"
#include <vector>

class CNodePropertyUI : public CNodePropertyAccessor
{
public:
	CNodePropertyUI();
	~CNodePropertyUI();

	void UpdatePropertiesFromTarget();
	bool UpdateTarget();

	// Helpers for GUI (Creating ribbon elements to edit props)
	void CreateUI();
	wxTextCtrl* CreateText(const std::string& name);
	wxChoice* CreateChoice(const std::string& name);
	wxCheckBox* CreateCheckBox(const std::string& name, bool default_value = false);
	void CreateUIPanel();
	void DestroyUI();
	void* FindInControlList(const std::string& propname);

private:
	typedef std::pair<std::string, void*> TControlPair;
	typedef std::vector<TControlPair> TControlList;
	wxSizer* mPropPanelSizer;
	wxTextCtrl* mNameCtrl;
	TControlList mCtrlList;
};
