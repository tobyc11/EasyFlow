#include <Main\Common.h>
#include "FlowGraph.h"
#include "NInterface.h"
#include "NNode.h"

int CFlowGraph::sUnnamedCount = 0;

CFlowGraph::CFlowGraph()
{
	gEnv->FlowGraph = this;
	mSpawningNode = 0;
}

CFlowGraph::~CFlowGraph()
{

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

const char* CFlowGraph::GetStatus()
{
	memset(mStatusText, 0, 4096);
	for (TNodeMap::iterator iter = mNodes.begin();
		iter != mNodes.end();
		iter++)
	{
		char curr[256];
		sprintf_s(curr, "%s %s %d %d\n",
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
			sprintf_s(curr, "%s ", (*iter2).mValue.c_str());
			strcat_s(mStatusText, curr);
		}

		sprintf_s(curr, "\n");
		strcat_s(mStatusText, curr);
	}
	return mStatusText;
}

const char* CFlowGraph::GenerateCode()
{

	return 0;
}
