/*This file is part of Output Blaster.

Output Blaster is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Output Blaster is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Output Blaster.If not, see < https://www.gnu.org/licenses/>.*/

#include "GTIClubSuperminiFesta.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	BYTE actiondata = *(BYTE *)(0xA7E794);
	BYTE startdata = *(BYTE *)(0xA7E790);
	BYTE view1data = *(BYTE *)(0xA7E7A0);
	BYTE view2data = *(BYTE *)(0xA7E7A4);
	BYTE view3data = *(BYTE *)(0xA7E798);
	BYTE view4data = *(BYTE *)(0xA7E79C);

	Outputs->SetValue(OutputLampLeader, !!(actiondata & 0x1F));
	Outputs->SetValue(OutputLampStart, !!(startdata & 0x1F));
	Outputs->SetValue(OutputLampView1, !!(view1data & 0x1F));
	Outputs->SetValue(OutputLampView2, !!(view2data & 0x1F));
	Outputs->SetValue(OutputLampView3, !!(view3data & 0x1F));
	Outputs->SetValue(OutputLampView4, !!(view4data & 0x1F));
}

void GTIClubSuperminiFesta::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "GTI Club Supermini Festa";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		SetTimer(0, 0, Output_Time, (TIMERPROC)OutputsAreGo);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}