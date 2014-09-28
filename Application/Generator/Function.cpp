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

#include "Function.h"
#include "Utils.h"

CFunction::CFunction()
{
	int i;
	for (i = 0; i < MAX_STRING_FRAGMENTS; i++)
	{
		mContents[i] = 0;
	}
}

CFunction::~CFunction()
{
	int i;
	for (i = 0; i < MAX_STRING_FRAGMENTS; i++)
	{
		DeleteContent(i);
	}
}

void CFunction::SetName(const char* name)
{
	mName = std::string(name);
}

void CFunction::SetReturnType(const char* returnType)
{
	mReturnType = std::string(returnType);
}

ULinkedString* CFunction::AllocContent(ULinkedString* prev /*= 0*/, ULinkedString* next /*= 0*/)
{
	ULinkedString* temp = new ULinkedString(prev, next);
	int i;
	for (i = 0; i < MAX_STRING_FRAGMENTS; i++)
		if (mContents[i] == 0)
		{
			mContents[i] = temp;
			break;
		}

	// I omitted checking for MAX_STRING_FRAGMENTS
	// cause I think it will never overflow
	return temp;
}

void CFunction::DeleteContent(ULinkedString* pContent)
{
	int i;
	for (i = 0; i < MAX_STRING_FRAGMENTS; i++)
	{
		if (mContents[i] == pContent)
			DeleteContent(i);
	}
}

void CFunction::DeleteContent(int index)
{
	if (mContents[index])
	{
		delete mContents[index];
		mContents[index] = 0;
	}
}

ULinkedString* CFunction::GenerateStub()
{
	// Make sure there is nothing present
	int i;
	for (i = 0; i < MAX_STRING_FRAGMENTS; i++)
	{
		DeleteContent(i);
	}

	ULinkedString* strHead = AllocContent(0, 0);
	ULinkedString* strEnd = AllocContent(strHead, 0);
	
	// Start filling in them
	strHead->Content = "\n" + mReturnType + " " + mName + "()\n{\n";
	strEnd->Content = "}\n";

	ULinkedString* realcontent = AllocContent(strHead, strEnd);
	return realcontent;
}

const char* CFunction::ReturnCode()
{
	// We fill in mContents from 0 -> MAX
	// so if there is nothing inside [0], there is nothing
	if (mContents[0] == NULL)
		return 0;
	ULinkedString* currObj = mContents[0];
	while (currObj->mPrev != 0)
		currObj = currObj->mPrev;

	// Now do it
	mCodeBuffer += currObj->Content;
	do 
	{
		currObj = currObj->mNext;
		mCodeBuffer += currObj->Content;
	} while (currObj->mNext != 0);
	return mCodeBuffer.c_str();
}
