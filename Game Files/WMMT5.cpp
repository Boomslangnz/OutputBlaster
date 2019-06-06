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

#include "WMMT5.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE outputdata = *(BYTE *)(imageBase + 0x199F0CC);
	BYTE outputdata2 = *(BYTE *)(imageBase + 0x199F0CD);

	Outputs->SetValue(OutputLampView1, !!(outputdata & 0x08));
	Outputs->SetValue(OutputInterruption, !!(outputdata & 0x04));
	Outputs->SetValue(OutputLampRed, !!(outputdata2 & 0x80));
	Outputs->SetValue(OutputLampGreen, !!(outputdata2 & 0x40));
	Outputs->SetValue(OutputLampBlue, !!(outputdata2 & 0x20));
	if (outputdata2 >= 0xE0)
	{
		Outputs->SetValue(OutputLampWhite, 0x01);
	}
	else
	{
		Outputs->SetValue(OutputLampWhite, 0x00);
	}
	Outputs->SetValue(OutputSideLamp, !!(outputdata2 & 0x10));
}

void WMMT5::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "Wangan Midnight Maximum Tune 5";
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