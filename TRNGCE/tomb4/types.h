#pragma once
#define DIRECT3D_VERSION 0x0600
#include <d3d.h>
#define DIRECTINPUT_VERSION 0x0500
#include <dinput.h>
#include <mmreg.h>
#define DIRECTSOUND_VERSION 0x0500
#include <dsound.h>

namespace tomb4
{
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned long ulong;

	inline constexpr int W2V_SHIFT = 14;

	constexpr long SQUARE(long x)
	{
		return x * x;
	}

	enum class mood_type
	{
		BORED_MOOD,
		ATTACK_MOOD,
		ESCAPE_MOOD,
		STALK_MOOD,
	};

	enum class zone_type
	{
		SKELLY_ZONE,
		BASIC_ZONE,
		CROC_ZONE,
		HUMAN_ZONE,
		FLYER_ZONE,
	};

	enum class sfx_options
	{
		SFX_DEFAULT     = 0,
		SFX_WATER       = 1,
		SFX_ALWAYS      = 2,
		SFX_SETPITCH    = 4
	};

	enum class sound_effect_names
	{
		SFX_LARA_FEET,
		SFX_LARA_CLIMB2,
		SFX_LARA_NO,
		SFX_LARA_SLIPPING,
		SFX_LARA_LAND,
		SFX_LARA_CLIMB1,
		SFX_LARA_DRAW,
		SFX_LARA_HOLSTER,
		SFX_LARA_FIRE,
		SFX_LARA_RELOAD,
		SFX_LARA_RICOCHET,
		SFX_PUSH_BLOCK_END,
		SFX_METAL_SCRAPE_LOOP1,
		SFX_SMALL_SCARAB_FEET,
		SFX_BIG_SCARAB_ATTACK,
		SFX_BIG_SCARAB_DEATH,
		SFX_BIG_SCARAB_FLYING,
		SFX_LARA_WET_FEET,
		SFX_LARA_WADE,
		SFX_RUMBLE_LOOP,
		SFX_METAL_SCRAPE_LOOP,
		SFX_CRICKET_LOOP,
		SFX_WOOD_BRIDGE_FALL,
		SFX_STARGATE_SWIRL,
		SFX_LARA_KNEES_SHUFFLE,
		SFX_PUSH_SPX_SWITCH,
		SFX_LARA_CLIMB3,
		SFX_UNUSED,
		SFX_LARA_SHIMMY2,
		SFX_LARA_JUMP,
		SFX_LARA_FALL,
		SFX_LARA_INJURY,
		SFX_LARA_ROLL,
		SFX_LARA_SPLASH,
		SFX_LARA_GETOUT,
		SFX_LARA_SWIM,
		SFX_LARA_BREATH,
		SFX_LARA_BUBBLES,
		SFX_SPINNING_PUZZLE,
		SFX_LARA_KEY,
		SFX_COG_RESAW_LIBRARY,
		SFX_LARA_GENERAL_DEATH,
		SFX_LARA_KNEES_DEATH,
		SFX_LARA_UZI_FIRE,
		SFX_LARA_UZI_STOP,
		SFX_LARA_SHOTGUN,
		SFX_LARA_BLOCK_PUSH1,
		SFX_LARA_BLOCK_PUSH2,
		SFX_SARLID_PALACES,
		SFX_LARA_SHOTGUN_SHELL,
		SFX_UNDERWATER_DOOR,
		SFX_LARA_BLKPULL,
		SFX_LARA_FLOATING,
		SFX_LARA_FALLDEATH,
		SFX_LARA_GRABHAND,
		SFX_LARA_GRABBODY,
		SFX_LARA_GRABFEET,
		SFX_RATCHET_3SHOT,
		SFX_RATCHET_1SHOT,
		SFX_WATER_LOOP_NOTINUSE,
		SFX_UNDERWATER,
		SFX_UNDERWATER_SWITCH,
		SFX_LARA_PICKUP,
		SFX_PUSHABLE_SOUND,
		SFX_DOOR_GENERAL,
		SFX_HELICOPTER_LOOP,
		SFX_ROCK_FALL_CRUMBLE,
		SFX_ROCK_FALL_LAND,
		SFX_PENDULUM_BLADES,
		SFX_STALEGTITE,
		SFX_LARA_THUD,
		SFX_GENERIC_SWOOSH,
		SFX_GENERIC_HEAVY_THUD,
		SFX_CROC_FEET,
		SFX_SWINGING_FLAMES,
		SFX_STONE_SCRAPE,
		SFX_BLAST_CIRCLE,
		SFX_BAZOOKA_FIRE,
		SFX_MP5_FIRE,
		SFX_WATERFALL_LOOP,
		SFX_CROC_ATTACK,
		SFX_CROC_DEATH,
		SFX_PORTCULLIS_UP,
		SFX_PORTCULLIS_DOWN,
		SFX_DOUBLE_DOOR_BANG,
		SFX_DOUBLE_DOOR_CREAK,
		SFX_PETES_PYRA_STONE,
		SFX_PETES_PYRA_PNEU,
		SFX_AHMET_DIE,
		SFX_AHMET_ATTACK,
		SFX_AMHET_HANDS,
		SFX_AHMET_FEET,
		SFX_AHMET_SWIPE,
		SFX_AHMET_WAIT,
		SFX_GUIDE_JUMP,
		SFX_GENERAL_FOOTSTEPS1,
		SFX_GUIDE_LAND_USENOT,
		SFX_POUR,
		SFX_SCALE1,
		SFX_SCALE2,
		SFX_BEETLARA_WINDUP,
		SFX_BEETLE_CLK_WHIRR,
		SFX_BEETLE_CLK_EXP,
		SFX_MINE_EXP_OVERLAY,
		SFX_MP5_STOP,
		SFX_EXPLOSION1,
		SFX_EXPLOSION2,
		SFX_EARTHQUAKE_LOOP,
		SFX_MENU_ROTATE,
		SFX_MENU_SELECT,
		SFX_MENU_EMPTY,
		SFX_MENU_CHOOSE,
		SFX_TICK_TOCK,
		SFX_MENU_EMPTY1,
		SFX_MENU_COMBINE,
		SFX_MENU_EMPTY2,
		SFX_MENU_MEDI,
		SFX_LARA_CLIMB_WALLS_NOISE,
		SFX_WATER_LOOP,
		SFX_VONCROY_JUMP,
		SFX_LOCUSTS_LOOP,
		SFX_DESERT_EAGLE_FIRE,
		SFX_BOULDER_FALL,
		SFX_LARA_MINI_LOAD,
		SFX_LARA_MINI_LOCK,
		SFX_LARA_MINI_FIRE,
		SFX_GATE_OPENING,
		SFX_LARA_ELECTRIC_LOOP,
		SFX_LARA_ELECTRIC_CRACKLES,
		SFX_BLOOD_LOOP,
		SFX_BIKE_START,
		SFX_BIKE_IDLE,
		SFX_BIKE_ACCELERATE,
		SFX_BIKE_MOVING,
		SFX_BIKE_SIDE_IMPACT,
		SFX_BIKE_FRONT_IMPACT,
		SFX_SOFT_WIND_LOOP,
		SFX_BIKE_LAND,
		SFX_CROCGOD_ROAR,
		SFX_CROCGOD_WINGS,
		SFX_CROCGOD_LAND,
		SFX_CROCGOD_FIRE_ROAR,
		SFX_BIKE_STOP,
		SFX_GENERIC_BODY_SLAM,
		SFX_MP5_OVERLAY,
		SFX_LARA_SPIKE_DEATH,
		SFX_LARA_DEATH3,
		SFX_ROLLING_BALL,
		SFX_BLK_PLAT_RAISE_LOW,
		SFX_RUMBLE_NEXTDOOR,
		SFX_LOOP_FOR_SMALL_FIRES,
		SFX_CHAINS_LIBRARY,
		SFX_JEEP_START,
		SFX_JEEP_IDLE,
		SFX_JEEP_ACCELERATE,
		SFX_JEEP_MOVE,
		SFX_JEEP_STOP,
		SFX_BATS_1,
		SFX_ROLLING_DOOR,
		SFX_LAUNCHER_1,
		SFX_LAUNCHER_2,
		SFX_TRAPDOOR_OPEN,
		SFX_TRAPDOOR_CLOSE,
		SFX_EMPTY1,
		SFX_BABOON_STAND_WAIT,
		SFX_BABOON_ATTACK_LOW,
		SFX_BABOON_ATTACK_JUMP,
		SFX_BABOON_JUMP,
		SFX_BABOON_DEATH,
		SFX_BAT_SQUEAL_FULL,
		SFX_BAT_SQK,
		SFX_BAT_FLAP,
		SFX_SPHINX_NOSE_RASP,
		SFX_SPHINX_WALK,
		SFX_SPHINX_NOISE,
		SFX_DOG_HOWL,
		SFX_DOG_HIT_GOUND,
		SFX_FOUNTAIN_LOOP,
		SFX_DOG_FOOT_1,
		SFX_DOG_JUMP,
		SFX_DOG_BITE,
		SFX_DOG_DEATH,
		SFX_THUNDER_RUMBLE,
		SFX_THUNDER_CRACK,
		SFX_WRAITH_WHISPERS,
		SFX_EMPTY2,
		SFX_EMPTY3,
		SFX_SKEL_FOOTSTEP,
		SFX_SKEL_ATTACK,
		SFX_GENERIC_SWORD_SWOOSH,
		SFX_SKEL_SWORD_CLANG,
		SFX_SKEL_STICK_GROUND,
		SFX_GEN_PULL_SWORD,
		SFX_SKEL_LAND_HEAVY,
		SFX_GUIDE_SCARE,
		SFX_JEEP_DOOR_OPEN,
		SFX_JEEP_DOOR_CLOSE,
		SFX_ELEC_ARCING_LOOP,
		SFX_ELEC_ONE_SHOT,
		SFX_EMPTY4,
		SFX_LIBRARY_COG_LOOP,
		SFX_JEEP_SIDE_IMPACT,
		SFX_JEEP_FRONT_IMPACT,
		SFX_JEEP_LAND,
		SFX_SPINNING_GEM_SLOTS,
		SFX_RUMMBLE,
		SFX_WARTHOG_HEADBUTT,
		SFX_WARTHOG_DEATH,
		SFX_SET_SPIKE_TIMER,
		SFX_WARTHOG_SQUEAL,
		SFX_WARTHOG_FEET,
		SFX_WARTHOG_GRUNT,
		SFX_SAVE_CRYSTAL,
		SFX_HORSE_RICOCHETS,
		SFX_METAL_SHUTTERS_SMASH,
		SFX_GEM_DROP_ON_FLOOR,
		SFX_SCORPION_SCREAM,
		SFX_SCORPION_FEET,
		SFX_SCORPION_CLAWS,
		SFX_SCORPION_TAIL_WHIP,
		SFX_SCORPION_SMALL_FEET,
		SFX_METAL_GATE_OPEN,
		SFX_HORSE_TROTTING,
		SFX_KN_TEMPLAR_WALK,
		SFX_KN_TEMPLAR_GURGLES,
		SFX_KN_SWORD_SCRAPE,
		SFX_KN_TEMPLAR_ATTACK,
		SFX_KN_SWORD_CLANG,
		SFX_KN_SWORD_SWOOSH,
		SFX_MUMMY_ATTACK,
		SFX_MUMMY_WALK,
		SFX_MUMMY_GURGLES,
		SFX_MUMMY_TAKE_HIT,
		SFX_SMALL_FAN,
		SFX_LARGE_FAN,
		SFX_LARA_CROSSBOW,
		SFX_SMALL_CREATURE_FEET,
		SFX_SAS_GADGIE_DIE,
		SFX_WATER_FLUSHES,
		SFX_GUID_ZIPPO,
		SFX_LEAP_SWITCH,
		SFX_OLD_SWITCH,
		SFX_DEMIGODS_FEET,
		SFX_DEMIGODS_BULL_SNORT,
		SFX_DEMIGODS_BULL_HAMMER,
		SFX_DEMIGODS_S_WAVE_RUMB,
		SFX_DEMIGOD_WEAP_SWOOSH,
		SFX_DEMIGOD_FALCON_SQUEAL,
		SFX_DEMIGOD_FALCON_PLAS,
		SFX_DEMIGOD_RISE,
		SFX_DEMI_TUT_PLASMA_SPRAY,
		SFX_DEMI_SIREN_SWAVE,
		SFX_DEMIGODS_TUT_GROWL,
		SFX_JOBY_ELECTRIC_INSERT,
		SFX_BAD_LAND,
		SFX_DOOR_GEN_THUD,
		SFX_BAD_GRUNTS,
		SFX_BAD_DIE,
		SFX_BAD_JUMP,
		SFX_BAD_TROOP_STUN,
		SFX_BAD_SWORDAWAY,
		SFX_BAD_TROOP_UZI,
		SFX_BAD_SWORD_RICO,
		SFX_BAD_TROOP_UZI_END,
		SFX_TROOP_SCROP_CRIES,
		SFX_SAS_TROOP_FEET,
		SFX_GENERIC_NRG_CHARGE,
		SFX_SAS_MG_FIRE,
		SFX_HAMMER_HEAD_WADE,
		SFX_SMALL_SWITCH,
		SFX_EMPTY5,
		SFX_SIREN_WING_FLAP,
		SFX_SIREN_NOIZES,
		SFX_SIREN_ATTACK,
		SFX_SIREN_DEATH,
		SFX_SIREN_GEN_NOISES,
		SFX_SETT_SIREN_PLASMA,
		SFX_HAMMER_HEAD_ATK,
		SFX_SMALL_DOOR_SUBWAY,
		SFX_TRAIN_DOOR_OPEN,
		SFX_TRAIN_DOOR_CLOSE,
		SFX_VONCROY_KNIFE_SWISH,
		SFX_TRAIN_UNLINK_BREAK,
		SFX_OBJ_BOX_HIT,
		SFX_OBJ_BOX_HIT_CHANCE,
		SFX_OBJ_GEM_SMASH,
		SFX_CATBLADES_DRAW,
		SFX_SWIRLY_LONG_MOVE_SFX,
		SFX_FOOTSTEPS_MUD,
		SFX_HORSEMAN_HORSE_NEIGH,
		SFX_FOOTSTEPS_GRAVEL,
		SFX_FOOTSTEPS_SAND_GRASS,
		SFX_FOOTSTEPS_WOOD,
		SFX_FOOTSTEPS_MARBLE,
		SFX_FOOTSTEPS_METAL,
		SFX_GEN_SPHINX_DOORTHD,
		SFX_SETT_PLASMA_1,
		SFX_SETT_BOLT_1,
		SFX_SETT_FEET,
		SFX_SETT_NRG_CHARGE,
		SFX_SETT_NRG_CHARGE2,
		SFX_HORSEMAN_TAKEHIT,
		SFX_HORSEMAN_WALK,
		SFX_HORSEMAN_GRUNT,
		SFX_HORSEMAN_FALL,
		SFX_HORSEMAN_DIE,
		SFX_MAPPER_SWITCH_ON,
		SFX_MAPPER_OPEN,
		SFX_MAPPER_LAZER,
		SFX_MAPPER_MOVE,
		SFX_MAPPER_CLUNK,
		SFX_BLADES_DRAW,
		SFX_BLADES_CLASH_LOUD,
		SFX_BLADES_CLASH_QUIET,
		SFX_HAMMER_TRAP_BANG,
		SFX_DOOR_BIG_STONE,
		SFX_SETT_BIG_ROAR,
		SFX_BABOON_CHATTER,
		SFX_BABOON_ROLL,
		SFX_SWOOSH_SWIRLY_DOUBLE,
		SFX_DOOR_SETTDOOR_SQK,
		SFX_DOOR_SETTDOOR_CLANK,
		SFX_SETT_JUMP_ATTACK,
		SFX_JOBY_BLOCK,
		SFX_SETT_TAKE_HIT,
		SFX_DART_SPITT,
		SFX_LARA_CROWBAR_GEM,
		SFX_CROWBAR_DOOR_OPEN,
		SFX_LARA_LEVER_GEN_SQKS,
		SFX_HORSEMAN_GETUP,
		SFX_EXH_BASKET_OPEN,
		SFX_EXH_MUMCOFF_OPE1,
		SFX_EXH_MUMCOFF_OPE2,
		SFX_EXH_MUM_JOLT,
		SFX_EXH_MUMHEAD_SPIN,
		SFX_EXH_MUMMY_RAHHH,
		SFX_EXH_ROLLER_BLINDS,
		SFX_LARA_LEVER_PART1,
		SFX_LARA_LEVER_PART2,
		SFX_LARA_POLE_CLIMB,
		SFX_LARA_POLE_LOOP,
		SFX_TRAP_SPIKEBALL_SPK,
		SFX_LARA_PULLEY,
		SFX_TEETH_SPIKES,
		SFX_SAND_LOOP,
		SFX_LARA_USE_OBJECT,
		SFX_LIBRARY_COG_SQKS,
		SFX_HIT_ROCK,
		SFX_LARA_NO_FRENCH,
		SFX_LARA_NO_JAPAN,
		SFX_LARA_CROW_WRENCH,
		SFX_LARA_ROPE_CREAK,
		SFX_BOWLANIM,
		SFX_SPHINX_DOOR_WOODCRACK,
		SFX_BEETLE_CLK_WHIRR1,
		SFX_MAPPER_PYRAMID_OPEN,
		SFX_LIGHT_BEAM_JOBY,
		SFX_GUIDE_FIRE_LIGHT,
		SFX_AUTOGUNS,
		SFX_PULLEY_ANDY,
		SFX_STEAM,
		SFX_JOBY_GARAGE_DOOR,
		SFX_JOBY_WIND,
		SFX_SANDHAM_IN_THE_HOUSE,
		SFX_SANDHAM_CONVEYS,
		SFX_CRANKY_GRAPE_CRUSH,
		SFX_BIKE_HIT_OBJECTS,
		SFX_BIKE_HIT_ENEMIES,
		SFX_FLAME_EMITTER,
		SFX_LARA_CLICK_SWITCH,

		NumSamples
	};

	enum class matrix_indices
	{
		M00, M01, M02, M03,
		M10, M11, M12, M13,
		M20, M21, M22, M23,

		indices_count
	};

	enum class object_types
	{
		LARA,
		PISTOLS_ANIM,
		UZI_ANIM,
		SHOTGUN_ANIM,
		CROSSBOW_ANIM,
		GRENADE_GUN_ANIM,
		SIXSHOOTER_ANIM,
		FLARE_ANIM,
		LARA_SKIN,
		LARA_SKIN_JOINTS,
		LARA_SCREAM,
		LARA_CROSSBOW_LASER,
		LARA_REVOLVER_LASER,
		LARA_HOLSTERS,
		LARA_HOLSTERS_PISTOLS,
		LARA_HOLSTERS_UZIS,
		LARA_HOLSTERS_SIXSHOOTER,
		LARA_SPEECH_HEAD1,
		LARA_SPEECH_HEAD2,
		LARA_SPEECH_HEAD3,
		LARA_SPEECH_HEAD4,
		ACTOR1_SPEECH_HEAD1,
		ACTOR1_SPEECH_HEAD2,
		ACTOR2_SPEECH_HEAD1,
		ACTOR2_SPEECH_HEAD2,
		LARA_WATER_MESH,
		LARA_PETROL_MESH,
		LARA_DIRT_MESH,
		CROWBAR_ANIM,
		TORCH_ANIM,
		HAIR,
		MOTORBIKE,
		JEEP,
		VEHICLE_EXTRA,
		ENEMY_JEEP,
		SKELETON,
		SKELETON_MIP,
		GUIDE,
		GUIDE_MIP,
		VON_CROY,
		VON_CROY_MIP,
		BADDY_1,
		BADDY_1_MIP,
		BADDY_2,
		BADDY_2_MIP,
		SETHA,
		SETHA_MIP,
		MUMMY,
		MUMMY_MIP,
		SPHINX,
		SPHINX_MIP,
		CROCODILE,
		CROCODILE_MIP,
		HORSEMAN,
		HORSEMAN_MIP,
		SCORPION,
		SCORPION_MIP,
		JEAN_YVES,
		JEAN_YVES_MIP,
		TROOPS,
		TROOPS_MIP,
		KNIGHTS_TEMPLAR,
		KNIGHTS_TEMPLAR_MIP,
		MUTANT,
		MUTANT_MIP,
		HORSE,
		HORSE_MIP,
		BABOON_NORMAL,
		BABOON_NORMAL_MIP,
		BABOON_INV,
		BABOON_INV_MIP,
		BABOON_SILENT,
		BABOON_SILENT_MIP,
		WILD_BOAR,
		WILD_BOAR_MIP,
		HARPY,
		HARPY_MIP,
		DEMIGOD1,
		DEMIGOD1_MIP,
		DEMIGOD2,
		DEMIGOD2_MIP,
		DEMIGOD3,
		DEMIGOD3_MIP,
		LITTLE_BEETLE,
		BIG_BEETLE,
		BIG_BEETLE_MIP,
		WRAITH1,
		WRAITH2,
		WRAITH3,
		WRAITH4,
		BAT,
		DOG,
		DOG_MIP,
		HAMMERHEAD,
		HAMMERHEAD_MIP,
		SAS,
		SAS_MIP,
		SAS_DYING,
		SAS_DYING_MIP,
		SAS_CAPTAIN,
		SAS_CAPTAIN_MIP,
		SAS_DRAG_BLOKE,
		AHMET,
		AHMET_MIP,
		LARA_DOUBLE,
		LARA_DOUBLE_MIP,
		SMALL_SCORPION,
		LOCUST_EMITTER,
		GAME_PIECE1,
		GAME_PIECE2,
		GAME_PIECE3,
		ENEMY_PIECE,
		WHEEL_OF_FORTUNE,
		SCALES,
		DARTS,
		DART_EMITTER,
		HOMING_DART_EMITTER,
		FALLING_CEILING,
		FALLING_BLOCK,
		FALLING_BLOCK2,
		SMASHABLE_BIKE_WALL,
		SMASHABLE_BIKE_FLOOR,
		TRAPDOOR1,
		TRAPDOOR2,
		TRAPDOOR3,
		FLOOR_TRAPDOOR1,
		FLOOR_TRAPDOOR2,
		CEILING_TRAPDOOR1,
		CEILING_TRAPDOOR2,
		SCALING_TRAPDOOR,
		ROLLINGBALL,
		SPIKEY_FLOOR,
		TEETH_SPIKES,
		JOBY_SPIKES,
		SLICER_DICER,
		CHAIN,
		PLOUGH,
		STARGATE,
		HAMMER,
		BURNING_FLOOR,
		COG,
		SPIKEBALL,
		FLAME,
		FLAME_EMITTER,
		FLAME_EMITTER2,
		FLAME_EMITTER3,
		ROPE,
		FIREROPE,
		POLEROPE,
		ONEBLOCK_PLATFORM,
		TWOBLOCK_PLATFORM,
		RAISING_BLOCK1,
		RAISING_BLOCK2,
		EXPANDING_PLATFORM,
		SQUISHY_BLOCK1,
		SQUISHY_BLOCK2,
		PUSHABLE_OBJECT1,
		PUSHABLE_OBJECT2,
		PUSHABLE_OBJECT3,
		PUSHABLE_OBJECT4,
		PUSHABLE_OBJECT5,
		TRIPWIRE,
		SENTRY_GUN,
		MINE,
		MAPPER,
		OBELISK,
		FLOOR_4BLADE,
		ROOF_4BLADE,
		BIRD_BLADE,
		CATWALK_BLADE,
		MOVING_BLADE,
		PLINTH_BLADE,
		SETH_BLADE,
		LIGHTNING_CONDUCTOR,
		ELEMENT_PUZZLE,
		PUZZLE_ITEM1,
		PUZZLE_ITEM2,
		PUZZLE_ITEM3,
		PUZZLE_ITEM4,
		PUZZLE_ITEM5,
		PUZZLE_ITEM6,
		PUZZLE_ITEM7,
		PUZZLE_ITEM8,
		PUZZLE_ITEM9,
		PUZZLE_ITEM10,
		PUZZLE_ITEM11,
		PUZZLE_ITEM12,
		PUZZLE_ITEM1_COMBO1,
		PUZZLE_ITEM1_COMBO2,
		PUZZLE_ITEM2_COMBO1,
		PUZZLE_ITEM2_COMBO2,
		PUZZLE_ITEM3_COMBO1,
		PUZZLE_ITEM3_COMBO2,
		PUZZLE_ITEM4_COMBO1,
		PUZZLE_ITEM4_COMBO2,
		PUZZLE_ITEM5_COMBO1,
		PUZZLE_ITEM5_COMBO2,
		PUZZLE_ITEM6_COMBO1,
		PUZZLE_ITEM6_COMBO2,
		PUZZLE_ITEM7_COMBO1,
		PUZZLE_ITEM7_COMBO2,
		PUZZLE_ITEM8_COMBO1,
		PUZZLE_ITEM8_COMBO2,
		KEY_ITEM1,
		KEY_ITEM2,
		KEY_ITEM3,
		KEY_ITEM4,
		KEY_ITEM5,
		KEY_ITEM6,
		KEY_ITEM7,
		KEY_ITEM8,
		KEY_ITEM9,
		KEY_ITEM10,
		KEY_ITEM11,
		KEY_ITEM12,
		KEY_ITEM1_COMBO1,
		KEY_ITEM1_COMBO2,
		KEY_ITEM2_COMBO1,
		KEY_ITEM2_COMBO2,
		KEY_ITEM3_COMBO1,
		KEY_ITEM3_COMBO2,
		KEY_ITEM4_COMBO1,
		KEY_ITEM4_COMBO2,
		KEY_ITEM5_COMBO1,
		KEY_ITEM5_COMBO2,
		KEY_ITEM6_COMBO1,
		KEY_ITEM6_COMBO2,
		KEY_ITEM7_COMBO1,
		KEY_ITEM7_COMBO2,
		KEY_ITEM8_COMBO1,
		KEY_ITEM8_COMBO2,
		PICKUP_ITEM1,
		PICKUP_ITEM2,
		PICKUP_ITEM3,
		PICKUP_ITEM4,
		PICKUP_ITEM1_COMBO1,
		PICKUP_ITEM1_COMBO2,
		PICKUP_ITEM2_COMBO1,
		PICKUP_ITEM2_COMBO2,
		PICKUP_ITEM3_COMBO1,
		PICKUP_ITEM3_COMBO2,
		PICKUP_ITEM4_COMBO1,
		PICKUP_ITEM4_COMBO2,
		EXAMINE1,
		EXAMINE2,
		EXAMINE3,
		CROWBAR_ITEM,
		BURNING_TORCH_ITEM,
		CLOCKWORK_BEETLE,
		CLOCKWORK_BEETLE_COMBO1,
		CLOCKWORK_BEETLE_COMBO2,
		MINE_DETECTOR,
		QUEST_ITEM1,
		QUEST_ITEM2,
		QUEST_ITEM3,
		QUEST_ITEM4,
		QUEST_ITEM5,
		QUEST_ITEM6,
		MAP,
		SECRET_MAP,
		PUZZLE_HOLE1,
		PUZZLE_HOLE2,
		PUZZLE_HOLE3,
		PUZZLE_HOLE4,
		PUZZLE_HOLE5,
		PUZZLE_HOLE6,
		PUZZLE_HOLE7,
		PUZZLE_HOLE8,
		PUZZLE_HOLE9,
		PUZZLE_HOLE10,
		PUZZLE_HOLE11,
		PUZZLE_HOLE12,
		PUZZLE_DONE1,
		PUZZLE_DONE2,
		PUZZLE_DONE3,
		PUZZLE_DONE4,
		PUZZLE_DONE5,
		PUZZLE_DONE6,
		PUZZLE_DONE7,
		PUZZLE_DONE8,
		PUZZLE_DONE9,
		PUZZLE_DONE10,
		PUZZLE_DONE11,
		PUZZLE_DONE12,
		KEY_HOLE1,
		KEY_HOLE2,
		KEY_HOLE3,
		KEY_HOLE4,
		KEY_HOLE5,
		KEY_HOLE6,
		KEY_HOLE7,
		KEY_HOLE8,
		KEY_HOLE9,
		KEY_HOLE10,
		KEY_HOLE11,
		KEY_HOLE12,
		WATERSKIN1_EMPTY,
		WATERSKIN1_1,
		WATERSKIN1_2,
		WATERSKIN1_3,
		WATERSKIN2_EMPTY,
		WATERSKIN2_1,
		WATERSKIN2_2,
		WATERSKIN2_3,
		WATERSKIN2_4,
		WATERSKIN2_5,
		SWITCH_TYPE1,
		SWITCH_TYPE2,
		SWITCH_TYPE3,
		SWITCH_TYPE4,
		SWITCH_TYPE5,
		SWITCH_TYPE6,
		SWITCH_TYPE7,
		SWITCH_TYPE8,
		UNDERWATER_SWITCH1,
		UNDERWATER_SWITCH2,
		TURN_SWITCH,
		COG_SWITCH,
		LEVER_SWITCH,
		JUMP_SWITCH,
		CROWBAR_SWITCH,
		PULLEY,
		DOOR_TYPE1,
		DOOR_TYPE2,
		DOOR_TYPE3,
		DOOR_TYPE4,
		DOOR_TYPE5,
		DOOR_TYPE6,
		DOOR_TYPE7,
		DOOR_TYPE8,
		PUSHPULL_DOOR1,
		PUSHPULL_DOOR2,
		KICK_DOOR1,
		KICK_DOOR2,
		UNDERWATER_DOOR,
		DOUBLE_DOORS,
		BRIDGE_FLAT,
		BRIDGE_TILT1,
		BRIDGE_TILT2,
		SARCOPHAGUS,
		SEQUENCE_DOOR1,
		SEQUENCE_SWITCH1,
		SEQUENCE_SWITCH2,
		SEQUENCE_SWITCH3,
		SARCOPHAGUS_CUT,
		HORUS_STATUE,
		GOD_HEAD,
		SETH_DOOR,
		STATUE_PLINTH,
		PISTOLS_ITEM,
		PISTOLS_AMMO_ITEM,
		UZI_ITEM,
		UZI_AMMO_ITEM,
		SHOTGUN_ITEM,
		SHOTGUN_AMMO1_ITEM,
		SHOTGUN_AMMO2_ITEM,
		CROSSBOW_ITEM,
		CROSSBOW_AMMO1_ITEM,
		CROSSBOW_AMMO2_ITEM,
		CROSSBOW_AMMO3_ITEM,
		CROSSBOW_BOLT,
		GRENADE_GUN_ITEM,
		GRENADE_GUN_AMMO1_ITEM,
		GRENADE_GUN_AMMO2_ITEM,
		GRENADE_GUN_AMMO3_ITEM,
		GRENADE,
		SIXSHOOTER_ITEM,
		SIXSHOOTER_AMMO_ITEM,
		BIGMEDI_ITEM,
		SMALLMEDI_ITEM,
		LASERSIGHT_ITEM,
		BINOCULARS_ITEM,
		FLARE_ITEM,
		FLARE_INV_ITEM,
		DIARY_ITEM,
		COMPASS_ITEM,
		MEMCARD_LOAD_INV_ITEM,
		MEMCARD_SAVE_INV_ITEM,
		PC_LOAD_INV_ITEM,
		PC_SAVE_INV_ITEM,
		SMOKE_EMITTER_WHITE,
		SMOKE_EMITTER_BLACK,
		STEAM_EMITTER,
		EARTHQUAKE,
		BUBBLES,
		WATERFALLMIST,
		GUNSHELL,
		SHOTGUNSHELL,
		GUN_FLASH,
		BUTTERFLY,
		SPRINKLER,
		RED_LIGHT,
		GREEN_LIGHT,
		BLUE_LIGHT,
		AMBER_LIGHT,
		WHITE_LIGHT,
		BLINKING_LIGHT,
		LENS_FLARE,
		AI_GUARD,
		AI_AMBUSH,
		AI_PATROL1,
		AI_MODIFY,
		AI_FOLLOW,
		AI_PATROL2,
		AI_X1,
		AI_X2,
		LARA_START_POS,
		KILL_ALL_TRIGGERS,
		TRIGGER_TRIGGERER,
		SMASH_OBJECT1,
		SMASH_OBJECT2,
		SMASH_OBJECT3,
		SMASH_OBJECT4,
		SMASH_OBJECT5,
		SMASH_OBJECT6,
		SMASH_OBJECT7,
		SMASH_OBJECT8,
		MESHSWAP1,
		MESHSWAP2,
		MESHSWAP3,
		DEATH_SLIDE,
		BODY_PART,
		CAMERA_TARGET,
		WATERFALL1,
		WATERFALL2,
		WATERFALL3,
		PLANET_EFFECT,
		ANIMATING1,
		ANIMATING1_MIP,
		ANIMATING2,
		ANIMATING2_MIP,
		ANIMATING3,
		ANIMATING3_MIP,
		ANIMATING4,
		ANIMATING4_MIP,
		ANIMATING5,
		ANIMATING5_MIP,
		ANIMATING6,
		ANIMATING6_MIP,
		ANIMATING7,
		ANIMATING7_MIP,
		ANIMATING8,
		ANIMATING8_MIP,
		ANIMATING9,
		ANIMATING9_MIP,
		ANIMATING10,
		ANIMATING10_MIP,
		ANIMATING11,
		ANIMATING11_MIP,
		ANIMATING12,
		ANIMATING12_MIP,
		ANIMATING13,
		ANIMATING13_MIP,
		ANIMATING14,
		ANIMATING14_MIP,
		ANIMATING15,
		ANIMATING15_MIP,
		ANIMATING16,
		ANIMATING16_MIP,
		HORIZON,
		SKY_GRAPHICS,
		BINOCULAR_GRAPHICS,
		TARGET_GRAPHICS,
		DEFAULT_SPRITES,
		MISC_SPRITES,
		MOTOR_BOAT,
		MOTOR_BOAT_LARA,
		RUBBER_BOAT,
		RUBBER_BOAT_LARA,
		MOTORBIKE_LARA,
		FONT_GRAPHICS,
		PARALLEL_BARS,
		PANEL_BORDER,
		PANEL_MIDDLE,
		PANEL_CORNER,
		PANEL_DIAGONAL,
		PANEL_STRIP,
		PANEL_HALF_BORDER1,
		PANEL_HALF_BORDER2,
		PANEL_MIDDLE_CORNER,
		TIGHT_ROPE,
		LASER_HEAD,
		LASER_HEAD_BASE,
		LASER_HEAD_TENTACLE,
		HYDRA,
		HYDRA_MISSILE,
		ENEMY_SUB_MARINE,
		ENEMY_SUB_MARINE_MIP,
		SUB_MARINE_MISSILE,
		FROG_MAN,
		FROG_MAN_HARPOON,
		FISH_EMITTER,
		KAYAK,
		KAYAK_LARA,
		CUSTOM_SPRITES,
		BRIDGE_TILT3,
		BRIDGE_TILT4,
		BRIDGE_CUSTOM,
		ROBOT_CLEANER,
		ROBOT_STAR_WARS,
		MECH_WARRIOR,
		MECH_WARRIOR_LARA,
		UW_PROPULSOR,
		UW_PROPULSOR_LARA,
		MINE_CART,
		MINE_CART_LARA,
		NEW_SLOT5,
		NEW_SLOT6,
		NEW_SLOT7,
		NEW_SLOT8,
		NEW_SLOT9,
		NEW_SLOT10,
		NEW_SLOT11,
		NEW_SLOT12,
		NEW_SLOT13,
		NEW_SLOT14,
		NEW_SLOT15,
		NEW_SLOT16,
		NEW_SLOT17,
		NEW_SLOT18,
		NUMBER_OBJECTS
	};

	enum class static_types
	{
		PLANT0, PLANT1, PLANT2, PLANT3, PLANT4, PLANT5, PLANT6, PLANT7, PLANT8, PLANT9,
		FURNITURE0, FURNITURE1, FURNITURE2, FURNITURE3, FURNITURE4,
		FURNITURE5, FURNITURE6, FURNITURE7, FURNITURE8, FURNITURE9,
		ROCK0, ROCK1, ROCK2, ROCK3, ROCK4, ROCK5, ROCK6, ROCK7, ROCK8, ROCK9,
		ARCHITECTURE0, ARCHITECTURE1, ARCHITECTURE2, ARCHITECTURE3, ARCHITECTURE4,
		ARCHITECTURE5, ARCHITECTURE6, ARCHITECTURE7, ARCHITECTURE8, ARCHITECTURE9,
		DEBRIS0, DEBRIS1, DEBRIS2, DEBRIS3, DEBRIS4, DEBRIS5, DEBRIS6, DEBRIS7, DEBRIS8, DEBRIS9,
		SHATTER0, SHATTER1, SHATTER2, SHATTER3, SHATTER4, SHATTER5, SHATTER6, SHATTER7, SHATTER8, SHATTER9,
		EXTRA00, EXTRA01, EXTRA02, EXTRA03, EXTRA04, EXTRA05, EXTRA06, EXTRA07, EXTRA08, EXTRA09,
		EXTRA10, EXTRA11, EXTRA12, EXTRA13, EXTRA14, EXTRA15, EXTRA16, EXTRA17, EXTRA18, EXTRA19,
		EXTRA20, EXTRA21, EXTRA22, EXTRA23, EXTRA24, EXTRA25, EXTRA26, EXTRA27, EXTRA28, EXTRA29,
		EXTRA30, EXTRA31, EXTRA32, EXTRA33, EXTRA34, EXTRA35, EXTRA36, EXTRA37, EXTRA38, EXTRA39,
		EXTRA40, EXTRA41, EXTRA42, EXTRA43, EXTRA44, EXTRA45, EXTRA46, EXTRA47, EXTRA48, EXTRA49,
		EXTRA50, EXTRA51, EXTRA52, EXTRA53, EXTRA54, EXTRA55, EXTRA56, EXTRA57, EXTRA58, EXTRA59,
		EXTRA60, EXTRA61, EXTRA62, EXTRA63, EXTRA64, EXTRA65, EXTRA66, EXTRA67, EXTRA68, EXTRA69,
		EXTRA70, EXTRA71, EXTRA72, EXTRA73, EXTRA74, EXTRA75, EXTRA76, EXTRA77, EXTRA78, EXTRA79,
		EXTRA80, EXTRA81, EXTRA82, EXTRA83, EXTRA84, EXTRA85, EXTRA86, EXTRA87, EXTRA88, EXTRA89,
		EXTRA90, EXTRA91, EXTRA92, EXTRA93, EXTRA94, EXTRA95, EXTRA96, EXTRA97, EXTRA98, EXTRA99,
		EXTRA100, EXTRA101, EXTRA102, EXTRA103, EXTRA104, EXTRA105, EXTRA106, EXTRA107, EXTRA108, EXTRA109,
		EXTRA110, EXTRA111, EXTRA112, EXTRA113, EXTRA114, EXTRA115, EXTRA116, EXTRA117, EXTRA118, EXTRA119,
		EXTRA120, EXTRA121, EXTRA122, EXTRA123, EXTRA124, EXTRA125, EXTRA126, EXTRA127, EXTRA128, EXTRA129,
		EXTRA130, EXTRA131, EXTRA132, EXTRA133, EXTRA134, EXTRA135, EXTRA136, EXTRA137, EXTRA138, EXTRA139,
		EXTRA140, EXTRA141, EXTRA142, EXTRA143, EXTRA144, EXTRA145, EXTRA146, EXTRA147, EXTRA148, EXTRA149,
		EXTRA150, EXTRA151, EXTRA152, EXTRA153, EXTRA154, EXTRA155, EXTRA156, EXTRA157, EXTRA158, EXTRA159,
		EXTRA160, EXTRA161, EXTRA162, EXTRA163, EXTRA164, EXTRA165, EXTRA166, EXTRA167, EXTRA168, EXTRA169,
		EXTRA170, EXTRA171, EXTRA172, EXTRA173, EXTRA174, EXTRA175, EXTRA176, EXTRA177, EXTRA178, EXTRA179,
		NUMBER_STATIC_OBJECTS
	};

	enum class ITEM_FLAGS
	{
		IFL_TRIGGERED =				0x20,
		IFL_SWITCH_ONESHOT =		0x40,	//oneshot for switch items
		IFL_ANTITRIGGER_ONESHOT =	0x80,	//oneshot for antitriggers
		IFL_INVISIBLE =				0x100,	//also used as oneshot for everything else
		IFL_CODEBITS =				0x3E00,
		IFL_REVERSE =				0x4000,
		IFL_CLEARBODY =				0x8000
	};

	enum class camera_type
	{
		CHASE_CAMERA,
		FIXED_CAMERA,
		LOOK_CAMERA,
		COMBAT_CAMERA,
		CINEMATIC_CAMERA,
		HEAVY_CAMERA,
	};

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

	struct FLOOR_INFO
	{
		ushort index;
		ushort fx : 4;
		ushort box : 11;
		ushort stopper : 1;
		uchar pit_room;
		char floor;
		uchar sky_room;
		char ceiling;
	};

	struct LIGHTINFO
	{
		long x;
		long y;
		long z;
		uchar r;
		uchar g;
		uchar b;
		uchar Type;
		short Intensity;
		float Inner;
		float Outer;
		float Length;
		float Cutoff;
		float nx;
		float ny;
		float nz;
	};

	struct MESH_INFO
	{
		long x;
		long y;
		long z;
		short y_rot;
		short shade;
		short Flags;
		short static_number;
	};

	struct PCLIGHT_INFO
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
		uchar Type;
		uchar Pad;
	};

	struct ROOM_INFO
	{
		short* data;
		short* door;
		FLOOR_INFO* floor;
		LIGHTINFO* light;
		MESH_INFO* mesh;
		long x;
		long y;
		long z;
		long minfloor;
		long maxceiling;
		short x_size;
		short y_size;
		long ambient;
		short num_lights;
		short num_meshes;
		uchar ReverbType;
		uchar FlipNumber;
		char MeshEffect;
		char bound_active;
		short left;
		short right;
		short top;
		short bottom;
		short test_left;
		short test_right;
		short test_top;
		short test_bottom;
		short item_number;
		short fx_number;
		short flipped_room;
		ushort flags;
		long nVerts;
		long nWaterVerts;
		long nShoreVerts;
		LPDIRECT3DVERTEXBUFFER SourceVB;
		short* FaceData;
		float posx;
		float posy;
		float posz;
		D3DVECTOR* vnormals;
		D3DVECTOR* fnormals;
		long* prelight;
		long* prelightwater;
		long watercalc;
		D3DVECTOR* verts;
		long gt3cnt;
		long gt4cnt;
		PCLIGHT_INFO* pclight;
	};

	struct BIKEINFO
	{
		short right_front_wheelrot;
		short right_back_wheelrot;
		long left_wheelrot;
		long velocity;
		long unused1;
		long pitch1;
		short move_angle;
		short extra_rotation;
		short rot_thing;
		long bike_turn;
		long pitch2;
		short flags;
		short light_intensity;
	};

	struct JEEPINFO
	{
		short right_front_wheelrot;
		short left_front_wheelrot;
		short left_back_wheelrot;
		short right_back_wheelrot;
		long velocity;
		long unused1;
		long pitch1;
		long turn_rate;
		long camera_angle;
		short move_angle;
		short extra_rotation;
		short rot_thing;
		long pitch2;
		short flags;
		short unused2;
		short gear;
	};

	struct ROPE_STRUCT
	{
		PHD_VECTOR Segment[24];
		PHD_VECTOR Velocity[24];
		PHD_VECTOR NormalisedSegment[24];
		PHD_VECTOR MeshSegment[24];
		PHD_VECTOR Position;
		long Coords[24][3];
		long SegmentLength;
		long Active;
	};

	struct PENDULUM
	{
		PHD_VECTOR Position;
		PHD_VECTOR Velocity;
		long node;
		ROPE_STRUCT* Rope;
	};

	struct GAME_VECTOR
	{
		long x;
		long y;
		long z;
		short room_number;
		short box_number;
	};

	struct OBJECT_VECTOR
	{
		long x;
		long y;
		long z;
		short data;
		short flags;
	};

	struct CAMERA_INFO
	{
		GAME_VECTOR pos;
		GAME_VECTOR target;
		camera_type type;
		camera_type old_type;
		long shift;
		long flags;
		long fixed_camera;
		long number_frames;
		long bounce;
		long underwater;
		long target_distance;
		short target_angle;
		short target_elevation;
		short actual_elevation;
		short actual_angle;
		short number;
		short last;
		short timer;
		short speed;
		ITEM_INFO* item;
		ITEM_INFO* last_item;
		OBJECT_VECTOR* fixed;
		long mike_at_lara;
		PHD_VECTOR mike_pos;
	};

	struct SPOTCAM
	{
		long x;
		long y;
		long z;
		long tx;
		long ty;
		long tz;
		uchar sequence;
		uchar camera;
		short fov;
		short roll;
		short timer;
		short speed;
		short flags;
		short room_number;
		short pad;
	};

	struct SCARAB_STRUCT
	{
		PHD_3DPOS pos;
		short room_number;
		short speed;
		short fallspeed;
		uchar On;
		uchar flags;
	};

	struct DXDISPLAYMODE
	{
		long w;
		long h;
		long bpp;
		long RefreshRate;
		long bPalette;
		DDSURFACEDESC2 ddsd;
		uchar rbpp;
		uchar gbpp;
		uchar bbpp;
		uchar rshift;
		uchar gshift;
		uchar bshift;
	};

	struct DXTEXTUREINFO
	{
		DDPIXELFORMAT ddpf;
		ulong bpp;
		long bPalette;
		long bAlpha;
		uchar rbpp;
		uchar gbpp;
		uchar bbpp;
		uchar abpp;
		uchar rshift;
		uchar gshift;
		uchar bshift;
		uchar ashift;
	};

	struct DXZBUFFERINFO
	{
		DDPIXELFORMAT ddpf;
		ulong bpp;
	};

	struct DXD3DDEVICE
	{
		char Name[30];
		char About[80];
		LPGUID lpGuid;
		GUID Guid;
		D3DDEVICEDESC DeviceDesc;
		long bHardware;
		long nDisplayModes;
		DXDISPLAYMODE* DisplayModes;
		long nTextureInfos;
		DXTEXTUREINFO* TextureInfos;
		long nZBufferInfos;
		DXZBUFFERINFO* ZBufferInfos;
	};

	struct DXDIRECTDRAWINFO
	{
		char Name[30];
		char About[80];
		LPGUID lpGuid;
		GUID Guid;
		DDCAPS DDCaps;
		DDDEVICEIDENTIFIER DDIdentifier;
		int	 nDisplayModes;
		DXDISPLAYMODE* DisplayModes;
		int nD3DDevices;
		DXD3DDEVICE* D3DDevices;
	};

	struct DXDIRECTSOUNDINFO
	{
		char Name[30];
		char About[80];
		LPGUID lpGuid;
		GUID Guid;
	};

	struct DXINFO
	{
		long nDDInfo;
		long nDSInfo;
		DXDIRECTDRAWINFO* DDInfo;
		DXDIRECTSOUNDINFO* DSInfo;
		long nDD;
		long nD3D;
		long nDisplayMode;
		long nTexture;
		long nZBuffer;
		long nDS;
		bool bHardware;
	};

	struct DXPTR
	{
		LPDIRECTDRAW4 lpDD;
		LPDIRECT3D3 lpD3D;
		LPDIRECT3DDEVICE3 lpD3DDevice;
		LPDIRECT3DDEVICE3 _lpD3DDevice;
		LPDIRECTDRAWSURFACE4 lpPrimaryBuffer;
		LPDIRECTDRAWSURFACE4 lpBackBuffer;
		LPDIRECTDRAWSURFACE4 lpZBuffer;
		LPDIRECT3DVIEWPORT3 lpViewport;
		LPDIRECTSOUND lpDS;
		ulong dwRenderWidth;
		ulong dwRenderHeight;
		RECT rViewport;
		RECT rScreen;
		long Flags;
		long WindowStyle;
		long CoopLevel;
		LPDIRECTINPUT2 lpDirectInput;
		LPDIRECTINPUTDEVICE2 Keyboard;
		HWND hWnd;
		volatile long InScene;
		volatile long WaitAtBeginScene;
		volatile long DoneBlit;
	};

	struct WINAPP
	{
		HINSTANCE hInstance;
		HWND hWnd;
		WNDCLASS WindowClass;
		DXINFO DXInfo;
		DXPTR dx;
		HANDLE mutex;
		float fps;
		LPDIRECT3DMATERIAL3 GlobalMaterial;
		D3DMATERIALHANDLE GlobalMaterialHandle;
		HACCEL hAccel;
		bool SetupComplete;
		bool BumpMapping;
		long TextureSize;
		long BumpMapSize;
		bool mmx;
		bool Filtering;
		bool Volumetric;
		bool SoundDisabled;
		long StartFlags;
		volatile bool fmv;
		long Desktopbpp;
		long AutoTarget;
	};
#pragma pack(pop)
}
