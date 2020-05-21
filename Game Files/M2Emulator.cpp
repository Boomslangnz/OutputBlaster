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

#include "M2Emulator.h"

static int WindowsLoop()
{
	INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, true);
	INT_PTR RambaseA = helpers->ReadIntPtr(Rambase + 0x100, false);
	UINT8 data = helpers->ReadByte(RambaseA + 0x824, false);

	Outputs->SetValue(OutputLampStart, !!(data & 0x04));
	Outputs->SetValue(OutputLampLeader, !!(data & 0x80));
	Outputs->SetValue(OutputLampView1, !!(data & 0x08));
	Outputs->SetValue(OutputLampView2, !!(data & 0x10));
	Outputs->SetValue(OutputLampView3, !!(data & 0x20));
	Outputs->SetValue(OutputLampView4, !!(data & 0x40));
	Outputs->SetValue(OutputRawLamps, data);

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

void M2Emulator::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "M2 Emulator";
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