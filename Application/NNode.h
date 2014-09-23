#pragma once
#include "NInterface.h"
#include <string>

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
	bool Init(std::string& name, int x, int y);
	void SetPosition(int x, int y);
	int GetX();
	int GetY();
	std::string& GetName();
	UNodeRegister* GetType();

	virtual NNode* GetSibling(int sib);
	virtual void SetSibling(int sib, NNode* value);
	virtual std::string GenerateCode();

protected:
	UNodeRegister* mType;
	std::string mName;
	int mX, mY;
	NNode *mLeftSib, *mRightSib, *mDownSib;

private:
};
