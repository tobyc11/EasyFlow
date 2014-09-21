#pragma once
#include <wx/wx.h>

class CMainFrame;
class CApplication : public wxApp
{
public:
	bool mRenderOn;
	void OnIdle(wxIdleEvent& evt);
	void ActivateRenderLoop(bool on);

	virtual bool OnInit();

private:
	CMainFrame* mMainFrame;
};
