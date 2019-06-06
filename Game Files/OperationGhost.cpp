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

#include "OperationGhost.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE OutputData = *(BYTE *)(imageBase + 0x246428);

	Outputs->SetValue(OutputLampStart, !!(OutputData & 0x80));
	Outputs->SetValue(Output1pRecoil, !!(OutputData & 0x40));
	Outputs->SetValue(Output1pHolderLamp, !!(OutputData & 0x02));
	Outputs->SetValue(Output2pLampStart, !!(OutputData & 0x10));
	Outputs->SetValue(Output2pRecoil, !!(OutputData & 0x08));
	Outputs->SetValue(Output2pHolderLamp, !!(OutputData & 0x01));
	Outputs->SetValue(OutputBillboardLamp, !!(OutputData & 0x20));
}

void OperationGhost::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "Operation G.H.O.S.T";
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