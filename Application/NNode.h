#pragma once
#include "NInterface.h"
#include <string>
#include <vector>

struct CNodeProperty
{
public:
	NNode* mOwner;
	std::string mName;
	std::string mType;
	std::string mValue;
};

typedef std::vector<CNodeProperty> TPropTable;

class NNode
{
public:
	enum SIBLING_ID
	{
		NS_LEFT = 0,
		NS_RIGHT,
		NS_DOWN
	};

	NNode(UNodeRegister* type);
	~NNode();
	bool Init(std::string& name);
	void SetPosition(int x, int y);
	int GetX();
	int GetY();
	std::string& GetName();
	UNodeRegister* GetType();

	virtual NNode* GetSibling(int sib);
	virtual void SetSibling(int sib, NNode* value);
	virtual std::string GenerateCode();

	//Make the property table public so that CPropertyController can access it
	TPropTable mPropTable;

protected:
	UNodeRegister* mType;
	std::string mName;
	int mX, mY;
	NNode *mLeftSib, *mRightSib, *mDownSib;
};
