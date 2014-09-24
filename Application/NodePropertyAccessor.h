#pragma once
#include <string>
#include "NNode.h"

class CNodePropertyAccessor
{
public:
	CNodePropertyAccessor();
	~CNodePropertyAccessor();

	void SetTargetNode(NNode* node);
	NNode* GetTargetNode() { return mTargetNode; }

	TPropTable& GetPropTable();
	std::string& GetPropertyValue(const std::string& name);
	bool SetPropertyValue(const std::string& name, const std::string& value);
protected:
	NNode* mTargetNode;
};
