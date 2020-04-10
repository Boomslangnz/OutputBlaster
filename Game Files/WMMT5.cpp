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

#include "WMMT5.h"

static int WindowsLoop()
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE outputdata = *(BYTE*)(imageBase + 0x199F0CC);
	BYTE outputdata2 = *(BYTE*)(imageBase + 0x199F0CD);
	INT_PTR FFB1 = *(INT_PTR*)imageBase + 0x196F188;
	INT_PTR FFB2 = *(INT_PTR*)imageBase + 0x196F18C;
	INT_PTR FFB3 = *(INT_PTR*)imageBase + 0x196F190;
	INT_PTR FFB4 = *(INT_PTR*)imageBase + 0x196F194;

	Outputs->SetValue(OutputLampView1, !!(outputdata & 0x08));
	Outputs->SetValue(OutputInterruption, !!(outputdata & 0x04));
	Outputs->SetValue(OutputLampRed, !!(outputdata2 & 0x80));
	Outputs->SetValue(OutputLampGreen, !!(outputdata2 & 0x40));
	Outputs->SetValue(OutputLampBlue, !!(outputdata2 & 0x20));
	if (outputdata2 >= 0xE0)
	{
		Outputs->SetValue(OutputLampWhite, 0x01);
	}
	else
	{
		Outputs->SetValue(OutputLampWhite, 0x00);
	}
	Outputs->SetValue(OutputSideLamp, !!(outputdata2 & 0x10));
	Outputs->SetValue(OutputFFB, FFB1);
	Outputs->SetValue(OutputFFB, FFB2);
	Outputs->SetValue(OutputFFB, FFB3);
	Outputs->SetValue(OutputFFB, FFB4);
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

void WMMT5::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Wangan Midnight Maximum Tune 5";
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