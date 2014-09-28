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
#include "../Common.h"
#include <string>

class ULinkedString;
class CFunction
{
public:
	CFunction();
	~CFunction();

	void SetName(const char*);
	inline const char* GetName() {	return mName.c_str(); }
	void SetReturnType(const char*);
	inline const char* GetReturnType() { return mReturnType.c_str(); }

	ULinkedString* AllocContent(ULinkedString* prev = 0, ULinkedString* next = 0);
	void DeleteContent(ULinkedString* pContent);
	void DeleteContent(int index);

	// To generate things like
	// int BluhBluh()
	// {}
	ULinkedString* GenerateStub();

	const char* ReturnCode();
private:
	std::string mName, mReturnType;
	std::string mCodeBuffer;
	ULinkedString* mContents[MAX_STRING_FRAGMENTS];
};
