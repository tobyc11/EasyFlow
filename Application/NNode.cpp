#include "NNode.h"

REGISTER_NODE(NNode, "Basic Node/Does nothing");

//NNode::NNode()
//{
//	mLeftSib = mRightSib = mDownSib = 0;
//}

NNode::NNode(UNodeRegister* type)
{
	mType = type;
	mLeftSib = mRightSib = mDownSib = 0;
}

NNode::~NNode()
{

}

bool NNode::Init(std::string& name)
{
	mName = name;

	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "TestProp";
		prop.mType = "T"; // T:Text D:Dropdown Menu C:CheckBox
		prop.mValue = "";
		mPropTable.push_back(prop);
	}

	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "TP2";
		prop.mType = "C"; // T:Text D:Dropdown Menu C:CheckBox
		prop.mValue = "F";
		mPropTable.push_back(prop);
	}

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

UNodeRegister* NNode::GetType()
{
	return mType;
}

NNode* NNode::GetSibling(int sib)
{
	switch (sib)
	{
	case NS_LEFT:
		return mLeftSib;
	case NS_RIGHT:
		return mRightSib;
	case NS_DOWN:
		return mDownSib;
	default:
		return 0;
	}
}

void NNode::SetSibling(int sib, NNode* value)
{
	switch (sib)
	{
	case NS_LEFT:
		mLeftSib = value;
		break;
	case NS_RIGHT:
		mRightSib = value;
		break;
	case NS_DOWN:
		mDownSib = value;
		break;
	default:
		break;
	}
	return;
}

std::string NNode::GenerateCode()
{
	return std::string("");
}
