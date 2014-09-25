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

class CFunction;
class CGlobalVar;

class CMainTask
{
public:
	CMainTask();
	~CMainTask();
};

class CGeneratorContext
{
public:
	enum
	{
		MAIN_ITERATE_ALL_EVENTS = 0
	};

	CGeneratorContext();
	~CGeneratorContext();

	CMainTask* InitMainTask(int mainTaskType);
	CFunction* AddFunction(const char* name);
	CGlobalVar* AddGlobalVar(const char* type, const char* name);
	// bool AddPortDefinition();

	const char* ReturnCode();

private:
	CMainTask* mMainTask;
};
