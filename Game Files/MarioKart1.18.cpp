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

#include "MarioKart1.18.h"

static int WindowsLoop()
{
	UINT8 ButtonData = helpers->ReadByte(0xAC6FB4, true);
	UINT8 KanbanSideLampData = helpers->ReadByte(0xAC72D8, true);
	UINT8 UnderLampData = helpers->ReadByte(0xAC72E8, true);


	Outputs->SetValue(OutputLampStart, !!(ButtonData & 0x04));
	Outputs->SetValue(OutputLampView1, !!(ButtonData & 0x08));
	Outputs->SetValue(OutputBillboardRed, !!(KanbanSideLampData & 0x000000F0));
	Outputs->SetValue(OutputBillboardGreen, !!(KanbanSideLampData & 0x0000000F));
	Outputs->SetValue(OutputBillboardBlue, !!(KanbanSideLampData & 0x00F00000));
	Outputs->SetValue(OutputBillboardWhite, !!(KanbanSideLampData & 0x00F0FF00));
	Outputs->SetValue(OutputSideRed, !!(KanbanSideLampData & 0xF0000000));
	Outputs->SetValue(OutputSideGreen, !!(KanbanSideLampData & 0x0F000000));
	Outputs->SetValue(OutputSideBlue, !!(KanbanSideLampData & 0x00F000000));
	Outputs->SetValue(OutputSideWhite, !!(KanbanSideLampData & 0xFFFF00000));
	Outputs->SetValue(OutputLampRed, !!(UnderLampData & 0x00FF0000));
	Outputs->SetValue(OutputLampGreen, !!(UnderLampData & 0x000F0000));
	Outputs->SetValue(OutputLampBlue, !!(UnderLampData & 0xF0000000));
	Outputs->SetValue(OutputLampWhite, !!(UnderLampData & 0xFFFF0000));
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

void MarioKart118::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Mario Kart 1.18";
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