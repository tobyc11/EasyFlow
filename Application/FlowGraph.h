#pragma once
#include <unordered_map>

class CFlowEditor;
class NNode;
class CFlowGraph
{
public:
	CFlowGraph();
	~CFlowGraph();
	void BindEditor(CFlowEditor*);
	CFlowEditor* GetEditor();
	//void UpdateEditor();

	NNode* StartSpawnNode(int id);
	NNode* GetSpawningNode();
	void SpawnNode(NNode*);
	void CancelSpawnNode();

	const char* GetStatus();
	const char* GenerateCode();

private:
	typedef std::unordered_map < std::string, NNode* > TNodeMap;
	static int sUnnamedCount;
	CFlowEditor* mEditor;
	TNodeMap mNodes;
	NNode* mSpawningNode;
	char mStatusText[4096];
};
