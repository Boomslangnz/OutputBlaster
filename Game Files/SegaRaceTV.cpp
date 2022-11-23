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

static int WindowsLoop()
{
	uintptr_t regal32Base = (uintptr_t)GetModuleHandleA("regal32.dll");
	INT_PTR outputBase = helpers->ReadIntPtr((INT_PTR)regal32Base + 0x262B58, false);
	INT_PTR outputOff0 = helpers->ReadIntPtr(outputBase + 0x5C, false);
	INT_PTR outputOff1 = helpers->ReadIntPtr(outputOff0 + 0x08, false);
	UINT8 output1 = helpers->ReadByte(outputOff1 + 0x2B2, false);
	UINT8 output2 = helpers->ReadByte(outputOff1 + 0x2B3, false);

	Outputs->SetValue(OutputLampStart, !!(output1 & 0x80));
	Outputs->SetValue(OutputLampView1, !!(output1 & 0x8));
	Outputs->SetValue(OutputBoost, !!(output1 & 0x10));
	Outputs->SetValue(OutputLampRed, !!(output1 & 0x1));
	Outputs->SetValue(OutputLampRed2, !!(output2 & 0x40));
	Outputs->SetValue(OutputLampBlue, !!(output1 & 0x2));
	Outputs->SetValue(OutputLampBlue2, !!(output2 & 0x80));
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

void SRTV::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Sega Race TV";
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