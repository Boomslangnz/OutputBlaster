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

#include "HOTD4.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	INT_PTR outputdataBase1 = *(INT_PTR *)(imageBase + 0x4C4F44);
	INT_PTR outputdataBase2 = *(INT_PTR *)(outputdataBase1 + 0x760);
	INT_PTR outputdataBase3 = *(INT_PTR *)(outputdataBase2 + 0x18);
	INT_PTR outputdataBase4 = *(INT_PTR *)(outputdataBase3 + 0x2BC);
	INT_PTR outputdataBase5 = *(INT_PTR *)(outputdataBase4 + 0xA8);
	BYTE outputdataBase6 = *(BYTE *)(outputdataBase5 + 0xC);
	BYTE outputdataBase7 = *(BYTE *)(outputdataBase5 + 0xD);

	Outputs->SetValue(OutputLampStart, !!(outputdataBase6 & 0x80));
	if (outputdataBase7 == 0x30)
	{
		Outputs->SetValue(Output2pLampStart, 0x01);
	}
	else
	{
		Outputs->SetValue(Output2pLampStart, 0x00);
	}	
}

void HOTD4::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "House of the Dead 4";
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