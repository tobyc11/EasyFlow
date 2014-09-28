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
#include "NodePropertyAccessor.h"

CNodePropertyAccessor::CNodePropertyAccessor()
{
	mTargetNode = 0;
	mErrorStr = std::string(ERROR_STRING);
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
	return mErrorStr;
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

