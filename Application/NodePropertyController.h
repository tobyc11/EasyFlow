#pragma once
#include "wx/wx.h"
#include <string>
#include <vector>
#include "NNode.h"

class CNodePropertyController
{
public:

	CNodePropertyController();
	~CNodePropertyController();

	void SetTargetNode(NNode* node);
	NNode* GetTargetNode() { return mTargetNode; }
	bool GetOutdated() { return mOutdated; }

	void UpdatePropertiesFromTarget();
	bool UpdateTarget();
	TPropTable& GetAvailableProps();
	std::string& GetPropertyValue(const std::string& name);
	bool SetPropertyValue(const std::string& name, const std::string& value);

	// Helpers for GUI (Creating ribbon elements to edit props)
	wxTextCtrl* CreateText(const std::string& name);
	wxChoice* CreateChoice(const std::string& name);
	wxCheckBox* CreateCheckBox(const std::string& name, bool default_value = false);
	void CreateUIPanel();
	void DestroyUI();

private:
	void SetOutdated(bool value) { mOutdated = value; }

	bool mOutdated;
	NNode* mTargetNode;

	int mRowXPos[3], mRowCount;
};
