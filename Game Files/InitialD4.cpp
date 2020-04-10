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

#include "InitialD4.h"

static int WindowsLoop()
{
	BYTE outputdata1 = *(BYTE*)(0x8D7CCDD);
	BYTE outputdata2 = *(BYTE*)(0x8D7CCDE);
	INT_PTR FFB = *(INT_PTR*)0x89AE89A;

	Outputs->SetValue(OutputLampStart, !!(outputdata1 & 0x80));
	Outputs->SetValue(OutputLampView1, !!(outputdata1 & 0x40));
	Outputs->SetValue(OutputLampSelectUp, !!(outputdata1 & 0x02));
	Outputs->SetValue(OutputLampSelectDown, !!(outputdata1 & 0x01));
	Outputs->SetValue(OutputLampSelectLeft, !!(outputdata2 & 0x80));
	Outputs->SetValue(OutputLampSelectRight, !!(outputdata2 & 0x40));
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

void InitialD4::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Initial D Arcade Stage 4";
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