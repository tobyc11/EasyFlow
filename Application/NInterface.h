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

class NNode;
class UNodeRegister
{
public:
	typedef NNode* (*NodeFactory)();
	UNodeRegister(char* name, NodeFactory factory, char* description);
	int GetID();
	NNode* CreateNode(char* name);
	NNode* CreateNodeByID(int id);
public:
	static UNodeRegister* sRegisterLink;
	static int sIDCount;
	char* mName, *mDesc;
	int mID;
	NodeFactory mFactory;
	UNodeRegister* mNext;
};

#define REGISTER_NODE(classname, description) \
	NNode* classname##Factory(); \
	UNodeRegister classname##Register(#classname, classname##Factory, description); \
	NNode* classname##Factory() { return new classname(&classname##Register); }
