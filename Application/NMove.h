#pragma once
#include "NNode.h"

class NMove : public NNode
{
public:
	NMove(UNodeRegister* type);
	~NMove();
private:
	NMove();
};
