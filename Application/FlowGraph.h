#pragma once

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

private:
	static int sUnnamedCount;
	CFlowEditor* mEditor;
	NNode* mNodes;
	NNode* mSpawningNode;
};
