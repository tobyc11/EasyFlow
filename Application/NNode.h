#pragma once
#include "NInterface.h"
#include <string>

class NNode
{
public:
	NNode();
	NNode(UNodeRegister* type);
	~NNode();
	bool Init(std::string& name);
	bool Init(std::string& name, int x, int y);
	void SetPosition(int x, int y);
	int GetX();
	int GetY();
	std::string& GetName();
	UNodeRegister* GetType();
protected:
	UNodeRegister* mType;
	std::string mName;
	int mX, mY;
private:
};
