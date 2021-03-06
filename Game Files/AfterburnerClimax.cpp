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

#include "AfterburnerClimax.h"

static int WindowsLoop()
{
	UINT8 data = helpers->ReadByte(0x8347A5E, false);

	Outputs->SetValue(OutputLampStart, !!(data & 0x80));
	Outputs->SetValue(OutputRawDrive, !!(data & 0x40));
	Outputs->SetValue(OutputLampRed, !!(data & 0x10));
	Outputs->SetValue(OutputLampGreen, !!(data & 0x08));
	Outputs->SetValue(OutputLampBlue, !!(data & 0x04));
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

void AfterburnerClimax::OutputsGameLoop()
{	
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Afterburner Climax";
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