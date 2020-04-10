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


#include "AliensExtermination.h"
#include <string>
#include <Windows.h>

//static wchar_t* settingsFilename = TEXT(".\\OutputBlaster.ini");
static int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);
static int configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength"), 120, settingsFilename);
static int HowtoRumbleGunEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleGunEffect"), 0, settingsFilename);
static int HowtoRumbleFlameEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleFlameEffect"), 0, settingsFilename);
static int HowtoRumbleHealthEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleHealthEffect"), 0, settingsFilename);
static int Gun1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gun1pStrength"), 0, settingsFilename);
static int Flame1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Flame1pStrength"), 0, settingsFilename);
static int Health1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health1pStrength"), 0, settingsFilename);
static int Gun2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gun2pStrength"), 0, settingsFilename);
static int Flame2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Flame2pStrength"), 0, settingsFilename);
static int Health2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health2pStrength"), 0, settingsFilename);

static bool Ammo1pBool = false;
static bool Ammo2pBool = false;
static bool Flame1pBool = false;
static bool Flame2pBool = false;
static bool Health1pBool = false;
static bool Health2pBool = false;

static int WindowsLoop()
{
	UINT8 Ammo1pA = helpers->ReadByte(0x4E7AEA0, true);
	UINT8 Ammo1pB = helpers->ReadByte(0x4E7AEA1, true);
	float Flame1p = helpers->ReadFloat32(0x556CB30, true);
	float Health1p = helpers->ReadFloat32(0x556C884, true);
	UINT8 Ammo2pA = helpers->ReadByte(0x4E7AEA2, true);
	UINT8 Ammo2pB = helpers->ReadByte(0x4E7AEA3, true);
	float Flame2p = helpers->ReadFloat32(0x556CEC4, true);
	float Health2p = helpers->ReadFloat32(0x556CC18, true);
	UINT8 Shoot1p = helpers->ReadByte(0x4E7AEC8, true);
	UINT8 Shoot2p = helpers->ReadByte(0x4E7AF00, true);
	
	static UINT8 oldAmmo = 0;
	UINT8 newAmmo = Ammo1pA;

	static UINT8 oldAmmo2 = 0;
	UINT8 newAmmo2 = Ammo2pA;

	static float oldFlame = 0;
	float newFlame = Flame1p;

	static float oldFlame2 = 0;
	float newFlame2 = Flame2p;

	static float oldHealth = 0;
	float newHealth = Health1p;

	static float oldHealth2 = 0;
	float newHealth2 = Health2p;

	static UINT8 oldShoot = 0;
	UINT8 newShoot = Shoot1p;

	static UINT8 oldShoot2 = 0;
	UINT8 newShoot2 = Shoot2p;

	if (oldAmmo != newAmmo)
	{
		if (Ammo1pBool)
		{
			if ((Ammo1pB >= 0) && (Ammo1pA > 0))
			{
				if (HowtoRumbleGunEffect == 0)
				{
					double percentForce = ((Gun1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 1)
				{
					double percentForce = ((Gun1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(0, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 2)
				{
					double percentForce = ((Gun1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, 0, percentLength);
				}
			}
		}

		if ((Ammo1pA == 0) && (Ammo1pB == 0))
		{
			Ammo1pBool = false;
		}
		else
		{
			Ammo1pBool = true;
		}
	}

	if (oldShoot != newShoot)
	{
		if (((Ammo1pA == 0) && (Ammo1pB == 0)) || ((Ammo1pA == 10) && (Ammo1pB == 10)))
		{ 
			if (Shoot1p == 1)
			{
				if (HowtoRumbleGunEffect == 0)
				{
					double percentForce = ((Gun1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 1)
				{
					double percentForce = ((Gun1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(0, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 2)
				{
					double percentForce = ((Gun1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, 0, percentLength);
				}
			}
		}
	}

	if (oldAmmo2 != newAmmo2)
	{
		if (Ammo2pBool)
		{
			if ((Ammo2pB >= 0) && (Ammo2pA > 0))
			{
				if (HowtoRumbleGunEffect == 0)
				{
					double percentForce = ((Gun2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 1)
				{
					double percentForce = ((Gun2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(0, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 2)
				{
					double percentForce = ((Gun2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, 0, percentLength);
				}
			}
		}

		if ((Ammo2pA == 0) && (Ammo2pB == 0))
		{
			Ammo2pBool = false;
		}
		else
		{
			Ammo2pBool = true;
		}
	}

	if (oldShoot2 != newShoot2)
	{
		if (((Ammo2pA == 0) && (Ammo2pB == 0)) || ((Ammo2pA == 10) && (Ammo2pB == 10)))
		{ 
			if (Shoot2p == 1)
			{
				if (HowtoRumbleGunEffect == 0)
				{
					double percentForce = ((Gun2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 1)
				{
					double percentForce = ((Gun2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(0, percentForce, percentLength);
				}
				else if (HowtoRumbleGunEffect == 2)
				{
					double percentForce = ((Gun2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, 0, percentLength);
				}
			}
		}
	}

	if (oldFlame != newFlame)
	{
		if (Flame1pBool)
		{
			if (Flame1p > 0)
			{
				if (HowtoRumbleFlameEffect == 0)
				{
					double percentForce = ((Flame1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleFlameEffect == 1)
				{
					double percentForce = ((Flame1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(0, percentForce, percentLength);
				}
				else if (HowtoRumbleFlameEffect == 2)
				{
					double percentForce = ((Flame1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, 0, percentLength);
				}
			}
		}

		if ((Flame1p <= 0) )
		{
			Flame1pBool = false;
		}
		else
		{
			Flame1pBool = true;
		}
	}

	if (oldFlame2 != newFlame2)
	{
		if (Flame2pBool)
		{
			if (Flame2p > 0)
			{
				if (HowtoRumbleFlameEffect == 0)
				{
					double percentForce = ((Flame2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleFlameEffect == 1)
				{
					double percentForce = ((Flame2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(0, percentForce, percentLength);
				}
				else if (HowtoRumbleFlameEffect == 2)
				{
					double percentForce = ((Flame2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, 0, percentLength);
				}
			}
		}

		if ((Flame2p <= 0))
		{
			Flame2pBool = false;
		}
		else
		{
			Flame2pBool = true;
		}
	}

	if (oldHealth != newHealth)
	{
		if (Health1pBool)
		{
			if (Health1p > 0)
			{
				if (HowtoRumbleHealthEffect == 0)
				{
					double percentForce = ((Health1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 1)
				{
					double percentForce = ((Health1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(0, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 2)
				{
					double percentForce = ((Health1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->Rumble(percentForce, 0, percentLength);
				}
			}
		}

		if ((Health1p == 0))
		{
			Health1pBool = false;
		}
		else
		{
			Health1pBool = true;
		}
	}

	if (oldHealth2 != newHealth2)
	{
		if (Health2pBool)
		{
			if (Health2p > 0)
			{
				if (HowtoRumbleHealthEffect == 0)
				{
					double percentForce = ((Health2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 1)
				{
					double percentForce = ((Health2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(0, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 2)
				{
					double percentForce = ((Health2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					//triggers->RumbleDevice2(percentForce, 0, percentLength);
				}
			}
		}

		if ((Health2p == 0))
		{
			Health2pBool = false;
		}
		else
		{
			Health2pBool = true;
		}
	}

	oldAmmo = newAmmo;
	oldAmmo2 = newAmmo2;
	oldFlame = newFlame;
	oldFlame2 = newFlame2;
	oldHealth = newHealth;
	oldHealth2 = newHealth2;
	oldShoot = newShoot;
	oldShoot2 = newShoot2;


	Outputs->SetValue(EOutputs::OutputAmmo1pA, Ammo1pA);
	Outputs->SetValue(EOutputs::OutputAmmo1pB, Ammo1pB);
	Outputs->SetValue(EOutputs::OutputAmmo2pA, Ammo2pA);
	Outputs->SetValue(EOutputs::OutputAmmo2pB, Ammo2pB);
	Outputs->SetValue(EOutputs::OutputFlame1pBool, Flame1pBool);
	Outputs->SetValue(EOutputs::OutputFlame2pBool, Flame2pBool);
	Outputs->SetValue(EOutputs::OutputHealth1pBool, Health1pBool);
	Outputs->SetValue(EOutputs::OutputHealth2pBool, Health2pBool);
	Outputs->SetValue(EOutputs::OutputShoot1p, Shoot1p);
	Outputs->SetValue(EOutputs::OutputShoot2p, Shoot2p);

	return 0;
}

static DWORD WINAPI OutputsAreGo(LPVOID lpParam)
{
	while (true) {
		WindowsLoop();
		Sleep(16);
	}
}

void AliensExtermination::OutputsGameLoop()
{
	if (!init) {
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Aliens Extermination";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0)) {
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}
