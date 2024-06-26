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

#include "DaytonaChampionshipUSANSE.h"

static int WindowsLoop()
{
	UINT8 startdata = helpers->ReadByte(0x11C16E4, true);
	UINT8 view1data = helpers->ReadByte(0x11C16F8, true);
	UINT8 view2data = helpers->ReadByte(0x11C170C, true);
	UINT8 view3data = helpers->ReadByte(0x11C1720, true);
	UINT8 view4data = helpers->ReadByte(0x11C1734, true);
	UINT8 OutputsRaw = helpers->ReadByte(0x15C8803, true);
	DWORD RPM = helpers->ReadInt32(0x15CDAF8, true);
	UINT8 FFB = helpers->ReadByte(0x1334061, true);

	Outputs->SetValue(OutputLampStart, !!(startdata & 0x01));
	Outputs->SetValue(OutputLampView1, !!(view1data & 0x01));
	Outputs->SetValue(OutputLampView2, !!(view2data & 0x01));
	Outputs->SetValue(OutputLampView3, !!(view3data & 0x01));
	Outputs->SetValue(OutputLampView4, !!(view4data & 0x01));
	Outputs->SetValue(OutputLampLeader, !!(OutputsRaw & 0x80));
	Outputs->SetValue(OutputRPM, RPM / 100.0);
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

void DaytonaChampionshipUSANSE::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Daytona Championship USA NSE";
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