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

#include "GeneratorContext.h"
#include "GlobalVar.h"
#include "Function.h"

CMainTask::CMainTask()
{

}

CMainTask::~CMainTask()
{

}

void CMainTask::AddEventListener(CFunction* funcListener)
{

}

const char* CMainTask::ReturnCode()
{
	return mCodeBuffer.c_str();
}

CGeneratorContext::CGeneratorContext()
{
	mMainTask = 0;
}

CGeneratorContext::~CGeneratorContext()
{
	if (mMainTask)
		delete mMainTask;
	ReleaseFunctions();
	ReleaseGlobalVars();
}

CMainTask* CGeneratorContext::InitMainTask(int mainTaskType)
{
	mFunctions.clear();
	mGlobalVars.clear();
	if (mainTaskType == MAIN_ITERATE_ALL_EVENTS)
	{
		mMainTask = new CMainTask();
		return mMainTask;
	}
	mMainTask = 0;
	return 0;
}

CFunction* CGeneratorContext::AddFunction(const char* name)
{
	CFunction* function = new CFunction();
	function->SetName(name);
	mFunctions.push_back(function);
	return function;
}

CGlobalVar* CGeneratorContext::AddGlobalVar(const char* type, const char* name)
{
	CGlobalVar* gvar = new CGlobalVar();
	mGlobalVars.push_back(gvar);
	return 0;
}

const char* CGeneratorContext::ReturnCode()
{
	mCodeBuffer = std::string();

	// Generate code for global variables
	for (TLGlobalVar::iterator iter = mGlobalVars.begin();
		iter != mGlobalVars.end(); iter++)
	{

	}

	// Generate code for functions
	for (TLFunction::iterator iter = mFunctions.begin();
		iter != mFunctions.end(); iter++)
	{
		mCodeBuffer += (*iter)->ReturnCode();
	}

	// Generate main task

	return mCodeBuffer.c_str();
}

void CGeneratorContext::ReleaseFunctions()
{
	for (TLFunction::iterator iter = mFunctions.begin();
		iter != mFunctions.end(); iter++)
	{
		delete (*iter);
	}
	mFunctions.clear();
}

void CGeneratorContext::ReleaseGlobalVars()
{
	for (TLGlobalVar::iterator iter = mGlobalVars.begin();
		iter != mGlobalVars.end(); iter++)
	{
		delete (*iter);
	}
	mGlobalVars.clear();
}
