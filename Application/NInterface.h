#pragma once

class NNode;
class UNodeRegister
{
public:
	typedef NNode* (*NodeFactory)();
	UNodeRegister(char* name, NodeFactory factory, char* description);
	int GetID();
	NNode* CreateNode(char* name);
	NNode* CreateNodeByID(int id);
public:
	static UNodeRegister* sRegisterLink;
	static int sIDCount;
	char* mName, *mDesc;
	int mID;
	NodeFactory mFactory;
	UNodeRegister* mNext;
};

#define REGISTER_NODE(classname, description) \
	NNode* classname##Factory() { return new classname; } \
	UNodeRegister classname##Register(#classname, classname##Factory, description);
