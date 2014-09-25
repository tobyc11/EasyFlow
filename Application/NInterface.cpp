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

#include "NInterface.h"
#include <string.h>

UNodeRegister* UNodeRegister::sRegisterLink = 0;
int UNodeRegister::sIDCount = 0;

UNodeRegister::UNodeRegister(char* name, NodeFactory factory, char* description)
{
	this->mName = name;
	this->mDesc = description;
	this->mFactory = factory;
	this->mNext = sRegisterLink;
	sRegisterLink = this;
	this->mID = sIDCount;
	sIDCount++;
}

int UNodeRegister::GetID()
{
	return mID;
}

NNode* UNodeRegister::CreateNode(char* name)
{
	UNodeRegister* curr = sRegisterLink;
	while (curr != 0)
	{
		if (strcmp(name, curr->mName) == 0)
			return curr->mFactory();
		curr = curr->mNext;
	}
	return 0;
}

NNode* UNodeRegister::CreateNodeByID(int id)
{
	UNodeRegister* curr = sRegisterLink;
	while (curr != 0)
	{
		if (id == curr->mID)
			return curr->mFactory();
		curr = curr->mNext;
	}
	return 0;
}
