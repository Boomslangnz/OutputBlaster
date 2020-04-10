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

#include "WackyRaces.h"

static int WindowsLoop()
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	INT_PTR lampbase = *(INT_PTR*)(imageBase + 0x7E00590);
	INT_PTR lamps = *(INT_PTR*)(lampbase + 0x45);
	BYTE Seatlamp1 = *(BYTE*)(lampbase + 0x53);
	BYTE Seatlamp2 = *(BYTE*)(lampbase + 0x51);
	BYTE Seatlamp3 = *(BYTE*)(lampbase + 0x23);
	BYTE Seatlamp4 = *(BYTE*)(lampbase + 0x4D);
	BYTE Seatlamp5 = *(BYTE*)(lampbase + 0x1F);
	BYTE Seatlamp6 = *(BYTE*)(lampbase + 0x49);
	INT_PTR FFBBase = *(INT_PTR*)(imageBase + 0x7E00590);
	BYTE FFB = *(BYTE*)FFBBase + 0x45;

	Outputs->SetValue(OutputLampStart, !!(lamps & 0x80));
	Outputs->SetValue(OutputLampView1, !!(lamps & 0x100));
	Outputs->SetValue(OutputPanelLamp, !!(lamps & 0x08));
	Outputs->SetValue(OutputSlot1Lamp, !!(lamps & 0x400));
	Outputs->SetValue(OutputSlot2Lamp, !!(lamps & 0x10));
	Outputs->SetValue(OutputSlot3Lamp, !!(lamps & 0x200));
	Outputs->SetValue(OutputSeat1Lamp, !!(Seatlamp1 & 0xFF));
	Outputs->SetValue(OutputSeat2Lamp, !!(Seatlamp2 & 0xFF));
	Outputs->SetValue(OutputSeat3Lamp, !!(Seatlamp3 & 0xFF));
	Outputs->SetValue(OutputSeat4Lamp, !!(Seatlamp4 & 0xFF));
	Outputs->SetValue(OutputSeat5Lamp, !!(Seatlamp5 & 0xFF));
	Outputs->SetValue(OutputSeat6Lamp, !!(Seatlamp6 & 0xFF));
	Outputs->SetValue(OutputSeat7Lamp, !!(lamps & 0x4000));
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

void WackyRaces::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Wacky Races";
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