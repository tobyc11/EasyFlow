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

#include "Utils.h"

ULinkedString::ULinkedString(ULinkedString* pPrev, ULinkedString* pNext)
{
	mPrev = pPrev;
	mNext = pNext;
	if (mPrev)
		mPrev->mNext = this;
	if (mNext)
		mNext->mPrev = this;
}

ULinkedString::~ULinkedString()
{
	Remove();
}

//ULinkedString* ULinkedString::InsertBefore()
//{
//	
//}
//
//ULinkedString* ULinkedString::InsertAfter()
//{
//
//}

const char* ULinkedString::Read()
{
	return Content.c_str();
}

void ULinkedString::Write(const char* content)
{
	Content = std::string(content);
}

void ULinkedString::Remove()
{
	if (mPrev)
		mPrev->mNext = this->mNext;
	if (mNext)
		mNext->mPrev = this->mPrev;
	mPrev = 0;
	mNext = 0;
}
