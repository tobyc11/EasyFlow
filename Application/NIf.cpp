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

#include "NIf.h"
#include "NodePropertyAccessor.h"
#include "Generator/Function.h"
#include "Generator/Utils.h"

REGISTER_NODE(NIf, "If statement")

NIf::NIf(UNodeRegister* type) : NNode(type)
{
	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "RFlag";
		prop.mType = "hT";
		prop.mValue = "RR";
		mPropTable.push_back(prop);
	}
	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "Statement";
		prop.mType = "T";
		prop.mValue = "true";
		mPropTable.push_back(prop);
	}
	// ADD YOUR OWN PROPERTIES HERE!
}

NIf::~NIf()
{

}

void NIf::GenerateCodeInto(ULinkedString* strThis, int indent)
{
	CNodePropertyAccessor propAcc;
	propAcc.SetTargetNode(this);
	std::string statement = propAcc.GetPropertyValue("Statement");
	strThis->Content += sIndent[INDENT_INDEX - 5];
	strThis->Content += "if(" + statement + ")\n";
	strThis->Content += sIndent[INDENT_INDEX - indent];
	strThis->Content += "{\n";

	CFunction* currFuction = (CFunction*)strThis->pMemMgr;
	ULinkedString* strNextNode = currFuction->AllocContent(strThis, strThis->mNext);
	ULinkedString* strMiddle = currFuction->AllocContent(strNextNode, strNextNode->mNext);

	NNode* sibling;
	if (sibling = GetSibling(NS_RIGHT))
	{
		sibling->GenerateCodeInto(strNextNode, indent + 1);
	}

	strMiddle->Content += sIndent[INDENT_INDEX - indent];
	strMiddle->Content += "}\n";

	if (sibling = GetSibling(NS_RIGHT2))
	{
		ULinkedString* strRight2 = currFuction->AllocContent(strMiddle, strMiddle->mNext);
		ULinkedString* strFinal = currFuction->AllocContent(strRight2, strRight2->mNext);
		strMiddle->Content += sIndent[INDENT_INDEX - indent];
		strMiddle->Content += "else\n";
		strMiddle->Content += sIndent[INDENT_INDEX - indent];
		strMiddle->Content += "{\n";
		sibling->GenerateCodeInto(strRight2, indent + 1);
		strFinal->Content += sIndent[INDENT_INDEX - indent];
		strFinal->Content += "}\n";
	}
}
