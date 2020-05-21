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

#include "R-Tuned.h"

static int WindowsLoop()
{
	UINT8 outputs1 = helpers->ReadByte(0x84FEA78, false);
	UINT8 outputs2 = helpers->ReadByte(0x84FEA79, false);

	Outputs->SetValue(OutputLampStart, !!(outputs1 & 0x08));
	Outputs->SetValue(OutputLampView1, !!(outputs1 & 0x10));
	Outputs->SetValue(OutputLampRed, !!(outputs2 & 0x02));
	Outputs->SetValue(OutputLampRed2, !!(outputs2 & 0x08));
	Outputs->SetValue(OutputLampBlue, !!(outputs2 & 0x01));
	Outputs->SetValue(OutputLampBlue2, !!(outputs2 & 0x04));
	Outputs->SetValue(OutputBoostRed, !!(outputs1 & 0x20));
	Outputs->SetValue(OutputBoostGreen, !!(outputs1 & 0x40));
	Outputs->SetValue(OutputBoostBlue, !!(outputs1 & 0x80));

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

void RTuned::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "R-Tuned Ultimate Street Racing";
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