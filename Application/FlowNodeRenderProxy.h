/*
This file is part of EasyFlow.

EasyFlow is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

EasyFlow is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with EasyFlow. If not, see <http://www.gnu.org/licenses/>.

Author: Toby Chen @ 2014
*/

#pragma once
#include <wx/wx.h>

class CFlowEditor;
class NNode;

struct SRenderEvtParams
{
	enum ERenderEvents
	{
		RE_MOUSE_OVER = 0,
		RE_LEFT_DOWN,
		RE_LEFT_UP,
		RE_RIGHT_DOWN,
		RE_RIGHT_UP,
		RE_MOUSE_MOVE
	} evt;
	int x;
	int y;
};

class CFlowNodeRenderProxy
{
private:
	CFlowNodeRenderProxy();
public:
	CFlowNodeRenderProxy(CFlowEditor* parent, NNode* node);
	~CFlowNodeRenderProxy();
	NNode* GetNNode();
	void Render();
	void Render(wxDC& dc);
	void SetHighlightPen(wxDC& dc, bool hi);
	bool PointInside(int x, int y);

	void ProcessEvents(SRenderEvtParams params);
	int DeterminePart(int x, int y);
	wxPoint GetSocketCenter(int NNodeSocket);

private:
	enum EParts
	{
		PART_UNKNOWN = 0,
		PART_S_LEFT,
		PART_S_RIGHT,
		PART_S_DOWN,
		PART_TITLE,
		PART_BODY
	};

	CFlowEditor* mParent;
	NNode* mNode;

	bool mHighlightLeft;
	bool mHighlightRight;
	bool mHighlightAll;
	wxPoint mMouseWndPos;
};
