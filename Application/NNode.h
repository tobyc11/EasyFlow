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
#include "Common.h"
#include "NInterface.h"
#include <string>
#include <vector>

struct CNodeProperty
{
public:
	NNode* mOwner;
	std::string mName;
	std::string mType;
	std::string mValue;
};

typedef std::vector<CNodeProperty> TPropTable;

class ULinkedString;
class NNode
{
public:
	enum SIBLING_ID
	{
		NS_LEFT = 0,
		NS_RIGHT,
		NS_DOWN
	};

	NNode(UNodeRegister* type);
	~NNode();
	bool Init(std::string& name);
	void SetPosition(int x, int y);
	int GetX();
	int GetY();
	void SetName(const std::string& name);
	std::string& GetName();
	UNodeRegister* GetType();

	virtual NNode* GetSibling(int sib);
	virtual void SetSibling(int sib, NNode* value);
	virtual void GenerateCode();
	virtual void GenerateCodeInto(ULinkedString* strThis, int indent);

	//Make the property table public so that CPropertyController can access it
	TPropTable mPropTable;

protected:
	UNodeRegister* mType;
	std::string mName;
	int mX, mY;
	NNode *mLeftSib, *mRightSib, *mDownSib;

#define INDENT_INDEX 16
	static const char* sIndent;
};
