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

#include "SRG.h"

static int WindowsLoop()
{
	UINT8 Lights1 = helpers->ReadByte(0x3E16ACA, true);
	UINT8 Lights2 = helpers->ReadByte(0x3E16AB9, true);
	UINT8 Lights3 = helpers->ReadByte(0x3E16ABB, true);

	Outputs->SetValue(OutputLampStart, !!(Lights1 & 0x10));
	Outputs->SetValue(OutputLampView1, !!(Lights1 & 0x08));
	Outputs->SetValue(OutputBillboardLamp, !!(Lights1 & 0x01));
	Outputs->SetValue(OutputDash, !!(Lights1 & 0x04));
	Outputs->SetValue(OutputSideLamp, !!(Lights2 & 0xFF));
	Outputs->SetValue(OutputSideLamp2, !!(Lights3 & 0xFF));
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

void SRG::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Storm Racer G";
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