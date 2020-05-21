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

#include "SonicAllStarsRacing.h"

static int WindowsLoop()
{
	UINT8 data = helpers->ReadByte(0x813708, true);
	UINT8 data2 = helpers->ReadByte(0x813709, true);
	UINT8 FFB = helpers->ReadByte(0x5CD864, true);

	//Enable FFB
	helpers->WriteByte(0x5CD858, 0x03, true);

	Outputs->SetValue(OutputLampStart, !!(data & 0x80));
	Outputs->SetValue(OutputLampLeader, !!(data & 0x40));
	Outputs->SetValue(OutputLampRed, !!(data2 & 0x08));
	Outputs->SetValue(OutputLampGreen, !!(data2 & 0x04));
	Outputs->SetValue(OutputLampBlue, !!(data2 & 0x02));
	Outputs->SetValue(OutputSideRed, !!(data & 0x02));
	Outputs->SetValue(OutputSideGreen, !!(data & 0x01));
	Outputs->SetValue(OutputSideBlue, !!(data2 & 0x80));
	Outputs->SetValue(OutputWooferRed, !!(data2 & 0x40));
	Outputs->SetValue(OutputWooferGreen, !!(data2 & 0x20));
	Outputs->SetValue(OutputWooferBlue, !!(data2 & 0x10));
	Outputs->SetValue(OutputItemRed, !!(data & 0x08));
	Outputs->SetValue(OutputItemGreen, !!(data & 0x20));
	Outputs->SetValue(OutputItemBlue, !!(data & 0x04));
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

void SonicAllStarsRacing::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Sonic & Sega All Stars Racing";
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