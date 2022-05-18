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

#include "WMMT5DXPlus.h"

static int WindowsLoop()
{
	UINT8 outputdata = helpers->ReadByte(0x1FD55D1, true);
	UINT8 outputdata2 = helpers->ReadByte(0x1FD55D2, true);
	float FFB1 = helpers->ReadFloat32(0x1FA6F40, true);
	float FFB2 = helpers->ReadFloat32(0x1FA6F44, true);
	float FFB3 = helpers->ReadFloat32(0x1FA6F48, true);
	float FFB4 = helpers->ReadFloat32(0x1FA6F4C, true);

	Outputs->SetValue(OutputLampView1, !!(outputdata & 0x08));
	Outputs->SetValue(OutputInterruption, !!(outputdata & 0x04));
	Outputs->SetValue(OutputLampRed, !!(outputdata2 & 0x80));
	Outputs->SetValue(OutputLampGreen, !!(outputdata2 & 0x40));
	Outputs->SetValue(OutputLampBlue, !!(outputdata2 & 0x20));
	if (outputdata2 >= 0xE0)
		Outputs->SetValue(OutputLampWhite, 0x01);
	else
		Outputs->SetValue(OutputLampWhite, 0x00);
	Outputs->SetValue(OutputSideLamp, !!(outputdata2 & 0x10));
	Outputs->SetValue(OutputFFB1, FFB1 * 100.0);
	Outputs->SetValue(OutputFFB2, FFB2 * 100.0);
	Outputs->SetValue(OutputFFB3, FFB3 * 100.0);
	Outputs->SetValue(OutputFFB4, FFB4 * 100.0);
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

void WMMT5DXPlus::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Wangan Midnight Maximum Tune 5DX+";
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