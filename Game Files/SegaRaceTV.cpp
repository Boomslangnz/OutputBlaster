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

#include "SegaRaceTV.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	INT_PTR outputdataBase1 = *(INT_PTR *)(imageBase + 0x731F70);
	INT_PTR outputdataBase2 = *(INT_PTR *)(outputdataBase1 + 0x21C);
	INT_PTR outputdataBase3 = *(INT_PTR *)(outputdataBase2 + 0x78);
	INT_PTR outputdataBase4 = *(INT_PTR *)(outputdataBase3 + 0x180);
	INT_PTR outputdataBase5 = *(INT_PTR *)(outputdataBase4 + 0x4E0);
	BYTE outputdataBase6 = *(BYTE *)(outputdataBase5 + 0xC);
	BYTE outputdataBase7 = *(BYTE *)(outputdataBase5 + 0xD);

	Outputs->SetValue(OutputLampStart, !!(outputdataBase6 & 0x80));
	Outputs->SetValue(OutputLampView1, !!(outputdataBase6 & 0x8));
	Outputs->SetValue(OutputBoost, !!(outputdataBase6 & 0x10));
	Outputs->SetValue(OutputLampRed, !!(outputdataBase6 & 0x1));
	Outputs->SetValue(OutputLampRed2, !!(outputdataBase7 & 0x40));
	Outputs->SetValue(OutputLampBlue, !!(outputdataBase6 & 0x2));
	Outputs->SetValue(OutputLampBlue2, !!(outputdataBase7 & 0x80));
}

void SRTV::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "Sega Race TV";
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