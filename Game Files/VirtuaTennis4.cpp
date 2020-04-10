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

#include "VirtuaTennis4.h"

static int WindowsLoop()
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE outputBase = *(BYTE*)(imageBase + 0x4057DC);
	BYTE outputData1p = *(BYTE*)(outputBase + 0x44);
	BYTE outputData2p = *(BYTE*)(outputBase + 0x48);

	Outputs->SetValue(OutputLampStart, !!(outputData1p & 0x80));
	Outputs->SetValue(Output2pLampStart, !!(outputData2p & 0x80));
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

void VirtuaTennis4::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Virtua Tennis 4";
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