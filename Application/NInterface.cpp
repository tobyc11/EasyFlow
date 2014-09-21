#include "NInterface.h"
#include <string.h>

UNodeRegister* UNodeRegister::sRegisterLink = 0;
int UNodeRegister::sIDCount = 0;

UNodeRegister::UNodeRegister(char* name, NodeFactory factory, char* description)
{
	this->mName = name;
	this->mDesc = description;
	this->mFactory = factory;
	this->mNext = sRegisterLink;
	sRegisterLink = this;
	this->mID = sIDCount;
	sIDCount++;
}

int UNodeRegister::GetID()
{
	return mID;
}

NNode* UNodeRegister::CreateNode(char* name)
{
	UNodeRegister* curr = sRegisterLink;
	while (curr != 0)
	{
		if (strcmp(name, curr->mName) == 0)
			return curr->mFactory();
		curr = curr->mNext;
	}
	return 0;
}

NNode* UNodeRegister::CreateNodeByID(int id)
{
	UNodeRegister* curr = sRegisterLink;
	while (curr != 0)
	{
		if (id == curr->mID)
			return curr->mFactory();
		curr = curr->mNext;
	}
	return 0;
}
