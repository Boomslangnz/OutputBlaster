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

#include "Cars.h"

static int WindowsLoop()
{
	UINT8 Start = helpers->ReadByte(0x14D14A5, true);
	UINT8 View1 = helpers->ReadByte(0x14D14AD, true);
	UINT8 View2 = helpers->ReadByte(0x14D14B1, true);
	UINT8 View3 = helpers->ReadByte(0x14D14B5, true);
	UINT8 SeatBase = helpers->ReadByte(0x14D14D1, true);
	UINT8 SeatBackrest = helpers->ReadByte(0x14D14D5, true);

	Outputs->SetValue(OutputLampStart, !!(Start & 0xFF));
	Outputs->SetValue(OutputLampView1, !!(View1 & 0xFF));
	Outputs->SetValue(OutputLampView2, !!(View2 & 0xFF));
	Outputs->SetValue(OutputLampView3, !!(View3 & 0xFF));
	Outputs->SetValue(OutputSeat1Lamp, !!(SeatBase & 0xFF));
	Outputs->SetValue(OutputSeat2Lamp, !!(SeatBackrest & 0xFF));
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

void Cars::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Cars";
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