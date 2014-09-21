#include "FlowGraph.h"
#include "NInterface.h"
#include "NNode.h"

int CFlowGraph::sUnnamedCount = 0;

CFlowGraph::CFlowGraph()
{
	mSpawningNode = 0;
}

CFlowGraph::~CFlowGraph()
{

}

void CFlowGraph::BindEditor(CFlowEditor* ed)
{
	mEditor = ed;
}

CFlowEditor* CFlowGraph::GetEditor()
{
	return mEditor;
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
}

void CFlowGraph::CancelSpawnNode()
{
	if (mSpawningNode)
		delete mSpawningNode;
	mSpawningNode = 0;
}
