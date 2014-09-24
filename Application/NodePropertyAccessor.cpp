#include "Common.h"
#include "NodePropertyAccessor.h"

CNodePropertyAccessor::CNodePropertyAccessor()
{
	mTargetNode = 0;
}

CNodePropertyAccessor::~CNodePropertyAccessor()
{

}

void CNodePropertyAccessor::SetTargetNode(NNode* node)
{
	mTargetNode = node;
}

TPropTable& CNodePropertyAccessor::GetPropTable()
{
	if (mTargetNode)
	{
		return mTargetNode->mPropTable;
	}
	//assert(1); // BUG!!!
	return mTargetNode->mPropTable;
}

std::string& CNodePropertyAccessor::GetPropertyValue(const std::string& name)
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
	//assert(1); // BUUUUGGGGG!!!
	return const_cast<std::string&>(name);
}

bool CNodePropertyAccessor::SetPropertyValue(const std::string& name, const std::string& value)
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

