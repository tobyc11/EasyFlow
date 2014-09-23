#pragma once
#define APP_NAME "EasyFlow"
#define APP_VERSION "0.1 Alpha"

class CMainFrame;
class CFlowGraph;
class CFlowEditor;
class CToolBox;
struct CGlobalEnvironment
{
	CMainFrame* MainFrame;
	CToolBox* ToolBox;
	CFlowGraph* FlowGraph;
	CFlowEditor* FlowEditor;
};

extern CGlobalEnvironment* gEnv;
