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

CGeneratorContext::CGeneratorContext()
{
	mMainTask = 0;
}

CGeneratorContext::~CGeneratorContext()
{
	if (mMainTask)
		delete mMainTask;
}

CMainTask* CGeneratorContext::InitMainTask(int mainTaskType)
{
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

}

CGlobalVar* CGeneratorContext::AddGlobalVar(const char* type, const char* name)
{

}

const char* CGeneratorContext::ReturnCode()
{

}
