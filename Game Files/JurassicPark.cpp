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

#include "JurassicPark.h"

static int WindowsLoop()
{
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

static void(__cdecl* CBLampSetOri)(int param_1, void* param_2);
static void __cdecl CBLampSet(int param_1, void* param_2)
{
	EOutputs lampType = OutputLampOnline;
	if (param_1 == 0) lampType = OutputLampStart; //LAMP_P1START,
	else if (param_1 == 2) lampType = Output2pLampStart; //LAMP_P2START
	else if (param_1 == 3) lampType = OutputBillboardLamp; //LAMP_DINOHEAD
	else if (param_1 == 4) lampType = OutputBillboardBlue; //LAMP_LOGO
	else if (param_1 == 5) lampType = OutputBillboardRed; //LAMP_DINOEYES
	else if (param_1 == 6) lampType = OutputBillboardWhite; //LAMP_ROOF
	else if (param_1 == 7) lampType = OutputBillboardLamp; //LAMP_MARQUEE
	else if (param_1 == 8) lampType = OutputLampView3; //LAMP_DASH
	else if (param_1 == 9) lampType = OutputLampGreen; //LAMP_FOLIAGE
	else if (param_1 == 10) lampType = Output1pHolderLamp; //LAMP_P1GUN_R
	else if (param_1 == 11) lampType = Output1pHolderLamp; //LAMP_P1GUN_G
	else if (param_1 == 12) lampType = Output1pHolderLamp; //LAMP_P1GUN_B
	else if (param_1 == 13) lampType = Output2pHolderLamp; //LAMP_P2GUN_R
	else if (param_1 == 14) lampType = Output2pHolderLamp; //LAMP_P2GUN_G
	else if (param_1 == 15) lampType = Output2pHolderLamp; //LAMP_P2GUN_B
	else if (param_1 == 16) lampType = OutputBase0Left; //LAMP_SEAT_R
	else if (param_1 == 17) lampType = OutputBase0Right; //LAMP_SEAT_G
	else if (param_1 == 18) lampType = OutputBase1Left; //LAMP_SEAT_B
	else if (param_1 == 19) lampType = OutputBase1Right; //LAMP_BENCH_LOGO
	else if (param_1 == 20) lampType = OutputLampView1; //LAMP_P1GUN_MOUNT
	else if (param_1 == 21) lampType = OutputLampView2; //LAMP_P2GUN_MOUNT
	else if (param_1 == 22) lampType = OutputBillboardGreen; //LAMP_SEAT_BASE
	else if (param_1 == 23) lampType = OutputLampRed; //LAMP_ESTOP
	else if (param_1 == 24) lampType = OutputLampRed; //LAMP_COMPRESSOR

	if (lampType) {
		bool lampOn = false;
		if (param_2 > 0) {
			if ((int)param_2 >= 1055000000)
			{
				lampOn = true;
			}
		}
		Outputs->SetValue(lampType, lampOn);
	}
	return CBLampSetOri(param_1, param_2);
}


void JurassicPark::OutputsGameLoop()
{
	if (!init)
	{
		OutputDebugStringA("Jurassic Park");
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Jurassic Park";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);

		MH_Initialize();
		MH_CreateHook((void*)(0x81c8a00), CBLampSet, (void**)&CBLampSetOri);
		MH_EnableHook(MH_ALL_HOOKS);

		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}