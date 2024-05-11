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

#include "MotoGP.h"

static int WindowsLoop()
{

	UINT8 startLamp = helpers->ReadByte(0x094AF4A0,false);
	UINT8 raceLeader = helpers->ReadByte(0x094AF49C,false);
	UINT8 dashRed = helpers->ReadByte(0x08D4E590,false);
	UINT8 dashGreen = helpers->ReadByte(0x08D4E594,false);
	UINT8 dashBlue = helpers->ReadByte(0x08D4E598,false);
	UINT8 moldingRed = helpers->ReadByte(0x08D4E59C,false);
	UINT8 moldingGreen = helpers->ReadByte(0x08D4E5A0,false);
	UINT8 moldingBlue = helpers->ReadByte(0x08D4E5A4,false);
	UINT8 wheelRed = helpers->ReadByte(0x094AF4D8,false);
	UINT8 wheelOrange = helpers->ReadByte(0x094AF4DC,false);
	UINT8 wheelBlue = helpers->ReadByte(0x094AF4E0,false);
	UINT8 brakeRed = helpers->ReadByte(0x094AF4F0,false);
	UINT8 brakeGreen = helpers->ReadByte(0x094AF4F4,false);
	UINT8 brakeBlue = helpers->ReadByte(0x094AF4F8,false);
	//set lamps if the value is greaterthan 0

	Outputs->SetValue(OutputLampStart, startLamp > 0);
	Outputs->SetValue(OutputLampLeader, raceLeader > 0);
	Outputs->SetValue(OutputLampView1, dashRed > 0);
	Outputs->SetValue(OutputLampView2, dashGreen > 0);
	Outputs->SetValue(OutputLampView3, dashBlue > 0);
	//Outputs->SetValue(OutputLampMoldingRed, moldingRed > 0); // not sure where to put these
	//Outputs->SetValue(OutputLampMoldingGreen, moldingGreen > 0);
	//Outputs->SetValue(OutputLampMoldingBlue, moldingBlue > 0);
	// Outputs->SetValue(OutputLampWheelRed, wheelRed > 0);
	// Outputs->SetValue(OutputLampWheelOrange, wheelOrange > 0);
	// Outputs->SetValue(OutputLampWheelBlue, wheelBlue > 0);
	Outputs->SetValue(OutputBrakeLamp1p, brakeRed > 0);
	Outputs->SetValue(OutputBrakeLamp1p, brakeGreen > 0);
	Outputs->SetValue(OutputBrakeLamp1p, brakeBlue > 0);
	

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


void MotoGP::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Moto GP";
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