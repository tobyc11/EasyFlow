#include "NNode.h"

REGISTER_NODE(NNode, "Basic Node");

NNode::NNode()
{

}

NNode::~NNode()
{

}

bool NNode::Init(std::string& name)
{
	mName = name;
	return true;
}

bool NNode::Init(std::string& name, int x, int y)
{
	if (!Init(name))
		return false;
	SetPosition(x, y);
	return true;
}

void NNode::SetPosition(int x, int y)
{
	mX = x;
	mY = y;
}

int NNode::GetX()
{
	return mX;
}

int NNode::GetY()
{
	return mY;
}

std::string& NNode::GetName()
{
	return mName;
}

