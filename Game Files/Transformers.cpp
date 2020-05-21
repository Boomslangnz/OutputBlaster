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

#include "Transformers.h"

static int WindowsLoop(Helpers* helpers)
{
	UINT8 Testoutputs1 = helpers->ReadByte(0x5A9428, false);
	UINT8 Testoutputs2 = helpers->ReadByte(0x5A9429, false);
	UINT8 outputs1 = helpers->ReadByte(0xD8CD14, false);
	UINT8 outputs2 = helpers->ReadByte(0xD8CD15, false);

	Outputs->SetValue(OutputLampStart, !!(outputs1 & 0x80) || !!(Testoutputs1 & 0x80));
	Outputs->SetValue(Output2pLampStart, !!(outputs1 & 0x10) || !!(Testoutputs1 & 0x10));
	Outputs->SetValue(OutputControllerLamp1p, !!(outputs1 & 0x02) || !!(Testoutputs1 & 0x02));
	Outputs->SetValue(OutputControllerLamp2p, !!(outputs1 & 0x01) || !!(Testoutputs1 & 0x01));
	Outputs->SetValue(OutputBrakeLamp1p, !!(outputs2 & 0x80) || !!(Testoutputs2 & 0x80));
	Outputs->SetValue(OutputBrakeLamp2p, !!(outputs2 & 0x40) || !!(Testoutputs2 & 0x40));
	Outputs->SetValue(OutputBillboardLamp, !!(outputs2 & 0x04) || !!(Testoutputs2 & 0x04));
	Outputs->SetValue(OutputEmblemRed, !!(outputs2 & 0x20) || !!(Testoutputs2 & 0x20));
	Outputs->SetValue(OutputEmblemGreen, !!(outputs2 & 0x10) || !!(Testoutputs2 & 0x10));
	Outputs->SetValue(OutputEmblemBlue, !!(outputs2 & 0x08) || !!(Testoutputs2 & 0x08));
	Outputs->SetValue(OutputShoot1p, !!(outputs1 & 0x40) || !!(Testoutputs1 & 0x40));
	Outputs->SetValue(OutputShoot2p, !!(outputs1 & 0x08) || !!(Testoutputs1 & 0x08));
	return 0;
}

static DWORD WINAPI OutputsAreGo(LPVOID lpParam)
{
	while (true)
	{
		WindowsLoop(0);
		Sleep(SleepA);
	}
}

void Transformers::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Transformers Human Alliance";
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