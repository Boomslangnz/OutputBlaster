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

#include "DaytonaChampionshipUSA.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE startdata = *(BYTE *)(imageBase + 0x11AF464);
	BYTE view1data = *(BYTE *)(imageBase + 0x11AF478);
	BYTE view2data = *(BYTE *)(imageBase + 0x11AF48C);
	BYTE view3data = *(BYTE *)(imageBase + 0x11AF4A0);
	BYTE view4data = *(BYTE *)(imageBase + 0x11AF4B4);
	Outputs->SetValue(OutputLampStart, !!(startdata & 0x01));
	Outputs->SetValue(OutputLampView1, !!(view1data & 0x01));
	Outputs->SetValue(OutputLampView2, !!(view2data & 0x01));
	Outputs->SetValue(OutputLampView3, !!(view3data & 0x01));
	Outputs->SetValue(OutputLampView4, !!(view4data & 0x01));
}

void DaytonaChampionshipUSA::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "Daytona Championship USA";
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