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

#include "HOTD4VerC.h"

static INT_PTR JvsBaseA;
static INT_PTR JvsBaseB;
static INT_PTR JvsBaseC;
static INT_PTR JvsBaseD;
static INT_PTR JvsBaseE;
static INT_PTR JvsBaseF;
static INT_PTR JvsBaseG;
static INT_PTR JvsBaseH;
static INT_PTR JvsBaseI;

static INT_PTR HOTD4BasePtr;
static INT_PTR HOTD4PtrA;
static INT_PTR HOTD4PtrB;
static INT_PTR HOTD4PtrC;
static INT_PTR HOTD4Ptr1P;
static INT_PTR HOTD4Ptr2P;

static uintptr_t cgGLBase;
static UINT8 InGame;
static UINT8 ChapterNum;

static DWORD P1BulletsFired;
static DWORD P2BulletsFired;
static DWORD OldP1BulletsFired;
static DWORD OldP2BulletsFired;

static bool NewChapter;

typedef enum _HOTD4_PLAYER_STATE {
	HPS_DEAD = 0,
	HPS_RESERVED_1 = 1,
	HPS_LOADING = 2,
	HPS_PLAYING = 3,
	HPS_CUT_SCENE = 4,
	HPS_CHOOSE_PATH = 5,
	HPS_RESULTS = 6,
	HPS_RANKING = 7,
	HPS_DYING = 8,
	HPS_CONTINUE_OTHER_PLAYER_STILL_ALIVE = 9,
	HPS_RESERVED_10 = 10,
	HPS_CONTINUE_LAST_PLAYER = 11,
	HPS_MAX = 255
} HOTD4_PLAYER_STATE;

static HOTD4_PLAYER_STATE JvsP1State = HPS_DEAD;
static HOTD4_PLAYER_STATE JvsP2State = HPS_DEAD;

static int WindowsLoop()
{
	HOTD4BasePtr = helpers->ReadIntPtr(cgGLBase + 0x40E4, false);
	HOTD4PtrA = helpers->ReadIntPtr(HOTD4BasePtr + 0xF14, false);
	HOTD4PtrB = helpers->ReadIntPtr(HOTD4PtrA + 0xE4, false);
	HOTD4PtrC = helpers->ReadIntPtr(HOTD4PtrB + 0x00, false);
	HOTD4Ptr1P = helpers->ReadIntPtr(HOTD4PtrC + 0x20, false);
	HOTD4Ptr2P = helpers->ReadIntPtr(HOTD4PtrC + 0x38, false);

	JvsBaseA = helpers->ReadIntPtr(cgGLBase + 0x40E4, false);
	JvsBaseB = helpers->ReadIntPtr(JvsBaseA + 0xF14, false);
	JvsBaseC = helpers->ReadIntPtr(JvsBaseB + 0xE4, false);
	JvsBaseD = helpers->ReadIntPtr(JvsBaseC + 0x0, false);
	JvsBaseE = helpers->ReadIntPtr(JvsBaseD + 0x20, false);

	JvsBaseF = helpers->ReadIntPtr(JvsBaseA + 0x494, false);
	JvsBaseG = helpers->ReadIntPtr(JvsBaseF + 0x218, false);
	JvsBaseH = helpers->ReadIntPtr(JvsBaseG + 0x0, false);
	JvsBaseI = helpers->ReadIntPtr(JvsBaseH + 0x38, false);

	InGame = helpers->ReadByte(0xA6F27EC, false);

	JvsP1State = (HOTD4_PLAYER_STATE)helpers->ReadByte(JvsBaseE + 0x38, false);
	JvsP2State = (HOTD4_PLAYER_STATE)helpers->ReadByte(JvsBaseI + 0x38, false);

	if (JvsP1State == HPS_RESULTS || JvsP2State == HPS_RESULTS || JvsP1State == HPS_RANKING || JvsP2State == HPS_RANKING)
	{
		if (!NewChapter)
		{
			NewChapter = true;
			++ChapterNum;
		}
	}

	if (JvsP1State == HPS_CUT_SCENE || JvsP2State == HPS_CUT_SCENE)
	{
		if (NewChapter)
			NewChapter = false;
	}

	if ((JvsP1State == HPS_PLAYING || JvsP2State == HPS_PLAYING) && InGame == 0x0A)
	{
		switch (ChapterNum)
		{
		case 0:
			P1BulletsFired = helpers->ReadInt32(HOTD4Ptr1P + 0x68, false);
			P2BulletsFired = helpers->ReadInt32(HOTD4Ptr2P + 0x68, false);
			break;
		case 1:
			P1BulletsFired = helpers->ReadInt32(HOTD4Ptr1P + 0x6C, false);
			P2BulletsFired = helpers->ReadInt32(HOTD4Ptr2P + 0x6C, false);
			break;
		case 2:
			P1BulletsFired = helpers->ReadInt32(HOTD4Ptr1P + 0x70, false);
			P2BulletsFired = helpers->ReadInt32(HOTD4Ptr2P + 0x70, false);
			break;
		case 3:
			P1BulletsFired = helpers->ReadInt32(HOTD4Ptr1P + 0x74, false);
			P2BulletsFired = helpers->ReadInt32(HOTD4Ptr2P + 0x74, false);
			break;
		case 4:
			P1BulletsFired = helpers->ReadInt32(HOTD4Ptr1P + 0x78, false);
			P2BulletsFired = helpers->ReadInt32(HOTD4Ptr2P + 0x78, false);
			break;
		case 5:
			P1BulletsFired = helpers->ReadInt32(HOTD4Ptr1P + 0x7C, false);
			P2BulletsFired = helpers->ReadInt32(HOTD4Ptr2P + 0x7C, false);
			break;
		}

		if (JvsP1State == HPS_PLAYING && InGame == 0x0A)
		{
			if (OldP1BulletsFired != P1BulletsFired && OldP1BulletsFired && P1BulletsFired)
			{
				if (Outputs->GetValue(OutputShoot1p) && AutoRecoilPulse)
					Outputs->SetValue(OutputShoot1p, 0);
				else
					Outputs->SetValue(OutputShoot1p, 1);
			}
			else
				Outputs->SetValue(OutputShoot1p, 0);
		}

		if (JvsP2State == HPS_PLAYING && InGame == 0x0A)
		{
			if (OldP2BulletsFired != P2BulletsFired && OldP2BulletsFired && P2BulletsFired)
				Outputs->SetValue(OutputShoot2p, 1);
			else
				Outputs->SetValue(OutputShoot2p, 0);
		}
	}
	else
	{
		Outputs->SetValue(OutputShoot1p, 0);
		Outputs->SetValue(OutputShoot2p, 0);
	}

	OldP1BulletsFired = P1BulletsFired;
	OldP2BulletsFired = P2BulletsFired;
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

void HOTD4VerC::OutputsGameLoop()
{
	if (!init)
	{
		cgGLBase = (uintptr_t)GetModuleHandleA("cgGL.dll");
		Outputs = CreateOutputsFromConfig();
		m_game.name = "House Of The Dead 4 (Version C)";
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