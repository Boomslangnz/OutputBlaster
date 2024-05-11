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

#include "CruisnBlast.h"

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
	//set lampType to nothing
	EOutputs lampType = OutputLampOnline;
	if (param_1 == 0) lampType = OutputLampStart;
	else if (param_1 == 2) lampType = OutputLampView1;
	else if (param_1 == 3) lampType = OutputLampView2;
	else if (param_1 == 4) lampType = OutputLampView3;
	else if (param_1 == 5) lampType = OutputLampView4;
	else if (param_1 == 6) lampType = OutputLampLeader;

	if (lampType) {
		bool lampOn = false;
		if (param_2 > 0) {
			if ((int)param_2 >= 1055000000)
			{
				lampOn = true;
			}
		}
		Outputs->SetValue(lampType,lampOn);
	}
	return CBLampSetOri(param_1, param_2);
}

static unsigned int (__cdecl* CB_RIO_PwmOutSetOrig)(int param_1, int param_2);
static unsigned int __cdecl RIO_PwmOutSet(int param_1, int param_2)
{
	return CB_RIO_PwmOutSetOrig(param_1, param_2);
	/*
	if (param_1 == 84)
	{
		Outputs->SetValue(OutputLampStart, param_2 && 3276);
	}
	if (param_1 == 86)
	{
		Outputs->SetValue(OutputLampView1, param_2 && 3276);
	}
	if (param_1 == 87)
	{
		Outputs->SetValue(OutputLampView2, param_2 && 3276);
	}
	if (param_1 == 88)
	{
		Outputs->SetValue(OutputLampView3, param_2 && 3276);
	}
	if (param_1 == 89)
	{
		Outputs->SetValue(OutputLampView4, param_2 && 3276);
	}
	if (param_1 == 94)
	{
		Outputs->SetValue(OutputLampLeader, param_2 && 3276);
	}

	return CB_RIO_PwmOutSetOrig(param_1, param_2);
	*/
}

static void (__cdecl* LampFX_UpdateOri)(unsigned int param_1, unsigned int param_2, int* param_3);
static void __cdecl LampFX_Update(unsigned int param_1, unsigned int param_2, int* param_3)
{	
	return LampFX_UpdateOri(param_1, param_2, param_3);
}

static void (__cdecl* LampDeluxe_SetOri)(unsigned int param_1, unsigned int param_2);
static void __cdecl LampDeluxe_Set(unsigned int param_1, unsigned int param_2)
{
	return LampDeluxe_SetOri(param_1, param_2);
}

static void (__cdecl* LampPX_SetOri)(unsigned int param_1, unsigned int param_2);
static void __cdecl LampPX_Set(unsigned int param_1, unsigned int param_2)
{
	return LampPX_SetOri(param_1, param_2);
}

static void (__cdecl* LampSC_SetOri)(unsigned int param_1, unsigned int param_2);
static void __cdecl LampSC_Set(unsigned int param_1, unsigned int param_2)
{
	EOutputs lampType = OutputLampOnline;
	if (param_1 == 0) lampType = OutputLampStart;
	else if (param_1 == 2) lampType = OutputLampView1;
	else if (param_1 == 3) lampType = OutputLampView2;
	else if (param_1 == 4) lampType = OutputLampView3;
	else if (param_1 == 5) lampType = OutputLampView4;
	else if (param_1 == 6) lampType = OutputLampLeader;

	if (lampType) {
		bool lampOn = false;

		if (param_2 > 0) {
			if ((int)param_2 >= 1040000000)
			{
				lampOn = true;
			}
		}
		//Outputs->SetValue(lampType,lampOn);
	}
	return LampSC_SetOri(param_1, param_2);
}

static long double (__cdecl* LampFX_BlinkOri)(unsigned int param_1, unsigned int param_2, int* param_3);
static long double __cdecl LampFX_Blink(unsigned int param_1, unsigned int param_2, int* param_3)
{
	return LampFX_BlinkOri(param_1, param_2, param_3);
}

static long double (__cdecl* LampFX_PulseOri)(unsigned int param_1, int* param_2);
static long double __cdecl LampFX_Pulse(unsigned int param_1, int* param_2)
{
	return LampFX_PulseOri(param_1, param_2);
}

static void (__cdecl* LampUnisMotion_SetOri)(unsigned int param_1, unsigned int param_2);
static void __cdecl LampUnisMotion_Set(unsigned int param_1, unsigned int param_2)
{
	return LampUnisMotion_SetOri(param_1, param_2);
}

static void (__cdecl* LampFX_SetStateOri)(void* param_1);
static void __cdecl LampFX_SetState(void* param_1)
{
	if ((int)param_1 == 5)
	{
		Outputs->SetValue(OutputLampStart, true);
		Outputs->SetValue(OutputLampView1, true);
		Outputs->SetValue(OutputLampView2, true);
		Outputs->SetValue(OutputLampView3, true);
		Outputs->SetValue(OutputLampView4, true);
	}
	else
	{
		Outputs->SetValue(OutputLampStart, false);
		Outputs->SetValue(OutputLampView1, false);
		Outputs->SetValue(OutputLampView2, false);
		Outputs->SetValue(OutputLampView3, false);
		Outputs->SetValue(OutputLampView4, false);
	
	}
	return LampFX_SetStateOri(param_1);
}

static void (__cdecl* LampFX_ColorCycleOri)(unsigned int param_1, float* param_2, float* param_3, float* param_4, int* param_5, int param_6);
static void __cdecl LampFX_ColorCycle(unsigned int param_1, float* param_2, float* param_3, float* param_4, int* param_5, int param_6)
{
	return LampFX_ColorCycleOri(param_1, param_2, param_3, param_4, param_5, param_6);
}

static long double (__cdecl* LampFX_ColorCycleValOri)(unsigned int param_1, int* param_2);
static long double __cdecl LampFX_ColorCycleVal(unsigned int param_1, int* param_2)
{
	return LampFX_ColorCycleValOri(param_1, param_2);
}

static long double (__cdecl* LampFX_PulseValOri)(unsigned int param_1, int* param_2);
static long double __cdecl LampFX_PulseVal(unsigned int param_1, int* param_2)
{
		return LampFX_PulseValOri(param_1, param_2);
}

void CruisnBlast::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "CruisnBlast";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);

		MH_Initialize();
		MH_CreateHook((void*)(0x8142490), CBLampSet, (void**)&CBLampSetOri);
		MH_CreateHook((void*)(0x8143320), LampFX_SetState, (void**)&LampFX_SetStateOri);
		/*
		Unused hooks, maybe we can use them later
		MH_CreateHook((void*)(0x83a9aa0), RIO_PwmOutSet, (void**)&CB_RIO_PwmOutSetOrig);
		MH_CreateHook((void*)(0x81427a0), LampFX_Update, (void**)&LampFX_UpdateOri);
		MH_CreateHook((void*)(0x8141dc0), LampPX_Set, (void**)&LampPX_SetOri);
		MH_CreateHook((void*)(0x8141fd0), LampDeluxe_Set, (void**)&LampDeluxe_SetOri);
		MH_CreateHook((void*)(0x8141c90), LampSC_Set, (void**)&LampSC_SetOri);
		MH_CreateHook((void*)(0x8142fd0), LampFX_Blink, (void**)&LampFX_BlinkOri);
		MH_CreateHook((void*)(0x8141eb0), LampUnisMotion_Set, (void**)&LampUnisMotion_SetOri);
		MH_CreateHook((void*)(0x81428e0), LampFX_Pulse, (void**)&LampFX_PulseOri);
		MH_CreateHook((void*)(0x8142aa0), LampFX_ColorCycle, (void**)&LampFX_ColorCycleOri);
		MH_CreateHook((void*)(0x8142a00), LampFX_ColorCycleVal, (void**)&LampFX_ColorCycleValOri);
		MH_CreateHook((void*)(0x8142840), LampFX_PulseVal, (void**)&LampFX_PulseValOri);
		*/
		MH_EnableHook(MH_ALL_HOOKS);

		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}