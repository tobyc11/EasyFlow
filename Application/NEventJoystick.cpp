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

#include "NEventJoystick.h"
#include "Generator/GeneratorContext.h"
#include "Generator/Function.h"

REGISTER_NODE(NEventJoystick, "The only entry point currently")

NEventJoystick::NEventJoystick(UNodeRegister* type) : NEvent(type)
{
	// User modifiable code
	// Add properties
	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "Button";
		prop.mType = "T";
		prop.mValue = "BtnU8";
		mPropTable.push_back(prop);
	}
}

NEventJoystick::~NEventJoystick()
{

}

void NEventJoystick::GenerateCode()
{
	// NEvent::GenerateCode();
	std::string fName = std::string("Listener_") + this->mName;
	CFunction* eventFunc = gEnv->GeneratorContext->AddFunction(fName.c_str());
	gEnv->GeneratorContext->GetMainTask()->AddEventListener(eventFunc);
	eventFunc->SetReturnType("void");
	ULinkedString* insideFunction = eventFunc->GenerateStub();

	NNode* sibling;
	if (sibling = GetSibling(NS_RIGHT))
	{
		sibling->GenerateCodeInto(insideFunction);
	}
}
