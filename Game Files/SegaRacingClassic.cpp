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

#include "SegaRacingClassic.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE data = *(BYTE *)(imageBase + 0x434C18);
	Outputs->SetValue(OutputLampStart, !!(data & 0x04));
	Outputs->SetValue(OutputLampView1, !!(data & 0x08));
	Outputs->SetValue(OutputLampView2, !!(data & 0x40));
	Outputs->SetValue(OutputLampView3, !!(data & 0x10));
	Outputs->SetValue(OutputLampView4, !!(data & 0x80));
	Outputs->SetValue(OutputLampLeader, !!(data & 0x20));
	Outputs->SetValue(OutputRawLamps, data);
}

void SegaRacingClassic::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "Sega Racing Classic";
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