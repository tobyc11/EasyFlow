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

#include "Common.h"
#include "FlowGraph.h"
#include "NInterface.h"
#include "NNode.h"
#include "NEvent.h"
#include "NodePropertyAccessor.h"
#include "Generator/GeneratorContext.h"
#include <sstream>

int CFlowGraph::sUnnamedCount = 0;

CFlowGraph::CFlowGraph()
{
	gEnv->FlowGraph = this;
	mSpawningNode = 0;
}

CFlowGraph::~CFlowGraph()
{
	ClearAll();
}

void CFlowGraph::ClearAll()
{
	for (TNodeMap::iterator iter = mNodes.begin();
		iter != mNodes.end();
		iter++)
	{
		delete (*iter).second;
	}
	mNodes.clear();
}

NNode * CFlowGraph::StartSpawnNode(int id)
{
	if (mSpawningNode)
		return 0;
	NNode* thenode = UNodeRegister::sRegisterLink->CreateNodeByID(id);
	if (thenode == 0)
		return 0;
	thenode->Init(std::string("NewNode") + std::to_string(sUnnamedCount));
	sUnnamedCount++;
	mSpawningNode = thenode;
	return thenode;
}

NNode* CFlowGraph::GetSpawningNode()
{
	return mSpawningNode;
}

void CFlowGraph::SpawnNode(NNode* thenode)
{
	mSpawningNode = 0;
	mNodes[thenode->GetName()] = thenode;
}

void CFlowGraph::CancelSpawnNode()
{
	if (mSpawningNode)
		delete mSpawningNode;
	mSpawningNode = 0;
}

void CFlowGraph::ReadFromStatus(const char* statusText)
{
	ClearAll();
	std::istringstream inputStream(statusText);
	std::stringstream tempStream;
	std::string line, str0, str1;
	NNode* currNode;
	int stage = -1, int0, int1;
	while (std::getline(inputStream, line))
	{
		if (line == "#")
		{
			stage = 0;
			currNode = 0;
			continue;
		}
		if (stage == -1)
			return; // Shall never reach here

		switch (stage)
		{
		case 0:
			tempStream = std::stringstream(line);
			tempStream >> str0 >> str1 >> int0 >> int1;
			currNode = UNodeRegister::sRegisterLink->CreateNode(str1.c_str());
			currNode->Init(str0);
			currNode->SetPosition(int0, int1);
			mNodes[currNode->GetName()] = currNode;
			break;
		case 1:
			tempStream = std::stringstream(line);
			while (tempStream >> str0)
			{
				if (str0.c_str()[str0.length() - 1] == ':')
				{
					str1 = str0.substr(0, str0.length() - 1);
					continue;
				}

			}
			break;
		default:
			break;
		}
		stage++;
		//currNode = UNodeRegister::sRegisterLink->CreateNodeByID();
	}
}

const char* CFlowGraph::GetStatus()
{
	memset(mStatusText, 0, 4096);
	for (TNodeMap::iterator iter = mNodes.begin();
		iter != mNodes.end();
		iter++)
	{
		char curr[256];
		sprintf_s(curr, "#\n%s %s %d %d\n",
			(*iter).second->GetName().c_str(),
			(*iter).second->GetType()->mName,
			(*iter).second->GetX(),
			(*iter).second->GetY());
		strcat_s(mStatusText, curr);
		NNode* sibTest;
		if (sibTest = (*iter).second->GetSibling(NNode::NS_LEFT))
		{
			sprintf_s(curr, "LEFT: %s ", sibTest->GetName().c_str());
			strcat_s(mStatusText, curr);
		}
		if (sibTest = (*iter).second->GetSibling(NNode::NS_RIGHT))
		{
			sprintf_s(curr, "RIGHT: %s ", sibTest->GetName().c_str());
			strcat_s(mStatusText, curr);
		}
		if (sibTest = (*iter).second->GetSibling(NNode::NS_RIGHT2))
		{
			sprintf_s(curr, "RIGHT2: %s ", sibTest->GetName().c_str());
			strcat_s(mStatusText, curr);
		}
		if (sibTest = (*iter).second->GetSibling(NNode::NS_DOWN))
		{
			sprintf_s(curr, "DOWN: %s ", sibTest->GetName().c_str());
			strcat_s(mStatusText, curr);
		}
		sprintf_s(curr, "\n");
		strcat_s(mStatusText, curr);

		for (TPropTable::iterator iter2 = (*iter).second->mPropTable.begin();
			iter2 != (*iter).second->mPropTable.end(); iter2++)
		{
			sprintf_s(curr, "%s %s %s\n", (*iter2).mName.c_str(),
				(*iter2).mType.c_str(), (*iter2).mValue.c_str());
			strcat_s(mStatusText, curr);
		}

		//sprintf_s(curr, "\n");
		//strcat_s(mStatusText, curr);
	}
	return mStatusText;
}

const char* CFlowGraph::GenerateCode()
{
	CGeneratorContext* genContext = new CGeneratorContext();
	CMainTask* mainTask = genContext->InitMainTask(CGeneratorContext::MAIN_ITERATE_ALL_EVENTS);
	gEnv->GeneratorContext = genContext;

	CNodePropertyAccessor propAcc;
	for (TNodeMap::iterator iter = mNodes.begin();
		iter != mNodes.end();
		iter++)
	{
		propAcc.SetTargetNode((*iter).second);
		std::string& value = propAcc.GetPropertyValue("CFlag");
		if (value != std::string("E"))
			continue;

		// This node has property CFlag == E
		// Assume that it is an Event Node
		// Start generating!!!
		// NEvent* eventNode = static_cast<NEvent*>((*iter).second);
		NNode* eventNode = static_cast<NNode*>((*iter).second);
		eventNode->GenerateCode();
	}

	const char* pCode = genContext->ReturnCode();
	mCode = std::string("Failed");
	if (pCode)
		mCode = std::string(pCode);
	gEnv->GeneratorContext = 0;
	delete genContext;
	return mCode.c_str();
}
