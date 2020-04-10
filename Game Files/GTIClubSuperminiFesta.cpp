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

#include "GTIClubSuperminiFesta.h"

static int WindowsLoop()
{
	BYTE actionlamp = *(BYTE*)(0xA7E794);
	BYTE startlamp = *(BYTE*)(0xA7E790);
	BYTE selectuplamp = *(BYTE*)(0xA7E7A0);
	BYTE selectdownlamp = *(BYTE*)(0xA7E7A4);
	BYTE selectleftlamp = *(BYTE*)(0xA7E798);
	BYTE selectrightlamp = *(BYTE*)(0xA7E79C); 
	INT_PTR FFB = *(INT_PTR*)0x918CBC;

	Outputs->SetValue(OutputLampAction, !!(actionlamp & 0x1F));
	Outputs->SetValue(OutputLampStart, !!(startlamp & 0x1F));
	Outputs->SetValue(OutputLampSelectUp, (selectuplamp / 31.0) * 100.0);
	Outputs->SetValue(OutputLampSelectDown, (selectdownlamp / 31.0) * 100.0);
	Outputs->SetValue(OutputLampSelectLeft, (selectleftlamp / 31.0) * 100.0);
	Outputs->SetValue(OutputLampSelectRight, (selectrightlamp / 31.0) * 100.0);
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

void GTIClubSuperminiFesta::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "GTI Club Supermini Festa";
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