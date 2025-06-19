#pragma once

namespace flep
{
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned long ulong;

#pragma pack(push, 1)
	struct CARTINFO
	{
		long Speed;
		long MidPos;
		long FrontPos;
		long TurnX;
		long TurnZ;
		short TurnLen;
		short TurnRot;
		short YVel;
		short Gradient;
		char Flags;
		char StopDelay;
	};

	struct QUADINFO
	{
		short joint_rotation[4];
		long Velocity;
		short FrontRot;
		short RearRot;
		long Revs;
		long EngineRevs;
		short track_mesh;
		long skidoo_turn;
		long left_fallspeed;
		long right_fallspeed;
		short momentum_angle;
		short extra_rotation;
		long pitch;
		uchar Flags;
	};
#pragma pack(pop)
}
