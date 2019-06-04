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

#ifndef INCLUDED_OUTPUTS_H
#define INCLUDED_OUTPUTS_H
#include "GameOutput.h"
/*
 * EOutputs enumeration of all available outputs.
 */
enum EOutputs
{
	OutputUnknown = -1,
	OutputPause = 0,
	OutputLampStart,
	OutputLampView1,
	OutputLampView2,
	OutputLampView3,
	OutputLampView4,
	OutputLampLeader,
	OutputRawDrive,
	OutputRawLamps,
	OutputLampAction,
	OutputLampSelectUp,
	OutputLampSelectDown,
	OutputLampSelectLeft,
	OutputLampSelectRight,
	OutputLampHazard,
	OutputLampKey,
	OutputLampOnline,
	OutputLampOverrev,
	OutputLampRed,
	OutputLampGreen,
	OutputLampBlue,
	OutputLampYellow,
	OutputLampCyan,
	OutputLampMagneta,
	OutputLampWhite,
	OutputLampPatoButtonR,
	OutputLampPatoButtonB,
	OutputLampPato,
	OutputWooferRed,
	OutputWooferGreen,
	OutputWooferBlue,
	OutputRearRed,
	OutputRearGreen,
	OutputRearBlue,
	OutputSideRed,
	OutputSideGreen,
	OutputSideBlue,
	OutputItemRed,
	OutputItemGreen,
	OutputItemBlue,
	OutputDriverLampL,
	OutputDriverLampR,
	Output1pKnock,
	Output1pMotor,
	Output2pKnock,
	Output2pMotor,
	Output2pLampStart,
	OutputVisualChange3D,
	Output1pAirFront,
	Output1pAirRear,
	Output2pAirFront,
	Output2pAirRear,
	OutputInterruption,
	OutputSideLamp
};

#define NUM_OUTPUTS 55

class COutputs
{
public:
	/*
	 * GetOutputName(output):
	 *
	 * Returns the name of the given output as a string.
	 */
	static const char *GetOutputName(EOutputs output);

	/*
	 * GetOutputByName(name):
	 *
	 * Returns the output with the given name (if any).
	 */
	static EOutputs GetOutputByName(const char *name);

	/*
	 * ~COutputs():
	 *
	 * Destructor.
	 */
	virtual ~COutputs();

	/*
	 * Initialize():
	 *
	 * Initializes the outputs.  Must be called before the outputs are attached.
	 * To be implemented by the subclass.
	 */
	virtual bool Initialize() = 0;
	/*
	 * Attached():
	 *
	 * Lets the outputs know they have been attached to the emulator.
	 * To be implemented by the subclass.
	 */
	virtual void Attached() = 0;

	/*
	 * GetGame():
	 *
	 * Returns the currently running game.
	 */
	const GameOutput &GetGame() const;

	/*
	 * SetGame(game):
	 *
	 * Sets the currently running game.
	 */
	void SetGame(const GameOutput &game);

	/*
	 * GetValue(output):
	 *
	 * Returns the current value of the given output.
	 */
	UINT8 GetValue(EOutputs output) const;

	/*
	 * SetValue(output, value):
	 *
	 * Sets the current value of the given output.
	 */
	void SetValue(EOutputs output, UINT8 value);

protected:
	/*
	 * COutputs():
	 *
	 * Constructor.
	 */
	COutputs();

	/*
	 * SendOutput():
	 *
	 * Called when an output's value changes so that the subclass can handle it appropriately.
	 * To be implemented by the subclass.
	 */
	virtual void SendOutput(EOutputs output, UINT8 prevValue, UINT8 value) = 0;

private:
	static const char* s_outputNames[]; // Static array of output names

	GameOutput m_game;                  // Currently running game
	bool m_first[NUM_OUTPUTS];    // For each output, true if an initial value has been set
	UINT8 m_values[NUM_OUTPUTS];  // Current value of each output
};

#endif	// INCLUDED_OUTPUTS_H