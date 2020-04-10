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

static int WindowsLoop()
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE data = *(BYTE*)(imageBase + 0x434C18);
	BYTE data2 = *(BYTE*)(imageBase + 0x50DBEA);
	BYTE FFB = *(BYTE*)(0x834C19);

	Outputs->SetValue(OutputLampStart, !!(data & 0x04));
	Outputs->SetValue(OutputLampLeader, !!(data & 0x20));
	Outputs->SetValue(OutputLampView1, !!(data & 0x08));
	Outputs->SetValue(OutputLampView2, !!(data & 0x40));
	Outputs->SetValue(OutputLampView3, !!(data & 0x10));
	Outputs->SetValue(OutputLampView4, !!(data & 0x80));	
	Outputs->SetValue(OutputRawLamps, data);
	Outputs->SetValue(OutputWooferRed, !!(data2 & 0x01));
	Outputs->SetValue(OutputWooferGreen, !!(data2 & 0x02));
	Outputs->SetValue(OutputWooferBlue, !!(data2 & 0x04));
	Outputs->SetValue(OutputRearRed, !!(data2 & 0x08));
	Outputs->SetValue(OutputRearGreen, !!(data2 & 0x10));
	Outputs->SetValue(OutputRearBlue, !!(data2 & 0x20));
	Outputs->SetValue(OutputFFB, FFB);
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

void SegaRacingClassic::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Sega Racing Classic";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);		
		init = true;
	}

	while (GetMessage(&Msg1, NULL, NULL, 0))
	{
		TranslateMessage(&Msg1);
		DispatchMessage(&Msg1);
	}
	
}