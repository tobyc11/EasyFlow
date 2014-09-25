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

#include "NNode.h"

REGISTER_NODE(NNode, "Basic Node/Does nothing");

//NNode::NNode()
//{
//	mLeftSib = mRightSib = mDownSib = 0;
//}

NNode::NNode(UNodeRegister* type)
{
	mType = type;
	mLeftSib = mRightSib = mDownSib = 0;
}

NNode::~NNode()
{

}

bool NNode::Init(std::string& name)
{
	mName = name;

	// User modifiable code
	// Add properties
	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "Enable";
		prop.mType = "C"; // T:Text (D:Dropdown Menu) C:CheckBox
		prop.mValue = "T"; // T: true F: false
		mPropTable.push_back(prop);
	}
	return true;
}

void NNode::SetPosition(int x, int y)
{
	mX = x;
	mY = y;
}

int NNode::GetX()
{
	return mX;
}

int NNode::GetY()
{
	return mY;
}

void NNode::SetName(const std::string& name)
{
	mName = name;
}

std::string& NNode::GetName()
{
	return mName;
}

UNodeRegister* NNode::GetType()
{
	return mType;
}

NNode* NNode::GetSibling(int sib)
{
	switch (sib)
	{
	case NS_LEFT:
		return mLeftSib;
	case NS_RIGHT:
		return mRightSib;
	case NS_DOWN:
		return mDownSib;
	default:
		return 0;
	}
}

void NNode::SetSibling(int sib, NNode* value)
{
	switch (sib)
	{
	case NS_LEFT:
		mLeftSib = value;
		break;
	case NS_RIGHT:
		mRightSib = value;
		break;
	case NS_DOWN:
		mDownSib = value;
		break;
	default:
		break;
	}
	return;
}

std::string NNode::GenerateCode()
{
	return std::string("");
}
