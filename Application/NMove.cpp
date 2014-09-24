#include "NMove.h"

REGISTER_NODE(NMove, "Control Motion")

NMove::NMove(UNodeRegister* type) : NNode(type)
{
	// User modifiable code
	// Add properties
	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "Time";
		prop.mType = "T"; // T:Text (D:Dropdown Menu) C:CheckBox
		prop.mValue = "1000";
		mPropTable.push_back(prop);
	}
	{
		CNodeProperty prop;
		prop.mOwner = this;
		prop.mName = "Power";
		prop.mType = "T";
		prop.mValue = "100";
		mPropTable.push_back(prop);
	}
}

NMove::~NMove()
{

}
