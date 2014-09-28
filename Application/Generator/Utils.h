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
#include <string>

// Linked string class to help code generation
class ULinkedString
{
	friend class CFunction;
public:

	// Constructor: 0 as NULL
	//ULinkedString* InsertBefore();
	//ULinkedString* InsertAfter();

	std::string Content;

	// C Wrappers to avoid problematic C++ STL
	const char* Read();
	void Write(const char* content);
private:
	ULinkedString(ULinkedString* pPrev, ULinkedString* pNext);
	~ULinkedString();

	// You don't need to call this directly, destructor does it
	void Remove();
	ULinkedString *mPrev, *mNext;
};
