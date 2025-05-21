#pragma once
#include "enums.h"

namespace tomb4
{
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned long ulong;

	inline constexpr int W2V_SHIFT	= 14;

#pragma pack(push, 1)
    struct PHD_3DPOS
	{
		long x_pos;
		long y_pos;
		long z_pos;
		short x_rot;
		short y_rot;
		short z_rot;
	};

	struct LOCUST_STRUCT
	{
		PHD_3DPOS pos;
		short room_number;
		short speed;
		short Counter;
		short LaraTarget;
		char XTarget;
		char ZTarget;
		uchar On;
		uchar flags;
	};

	struct PHD_VECTOR
	{
		long x;
		long y;
		long z;
	};

	struct PCLIGHT
	{
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;
		long shadow;
		float Inner;
		float Outer;
		float InnerAngle;
		float OuterAngle;
		float Cutoff;
		float nx;
		float ny;
		float nz;
		long ix;
		long iy;
		long iz;
		long inx;
		long iny;
		long inz;
		float tr;
		float tg;
		float tb;
		float rs;
		float gs;
		float bs;
		long fcnt;
		uchar Type;
		uchar Active;
		PHD_VECTOR rlp;
		long Range;
	};

	struct ITEM_LIGHT
	{
		long r;
		long g;
		long b;
		long ambient;
		long rs;
		long gs;
		long bs;
		long fcnt;
		PCLIGHT	CurrentLights[21];
		PCLIGHT	PrevLights[21];
		long nCurrentLights;
		long nPrevLights;
		long room_number;
		long RoomChange;
		PHD_VECTOR item_pos;
		void* pCurrentLights;
		void* pPrevLights;
	};

	struct ITEM_INFO
	{
		long floor;
		ulong touch_bits;
		ulong mesh_bits;
		short object_number;
		short current_anim_state;
		short goal_anim_state;
		short required_anim_state;
		short anim_number;
		short frame_number;
		short room_number;
		short next_item;
		short next_active;
		short speed;
		short fallspeed;
		short hit_points;
		ushort box_number;
		short timer;
		short flags;
		short shade;
		short trigger_flags;
		short carried_item;
		short after_death;
		ushort fired_weapon;
		short item_flags[4];
		void* data;
		PHD_3DPOS pos;
		ITEM_LIGHT il;
		ulong active : 1;
		ulong status : 2;
		ulong gravity_status : 1;
		ulong hit_status : 1;
		ulong collidable : 1;
		ulong looked_at : 1;
		ulong dynamic_light : 1;
		ulong poisoned : 1;
		ulong ai_bits : 5;
		ulong really_active : 1;
		ulong meshswap_meshbits;
		short draw_room;
		short TOSSPAD;
	};

	struct FX_INFO
	{
		PHD_3DPOS pos;
		short room_number;
		short object_number;
		short next_fx;
		short next_active;
		short speed;
		short fallspeed;
		short frame_number;
		short counter;
		short shade;
		short flag1;
		short flag2;
	};

	struct LARA_ARM
	{
		short* frame_base;
		short frame_number;
		short anim_number;
		short lock;
		short y_rot;
		short x_rot;
		short z_rot;
		short flash_gun;
	};

	struct BOX_NODE
	{
		short exit_box;
		ushort search_number;
		short next_expansion;
		short box_number;
	};

	struct LOT_INFO
	{
		BOX_NODE* node;
		short head;
		short tail;
		ushort search_number;
		ushort block_mask;
		short step;
		short drop;
		short zone_count;
		short target_box;
		short required_box;
		short fly;
		ushort can_jump : 1;
		ushort can_monkey : 1;
		ushort is_amphibious : 1;
		ushort is_jumping : 1;
		ushort is_monkeying : 1;
		PHD_VECTOR target;
		zone_type zone;
	};

	struct CREATURE_INFO
	{
		short joint_rotation[4];
		short maximum_turn;
		short flags;
		ushort alerted : 1;
		ushort head_left : 1;
		ushort head_right : 1;
		ushort reached_goal : 1;
		ushort hurt_by_lara : 1;
		ushort patrol2 : 1;
		ushort jump_ahead : 1;
		ushort monkey_ahead : 1;
		mood_type mood;
		ITEM_INFO* enemy;
		ITEM_INFO ai_target;
		short pad;
		short item_num;
		PHD_VECTOR target;
		LOT_INFO LOT;
	};

	struct LARA_INFO
	{
		short item_number;
		short gun_status;
		short gun_type;
		short request_gun_type;
		short last_gun_type;
		short calc_fallspeed;
		short water_status;
		short climb_status;
		short pose_count;
		short hit_frame;
		short hit_direction;
		short air;
		short dive_count;
		short death_count;
		short current_active;
		short current_xvel;
		short current_yvel;
		short current_zvel;
		short spaz_effect_count;
		short flare_age;
		short vehicle;
		short weapon_item;
		short back_gun;
		short flare_frame;
		short poisoned;
		short dpoisoned;
		uchar electric;
		uchar wet[15];
		ushort flare_control_left : 1;
		ushort Unused1 : 1;
		ushort look : 1;
		ushort burn : 1;
		ushort keep_ducked : 1;
		ushort IsMoving : 1;
		ushort CanMonkeySwing : 1;
		ushort Unused2 : 1;
		ushort OnBeetleFloor : 1;
		ushort BurnGreen : 1;
		ushort IsDucked : 1;
		ushort has_fired : 1;
		ushort Busy : 1;
		ushort LitTorch : 1;
		ushort IsClimbing : 1;
		ushort Fired : 1;
		long water_surface_dist;
		PHD_VECTOR last_pos;
		FX_INFO* spaz_effect;
		long mesh_effects;
		short* mesh_ptrs[15];
		ITEM_INFO* target;
		short target_angles[2];
		short turn_rate;
		short move_angle;
		short head_y_rot;
		short head_x_rot;
		short head_z_rot;
		short torso_y_rot;
		short torso_x_rot;
		short torso_z_rot;
		LARA_ARM left_arm;
		LARA_ARM right_arm;
		ushort holster;
		CREATURE_INFO* creature;
		long CornerX;
		long CornerZ;
		char RopeSegment;
		char RopeDirection;
		short RopeArcFront;
		short RopeArcBack;
		short RopeLastX;
		short RopeMaxXForward;
		short RopeMaxXBackward;
		long RopeDFrame;
		long RopeFrame;
		ushort RopeFrameRate;
		ushort RopeY;
		long RopePtr;
		void* GeneralPtr;
		long RopeOffset;
		ulong RopeDownVel;
		char RopeFlag;
		char MoveCount;
		long RopeCount;
		char pistols_type_carried;
		char uzis_type_carried;
		char shotgun_type_carried;
		char crossbow_type_carried;
		char grenade_type_carried;
		char sixshooter_type_carried;
		char lasersight;
		char binoculars;
		char crowbar;
		char mechanical_scarab;
		uchar small_water_skin;
		uchar big_water_skin;
		char examine1;
		char examine2;
		char examine3;
		char puzzleitems[12];
		ushort puzzleitemscombo;
		ushort keyitems;
		ushort keyitemscombo;
		ushort pickupitems;
		ushort pickupitemscombo;
		short questitems;
		short num_small_medipack;
		short num_large_medipack;
		short num_flares;
		short num_pistols_ammo;
		short num_uzi_ammo;
		short num_revolver_ammo;
		short num_shotgun_ammo1;
		short num_shotgun_ammo2;
		short num_grenade_ammo1;
		short num_grenade_ammo2;
		short num_grenade_ammo3;
		short num_crossbow_ammo1;
		short num_crossbow_ammo2;
		short num_crossbow_ammo3;
		char beetle_uses;
		char blindTimer;
		char location;
		char highest_location;
		char locationPad;
	};

	struct COLL_INFO
	{
		long mid_floor;
		long mid_ceiling;
		long mid_type;
		long front_floor;
		long front_ceiling;
		long front_type;
		long left_floor;
		long left_ceiling;
		long left_type;
		long right_floor;
		long right_ceiling;
		long right_type;
		long left_floor2;
		long left_ceiling2;
		long left_type2;
		long right_floor2;
		long right_ceiling2;
		long right_type2;
		long radius;
		long bad_pos;
		long bad_neg;
		long bad_ceiling;
		PHD_VECTOR shift;
		PHD_VECTOR old;
		short old_anim_state;
		short old_anim_number;
		short old_frame_number;
		short facing;
		short quadrant;
		short coll_type;
		short* trigger;
		char tilt_x;
		char tilt_z;
		char hit_by_baddie;
		char hit_static;
		ushort slopes_are_walls : 2;
		ushort slopes_are_pits : 1;
		ushort lava_is_pit : 1;
		ushort enable_baddie_push : 1;
		ushort enable_spaz : 1;
		ushort hit_ceiling : 1;
	};

	struct OBJECT_INFO
	{
		short nmeshes;
		short mesh_index;
		long bone_index;
		short* frame_base;
		void (*initialise)(short item_number);
		void (*control)(short item_number);
		void (*floor)(ITEM_INFO* item, long x, long y, long z, long* height);
		void (*ceiling)(ITEM_INFO* item, long x, long y, long z, long* height);
		void (*draw_routine)(ITEM_INFO* item);
		void (*collision)(short item_num, ITEM_INFO* laraitem, COLL_INFO* coll);
		short object_mip;
		short anim_index;
		short hit_points;
		short pivot_length;
		short radius;
		short shadow_size;
		ushort bite_offset;
		ushort loaded : 1;
		ushort intelligent : 1;
		ushort non_lot : 1;
		ushort save_position : 1;
		ushort save_hitpoints : 1;
		ushort save_flags : 1;
		ushort save_anim : 1;
		ushort semi_transparent : 1;
		ushort water_creature : 1;
		ushort using_drawanimating_item : 1;
		ushort HitEffect : 2;
		ushort undead : 1;
		ushort save_mesh : 1;
		void (*draw_routine_extra)(ITEM_INFO* item);
		ulong explodable_meshbits;
		ulong padfuck;
	};

	struct STATIC_INFO
	{
		short mesh_number;
		short flags;
		short x_minp;
		short x_maxp;
		short y_minp;
		short y_maxp;
		short z_minp;
		short z_maxp;
		short x_minc;
		short x_maxc;
		short y_minc;
		short y_maxc;
		short z_minc;
		short z_maxc;
	};

	struct CHANGE_STRUCT
	{
		short goal_anim_state;
		short number_ranges;
		short range_index;
	};

	struct RANGE_STRUCT
	{
		short start_frame;
		short end_frame;
		short link_anim_num;
		short link_frame_num;
	};

	struct ANIM_STRUCT
	{
		short* frame_ptr;
		short interpolation;
		short current_anim_state;
		long velocity;
		long acceleration;
		long Xvelocity;
		long Xacceleration;
		short frame_base;
		short frame_end;
		short jump_anim_num;
		short jump_frame_num;
		short number_changes;
		short change_index;
		short number_commands;
		short command_index;
	};
#pragma pack(pop)
}
