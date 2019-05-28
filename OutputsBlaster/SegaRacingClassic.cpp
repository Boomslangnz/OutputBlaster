/*This file is part of Outputs Blaster.

Outputs Blaster is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Outputs Blaster is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Outputs Blaster.If not, see < https://www.gnu.org/licenses/>.*/

#include <string>
#include "SegaRacingClassic.h"
#include "WinOutputs.h"
#include "stdafx.h"
//GameOutput m_game;
//COutputs  *Outputs;
//static MSG Msg1;
//UINT K_TIME;
//uintptr_t imageBase;
//static bool init = false;
//
//
//VOID CALLBACK YourTimer(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
//{
//	imageBase = (uintptr_t)GetModuleHandleA(0);
//	BYTE data = *(BYTE *)(imageBase + 0x434C18);
//	Outputs->SetValue(OutputLampStart, !!(data & 0x04));
//	Outputs->SetValue(OutputLampView1, !!(data & 0x08));
//	Outputs->SetValue(OutputLampView2, !!(data & 0x40));
//	Outputs->SetValue(OutputLampView3, !!(data & 0x10));
//	Outputs->SetValue(OutputLampView4, !!(data & 0x80));
//	Outputs->SetValue(OutputLampLeader, !!(data & 0x20));
//	Outputs->SetValue(OutputRawLamps, data);
//}
//
//void SegaRacingClassic::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers)
//{
//	if (!init)
//	{
//		Outputs = new CWinOutputs();
//		m_game.name = "Sega Racing Classic";
//		Outputs->SetGame(m_game);
//		Outputs->Initialize();
//		Outputs->Attached();
//		SetTimer(0, 0, K_TIME, YourTimer);
//		while (GetMessage(&Msg1, NULL, NULL, 0))
//		{
//			TranslateMessage(&Msg1);
//			DispatchMessage(&Msg1);
//		}
//		init = true;
//	}
//}