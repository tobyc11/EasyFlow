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
#include <unordered_map>

class NNode;
class CFlowGraph
{
public:
	CFlowGraph();
	~CFlowGraph();
	void ClearAll();

	NNode* StartSpawnNode(int id);
	NNode* GetSpawningNode();
	void SpawnNode(NNode*);
	void CancelSpawnNode();

	void ReadFromStatus(const char* statusText);
	const char* GetStatus();
	const char* GenerateCode();

private:
	typedef std::unordered_map < std::string, NNode* > TNodeMap;
	static int sUnnamedCount;
	TNodeMap mNodes;
	NNode* mSpawningNode;
	char mStatusText[4096];
	std::string mCode;
};
