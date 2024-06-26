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

static int WindowsLoop()
{
	UINT8 OutputData = helpers->ReadByte(0x246428, true);

	Outputs->SetValue(OutputLampStart, !!(OutputData & 0x80));
	Outputs->SetValue(Output1pHolderLamp, !!(OutputData & 0x02));
	Outputs->SetValue(Output2pLampStart, !!(OutputData & 0x10));
	Outputs->SetValue(Output2pHolderLamp, !!(OutputData & 0x01));
	Outputs->SetValue(OutputBillboardLamp, !!(OutputData & 0x20));

	if (Outputs->GetValue(Output1pRecoil) && AutoRecoilPulse)
		Outputs->SetValue(Output1pRecoil, 0);
	else
		Outputs->SetValue(Output1pRecoil, !!(OutputData & 0x40));

	if (Outputs->GetValue(Output2pRecoil) && AutoRecoilPulse)
		Outputs->SetValue(Output2pRecoil, 0);
	else
		Outputs->SetValue(Output2pRecoil, !!(OutputData & 0x08));

	return 0;
}

static DWORD WINAPI OutputsAreGo(LPVOID lpParam)
{
	while (true)
	{
		WindowsLoop();
		Sleep(SleepA);
	}
}

void OperationGhost::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Operation G.H.O.S.T";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}