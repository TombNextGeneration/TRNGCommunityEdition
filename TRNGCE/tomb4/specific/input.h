#pragma once

namespace tomb4
{
	extern long &linput;
	extern long &input;
	extern long &dbinput;
	extern long &joy_fire;
	extern long &joy_x;
	extern long &joy_y;

	long S_UpdateInput();
	long ReadJoystick(long& x, long& y);
}

void Inject_Input(bool replace);
