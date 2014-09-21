#include "NMove.h"

REGISTER_NODE(NMove, "Control Motion")

NMove::NMove(UNodeRegister* type)
{
	mType = type;
}

NMove::~NMove()
{

}
