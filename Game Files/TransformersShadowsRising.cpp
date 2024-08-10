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

#include "TransformersShadowsRising.h"
#include <TlHelp32.h>

DWORD GetProcessIDByName(const std::wstring& processName) {
	DWORD processID = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnapshot, &pe)) {
			do {
				if (pe.szExeFile == processName) {
					processID = pe.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &pe));
		}
		CloseHandle(hSnapshot);
	}
	return processID;
}

static int WindowsLoop()
{
	return 0;
}

static unsigned int(__cdecl* ShellMgr_SendCmdOri)(unsigned short param_1, unsigned char* param_2, int param_3);
static unsigned int __cdecl ShellMgr_SendCmd(unsigned short param_1, unsigned char* param_2, int param_3)
{

	std::string out = "ShellMgr_SendCmd: " + std::to_string(param_1) + " " + std::to_string(param_3);
	OutputDebugStringA(out.c_str());
	return ShellMgr_SendCmdOri(param_1, param_2, param_3);
}

static bool init2 = false;
static DWORD WINAPI OutputsAreGo(LPVOID lpParam)
{
	MH_Initialize();
	while (true)
	{
		if (!init2) {
			
			std::wstring exeName = L"Transformers2.exe";
			DWORD processID = GetProcessIDByName(exeName);
			if (processID != 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID);

					//hook hProcess + 0x5e7af0
				if (hProcess != NULL)
				{
					MH_CreateHook((void*)((DWORD)GetModuleHandle(NULL) + 0x5e7af0), ShellMgr_SendCmd, (void**)&ShellMgr_SendCmdOri);
					OutputDebugStringA("ShellMgr_SendCmd hooked");
					init2 = true;
				}
			}
		}
		WindowsLoop();
		Sleep(SleepA);
	}
}

void TransformersShadowsRising::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Transformers Shadows Rising";
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