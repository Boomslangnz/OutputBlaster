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

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;
bool OutputsRunning = true;


DWORD WINAPI OutputsLoop(LPVOID lpParam)
{
	return 0;	
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	BOOL result = TRUE;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, OutputsLoop, (LPVOID)&OutputsRunning, 0, NULL);
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		OutputsRunning = false;
        break;
    }
    return TRUE;
}