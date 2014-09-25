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
