#include <Main/Common.h>
#include "Application.h"
#include "MainFrame.h"

CGlobalEnvironment sEnv;
CGlobalEnvironment* gEnv = &sEnv;

wxIMPLEMENT_APP(CApplication);

bool CApplication::OnInit()
{
	mRenderOn = false;
	mMainFrame = new CMainFrame();
	mMainFrame->Show();
	//ActivateRenderLoop(true);
	return true;
}

void CApplication::ActivateRenderLoop(bool on)
{
	//if (on && !mRenderOn)
	//{
	//	Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(CApplication::OnIdle));
	//	mRenderOn = true;
	//}
	//else if (!on && mRenderOn)
	//{
	//	Disconnect(wxEVT_IDLE, wxIdleEventHandler(CApplication::OnIdle));
	//	mRenderOn = false;
	//}
}

void CApplication::OnIdle(wxIdleEvent& evt)
{
	if (mRenderOn)
	{
		mMainFrame->PaintFlowEditor();
		evt.RequestMore();
	}
}
