#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "bass.h"

namespace trng {
	inline constexpr int MAX_ALLOCATA = 5000;
	inline constexpr int MAX_PARAM_WTEXT = 100;
	inline constexpr int MAX_OLD_FLIPEFFECT = 512;
	inline constexpr int MAX_FMV = 128;
	inline constexpr int MAX_ACTIONS = 100;
	inline constexpr int MAX_OLD_ACTIONS = 512;
	inline constexpr int MAX_TEX_SEQUENCE = 100;
	inline constexpr int MAX_GLOBAL_TRIGGERS = 500;
	inline constexpr int MAX_RAIN_PARTICLES = 0x1A00;
	inline constexpr int MAX_SNOW_PARTICLES = 0x1A00;
	inline constexpr int MAX_ELEVATORS = 20;
	inline constexpr int MAX_ELEVATOR_DOORS = 10;
	inline constexpr int MAX_FRAME_ITEMS = 200;
	inline constexpr int MAX_MIRRORS = 100;
	inline constexpr int MAX_OFFSET_HARD_BREAK = 500;
	inline constexpr int MAX_EQUIP_ITEM = 100;
	inline constexpr int MAX_ENV_CONDITIONS = 100;
	inline constexpr int MAX_ENV_SCRIPT_CONDITIONS = 256;
	inline constexpr int MAX_SWAP_MESH = 100;
	inline constexpr int MAX_TRIGGER_GROUPS = 1000;
	inline constexpr int MAX_TRIGGERS_IN_THE_GROUP = 64;
	inline constexpr int MAX_OLD_CONDITIONS = 512;
	inline constexpr int MAX_COLLISIONI = 20;
	inline constexpr int MAX_ORGANIZE_COPPIE = 100;
	inline constexpr int MAX_ORGANIZERS = 500;
	inline constexpr int MAX_IMPORT_FILES = 200;
	inline constexpr int MAX_ITEM_GROUPS = 100;
	inline constexpr int MAX_COLORI_RGB = 200;
	inline constexpr int MAX_WATCH = 32;
	inline constexpr int MAX_ITEMS = 1024;
	inline constexpr int MAX_ADD_EFFECTS = 100;
	inline constexpr int MAX_MOVE_ADVANCE = 100;
	inline constexpr int MAX_SFX_MANCANTI = 10;
	inline constexpr int MAX_SUONATI = 10;
	inline constexpr int MAX_TEMPI_FPS = 32;
	inline constexpr int MAX_MOVE_PARAM = 100;
	inline constexpr int MAX_ROTATE_PARAM = 100;
	inline constexpr int MAX_COLORA_ITEM = 100;
	inline constexpr int MAX_TIMER_OGGETTI = 200;
	inline constexpr int MAX_ANIM_MORTE = 20;
	inline constexpr int MAX_DEAD_ANIM = 100;
	inline constexpr int MAX_PARAM_PRINT_TEXT = 100;
	inline constexpr int MAX_STRINGE_TR5 = 30;
	inline constexpr int MAX_TEST_POSITION = 100;
	inline constexpr int MAX_ANIM_DIAGNOSTIC = 20;
	inline constexpr int MAX_SET_CAMERA = 100;
	inline constexpr int MAX_ALLOCA = 200;
	inline constexpr int MAX_IMAGES = 200;
	inline constexpr int MAX_STRINGHE_DIARIO = 200;
	inline constexpr int MAX_PAGINE_DIARIO = 200;
	inline constexpr int MAX_FONTS = 100;
	inline constexpr int MAX_DIARI = 100;
	inline constexpr int MAX_ROOMS = 512;
	inline constexpr int MAX_EVENTI_NOW = 100;
	inline constexpr int MAX_SWITCH = 128;
	inline constexpr int MAX_FREEZE = 256;
	inline constexpr int MAX_TEX_PER_FRAME = 16;
	inline constexpr int MAX_COLL_DISABLED = 256;
	inline constexpr int MAX_VEICOLI = 50;
	inline constexpr int MAX_TAIL_INFOS = 1024;
	inline constexpr int MAX_FLOODS = 100;
	inline constexpr int MAX_DART_CUST = 50;
	inline constexpr int MAX_STANDBY = 50;
	inline constexpr int MAX_ASSIGN_SLOT = 400;
	inline constexpr int MAX_ROLL_BOATS = 80;
	inline constexpr int MAX_ROLL_BOAT_SCRIPT = 40;
	inline constexpr int MAX_SCALE_ITEM = 100;
	inline constexpr int MAX_SHOW_SPRITES = 100;
	inline constexpr int MAX_CUST_SFX = 100;
	inline constexpr int MAX_TRIANGLES = 256;
	inline constexpr int MAX_QUADS = 256;
	inline constexpr int MAX_CIRCLES = 256;
	inline constexpr int MAX_TARGET_LEVELS = 100;
	inline constexpr int MAX_SHOW_MESH = 200;
	inline constexpr int MAX_SLOT_COLLIDE = 400;
	inline constexpr int MAX_ANIM_SCRIPT = 256;
	inline constexpr int MAX_ANIM_OBJ_SCRIPT = 512;
	inline constexpr int MAX_REMAPPED_ZONES = 200;
	inline constexpr int MAX_PARAM_LIGHTNING = 100;
	inline constexpr int MAX_NOMI_SLOT = 600;
	inline constexpr int MAX_ENEMY_SCRIPT = 100;
	inline constexpr int MAX_DGX_OLD_ERRORS = 1000;
	inline constexpr int MAX_DGX_NEW_ERRORS = 10;
	inline constexpr int MAX_IMAGE_RECORDS = 30;
	inline constexpr int MAX_MY_RECT = 300;
	inline constexpr int MAX_INPUT_BOX = 100;
	inline constexpr int MAX_EXTRA_SCAN_CODES = 64;
	inline constexpr int MAX_SLOT_FLAGS = 500;
	inline constexpr int MAX_TIMING = 12;
	inline constexpr int MAX_DEMO_FRAMES = 54000;
	inline constexpr int MAX_DEMO_IDS = 200;
	inline constexpr int MAX_ACTORS = 100;
	inline constexpr int MAX_BASIC_COLLISIONS = 100;
	inline constexpr int MAX_SWAP_ANIM = 100;
	inline constexpr int MAX_MEM_SWAP_ANIM = 100;
	inline constexpr int MAX_SPEECH_PARAM = 100;
	inline constexpr int MAX_SPEECH_COMMANDS = 100;
	inline constexpr int MAX_ACTOR_SPEECHING = 3;
	inline constexpr int MAX_FLIP_MESH = 100;
	inline constexpr int MAX_NEW_ITEMS = 256;
	inline constexpr int MAX_PLUGINS_NGLE = 256;
	inline constexpr int MAX_EXTRA_EFFECT = 20;
	inline constexpr int MAX_STATIC_MIP = 160;
	inline constexpr int MAX_SALVA_CORD = 1024;

	// index to access to GlobTomb4.VetStringOffsets[]
	// Print OFFset
	inline constexpr int POFF_MainMenu = 0;
	inline constexpr int POFF_NewGameTitle = 1;
	inline constexpr int POFF_LoadGameTitle = 2;
	inline constexpr int POFF_NewGameList = 3;
	inline constexpr int POFF_LoadGameList = 4;
	inline constexpr int POFF_OptionSettings = 5;
	inline constexpr int POFF_OptionCmdList = 6;
	inline constexpr int POFF_PauseScreen = 7;
	inline constexpr int POFF_StatList = 8;
	inline constexpr int POFF_InventoryItemName = 9;
	inline constexpr int POFF_ExamineText = 10;
	inline constexpr int POFF_COUNTER = 11;

	// ----------- define for SLOT_ trigger constants -------------
	inline constexpr int SLOT_LARA = 0;		// [0] slot
	inline constexpr int SLOT_PISTOLS_ANIM = 1;		// [1] slot
	inline constexpr int SLOT_UZI_ANIM = 2;		// [2] slot
	inline constexpr int SLOT_SHOTGUN_ANIM = 3;		// [3] slot
	inline constexpr int SLOT_CROSSBOW_ANIM = 4;		// [4] slot
	inline constexpr int SLOT_GRENADE_GUN_ANIM = 5;		// [5] slot
	inline constexpr int SLOT_SIXSHOOTER_ANIM = 6;		// [6] slot
	inline constexpr int SLOT_FLARE_ANIM = 7;		// [7] slot
	inline constexpr int SLOT_LARA_SKIN = 8;		// [8] slot
	inline constexpr int SLOT_LARA_SKIN_JOINTS = 9;		// [9] slot
	inline constexpr int SLOT_LARA_SCREAM = 10;		// [10] slot
	inline constexpr int SLOT_LARA_CROSSBOW_LASER = 11;		// [11] slot
	inline constexpr int SLOT_LARA_REVOLVER_LASER = 12;		// [12] slot
	inline constexpr int SLOT_LARA_HOLSTERS = 13;		// [13] slot
	inline constexpr int SLOT_LARA_HOLSTERS_PISTOLS = 14;		// [14] slot
	inline constexpr int SLOT_LARA_HOLSTERS_UZIS = 15;		// [15] slot
	inline constexpr int SLOT_LARA_HOLSTERS_SIXSHOOTER = 16;		// [16] slot
	inline constexpr int SLOT_LARA_SPEECH_HEAD1 = 17;		// [17] slot
	inline constexpr int SLOT_LARA_SPEECH_HEAD2 = 18;		// [18] slot
	inline constexpr int SLOT_LARA_SPEECH_HEAD3 = 19;		// [19] slot
	inline constexpr int SLOT_LARA_SPEECH_HEAD4 = 20;		// [20] slot
	inline constexpr int SLOT_ACTOR1_SPEECH_HEAD1 = 21;		// [21] slot
	inline constexpr int SLOT_ACTOR1_SPEECH_HEAD2 = 22;		// [22] slot
	inline constexpr int SLOT_ACTOR2_SPEECH_HEAD1 = 23;		// [23] slot
	inline constexpr int SLOT_ACTOR2_SPEECH_HEAD2 = 24;		// [24] slot
	inline constexpr int SLOT_LARA_WATER_MESH = 25;		// [25] slot
	inline constexpr int SLOT_LARA_PETROL_MESH = 26;		// [26] slot
	inline constexpr int SLOT_LARA_DIRT_MESH = 27;		// [27] slot
	inline constexpr int SLOT_CROWBAR_ANIM = 28;		// [28] slot
	inline constexpr int SLOT_TORCH_ANIM = 29;		// [29] slot
	inline constexpr int SLOT_HAIR = 30;		// [30] slot
	inline constexpr int SLOT_MOTORBIKE = 31;		// [31] slot
	inline constexpr int SLOT_JEEP = 32;		// [32] slot
	inline constexpr int SLOT_VEHICLE_EXTRA = 33;		// [33] slot
	inline constexpr int SLOT_ENEMY_JEEP = 34;		// [34] slot
	inline constexpr int SLOT_SKELETON = 35;		// [35] slot
	inline constexpr int SLOT_SKELETON_MIP = 36;		// [36] slot
	inline constexpr int SLOT_GUIDE = 37;		// [37] slot
	inline constexpr int SLOT_GUIDE_MIP = 38;		// [38] slot
	inline constexpr int SLOT_VON_CROY = 39;		// [39] slot
	inline constexpr int SLOT_VON_CROY_MIP = 40;		// [40] slot
	inline constexpr int SLOT_BADDY_1 = 41;		// [41] slot
	inline constexpr int SLOT_BADDY_1_MIP = 42;		// [42] slot
	inline constexpr int SLOT_BADDY_2 = 43;		// [43] slot
	inline constexpr int SLOT_BADDY_2_MIP = 44;		// [44] slot
	inline constexpr int SLOT_SETHA = 45;		// [45] slot
	inline constexpr int SLOT_SETHA_MIP = 46;		// [46] slot
	inline constexpr int SLOT_MUMMY = 47;		// [47] slot
	inline constexpr int SLOT_MUMMY_MIP = 48;		// [48] slot
	inline constexpr int SLOT_SPHINX = 49;		// [49] slot
	inline constexpr int SLOT_SPHINX_MIP = 50;		// [50] slot
	inline constexpr int SLOT_CROCODILE = 51;		// [51] slot
	inline constexpr int SLOT_CROCODILE_MIP = 52;		// [52] slot
	inline constexpr int SLOT_HORSEMAN = 53;		// [53] slot
	inline constexpr int SLOT_HORSEMAN_MIP = 54;		// [54] slot
	inline constexpr int SLOT_SCORPION = 55;		// [55] slot
	inline constexpr int SLOT_SCORPION_MIP = 56;		// [56] slot
	inline constexpr int SLOT_JEAN_YVES = 57;		// [57] slot
	inline constexpr int SLOT_JEAN_YVES_MIP = 58;		// [58] slot
	inline constexpr int SLOT_TROOPS = 59;		// [59] slot
	inline constexpr int SLOT_TROOPS_MIP = 60;		// [60] slot
	inline constexpr int SLOT_KNIGHTS_TEMPLAR = 61;		// [61] slot
	inline constexpr int SLOT_KNIGHTS_TEMPLAR_MIP = 62;		// [62] slot
	inline constexpr int SLOT_MUTANT = 63;		// [63] slot
	inline constexpr int SLOT_MUTANT_MIP = 64;		// [64] slot
	inline constexpr int SLOT_HORSE = 65;		// [65] slot
	inline constexpr int SLOT_HORSE_MIP = 66;		// [66] slot
	inline constexpr int SLOT_BABOON_NORMAL = 67;		// [67] slot
	inline constexpr int SLOT_BABOON_NORMAL_MIP = 68;		// [68] slot
	inline constexpr int SLOT_BABOON_INV = 69;		// [69] slot
	inline constexpr int SLOT_BABOON_INV_MIP = 70;		// [70] slot
	inline constexpr int SLOT_BABOON_SILENT = 71;		// [71] slot
	inline constexpr int SLOT_BABOON_SILENT_MIP = 72;		// [72] slot
	inline constexpr int SLOT_WILD_BOAR = 73;		// [73] slot
	inline constexpr int SLOT_WILD_BOAR_MIP = 74;		// [74] slot
	inline constexpr int SLOT_HARPY = 75;		// [75] slot
	inline constexpr int SLOT_HARPY_MIP = 76;		// [76] slot
	inline constexpr int SLOT_DEMIGOD1 = 77;		// [77] slot
	inline constexpr int SLOT_DEMIGOD1_MIP = 78;		// [78] slot
	inline constexpr int SLOT_DEMIGOD2 = 79;		// [79] slot
	inline constexpr int SLOT_DEMIGOD2_MIP = 80;		// [80] slot
	inline constexpr int SLOT_DEMIGOD3 = 81;		// [81] slot
	inline constexpr int SLOT_DEMIGOD3_MIP = 82;		// [82] slot
	inline constexpr int SLOT_LITTLE_BEETLE = 83;		// [83] slot
	inline constexpr int SLOT_BIG_BEETLE = 84;		// [84] slot
	inline constexpr int SLOT_BIG_BEETLE_MIP = 85;		// [85] slot
	inline constexpr int SLOT_WRAITH1 = 86;		// [86] slot
	inline constexpr int SLOT_WRAITH2 = 87;		// [87] slot
	inline constexpr int SLOT_WRAITH3 = 88;		// [88] slot
	inline constexpr int SLOT_WRAITH4 = 89;		// [89] slot
	inline constexpr int SLOT_BAT = 90;		// [90] slot
	inline constexpr int SLOT_DOG = 91;		// [91] slot
	inline constexpr int SLOT_DOG_MIP = 92;		// [92] slot
	inline constexpr int SLOT_HAMMERHEAD = 93;		// [93] slot
	inline constexpr int SLOT_HAMMERHEAD_MIP = 94;		// [94] slot
	inline constexpr int SLOT_SAS = 95;		// [95] slot
	inline constexpr int SLOT_SAS_MIP = 96;		// [96] slot
	inline constexpr int SLOT_SAS_DYING = 97;		// [97] slot
	inline constexpr int SLOT_SAS_DYING_MIP = 98;		// [98] slot
	inline constexpr int SLOT_SAS_CAPTAIN = 99;		// [99] slot
	inline constexpr int SLOT_SAS_CAPTAIN_MIP = 100;		// [100] slot
	inline constexpr int SLOT_SAS_DRAG_BLOKE = 101;		// [101] slot
	inline constexpr int SLOT_AHMET = 102;		// [102] slot
	inline constexpr int SLOT_AHMET_MIP = 103;		// [103] slot
	inline constexpr int SLOT_LARA_DOUBLE = 104;		// [104] slot
	inline constexpr int SLOT_LARA_DOUBLE_MIP = 105;		// [105] slot
	inline constexpr int SLOT_SMALL_SCORPION = 106;		// [106] slot
	inline constexpr int SLOT_LOCUST_EMITTER = 107;		// [107] slot
	inline constexpr int SLOT_GAME_PIECE1 = 108;		// [108] slot
	inline constexpr int SLOT_GAME_PIECE2 = 109;		// [109] slot
	inline constexpr int SLOT_GAME_PIECE3 = 110;		// [110] slot
	inline constexpr int SLOT_ENEMY_PIECE = 111;		// [111] slot
	inline constexpr int SLOT_WHEEL_OF_FORTUNE = 112;		// [112] slot
	inline constexpr int SLOT_SCALES = 113;		// [113] slot
	inline constexpr int SLOT_DARTS = 114;		// [114] slot
	inline constexpr int SLOT_DART_EMITTER = 115;		// [115] slot
	inline constexpr int SLOT_HOMING_DART_EMITTER = 116;		// [116] slot
	inline constexpr int SLOT_FALLING_CEILING = 117;		// [117] slot
	inline constexpr int SLOT_FALLING_BLOCK = 118;		// [118] slot
	inline constexpr int SLOT_FALLING_BLOCK2 = 119;		// [119] slot
	inline constexpr int SLOT_SMASHABLE_BIKE_WALL = 120;		// [120] slot
	inline constexpr int SLOT_SMASHABLE_BIKE_FLOOR = 121;		// [121] slot
	inline constexpr int SLOT_TRAPDOOR1 = 122;		// [122] slot
	inline constexpr int SLOT_TRAPDOOR2 = 123;		// [123] slot
	inline constexpr int SLOT_TRAPDOOR3 = 124;		// [124] slot
	inline constexpr int SLOT_FLOOR_TRAPDOOR1 = 125;		// [125] slot
	inline constexpr int SLOT_FLOOR_TRAPDOOR2 = 126;		// [126] slot
	inline constexpr int SLOT_CEILING_TRAPDOOR1 = 127;		// [127] slot
	inline constexpr int SLOT_CEILING_TRAPDOOR2 = 128;		// [128] slot
	inline constexpr int SLOT_SCALING_TRAPDOOR = 129;		// [129] slot
	inline constexpr int SLOT_ROLLINGBALL = 130;		// [130] slot
	inline constexpr int SLOT_SPIKEY_FLOOR = 131;		// [131] slot
	inline constexpr int SLOT_TEETH_SPIKES = 132;		// [132] slot
	inline constexpr int SLOT_JOBY_SPIKES = 133;		// [133] slot
	inline constexpr int SLOT_SLICER_DICER = 134;		// [134] slot
	inline constexpr int SLOT_CHAIN = 135;		// [135] slot
	inline constexpr int SLOT_PLOUGH = 136;		// [136] slot
	inline constexpr int SLOT_STARGATE = 137;		// [137] slot
	inline constexpr int SLOT_HAMMER = 138;		// [138] slot
	inline constexpr int SLOT_BURNING_FLOOR = 139;		// [139] slot
	inline constexpr int SLOT_COG = 140;		// [140] slot
	inline constexpr int SLOT_SPIKEBALL = 141;		// [141] slot
	inline constexpr int SLOT_FLAME = 142;		// [142] slot
	inline constexpr int SLOT_FLAME_EMITTER = 143;		// [143] slot
	inline constexpr int SLOT_FLAME_EMITTER2 = 144;		// [144] slot
	inline constexpr int SLOT_FLAME_EMITTER3 = 145;		// [145] slot
	inline constexpr int SLOT_ROPE = 146;		// [146] slot
	inline constexpr int SLOT_FIREROPE = 147;		// [147] slot
	inline constexpr int SLOT_POLEROPE = 148;		// [148] slot
	inline constexpr int SLOT_ONEBLOCK_PLATFORM = 149;		// [149] slot
	inline constexpr int SLOT_TWOBLOCK_PLATFORM = 150;		// [150] slot
	inline constexpr int SLOT_RAISING_BLOCK1 = 151;		// [151] slot
	inline constexpr int SLOT_RAISING_BLOCK2 = 152;		// [152] slot
	inline constexpr int SLOT_EXPANDING_PLATFORM = 153;		// [153] slot
	inline constexpr int SLOT_SQUISHY_BLOCK1 = 154;		// [154] slot
	inline constexpr int SLOT_SQUISHY_BLOCK2 = 155;		// [155] slot
	inline constexpr int SLOT_PUSHABLE_OBJECT1 = 156;		// [156] slot
	inline constexpr int SLOT_PUSHABLE_OBJECT2 = 157;		// [157] slot
	inline constexpr int SLOT_PUSHABLE_OBJECT3 = 158;		// [158] slot
	inline constexpr int SLOT_PUSHABLE_OBJECT4 = 159;		// [159] slot
	inline constexpr int SLOT_PUSHABLE_OBJECT5 = 160;		// [160] slot
	inline constexpr int SLOT_TRIPWIRE = 161;		// [161] slot
	inline constexpr int SLOT_SENTRY_GUN = 162;		// [162] slot
	inline constexpr int SLOT_MINE = 163;		// [163] slot
	inline constexpr int SLOT_MAPPER = 164;		// [164] slot
	inline constexpr int SLOT_OBELISK = 165;		// [165] slot
	inline constexpr int SLOT_FLOOR_4BLADE = 166;		// [166] slot
	inline constexpr int SLOT_ROOF_4BLADE = 167;		// [167] slot
	inline constexpr int SLOT_BIRD_BLADE = 168;		// [168] slot
	inline constexpr int SLOT_CATWALK_BLADE = 169;		// [169] slot
	inline constexpr int SLOT_MOVING_BLADE = 170;		// [170] slot
	inline constexpr int SLOT_PLINTH_BLADE = 171;		// [171] slot
	inline constexpr int SLOT_SETH_BLADE = 172;		// [172] slot
	inline constexpr int SLOT_LIGHTNING_CONDUCTOR = 173;		// [173] slot
	inline constexpr int SLOT_ELEMENT_PUZZLE = 174;		// [174] slot
	inline constexpr int SLOT_PUZZLE_ITEM1 = 175;		// [175] slot
	inline constexpr int SLOT_PUZZLE_ITEM2 = 176;		// [176] slot
	inline constexpr int SLOT_PUZZLE_ITEM3 = 177;		// [177] slot
	inline constexpr int SLOT_PUZZLE_ITEM4 = 178;		// [178] slot
	inline constexpr int SLOT_PUZZLE_ITEM5 = 179;		// [179] slot
	inline constexpr int SLOT_PUZZLE_ITEM6 = 180;		// [180] slot
	inline constexpr int SLOT_PUZZLE_ITEM7 = 181;		// [181] slot
	inline constexpr int SLOT_PUZZLE_ITEM8 = 182;		// [182] slot
	inline constexpr int SLOT_PUZZLE_ITEM9 = 183;		// [183] slot
	inline constexpr int SLOT_PUZZLE_ITEM10 = 184;		// [184] slot
	inline constexpr int SLOT_PUZZLE_ITEM11 = 185;		// [185] slot
	inline constexpr int SLOT_PUZZLE_ITEM12 = 186;		// [186] slot
	inline constexpr int SLOT_PUZZLE_ITEM1_COMBO1 = 187;		// [187] slot
	inline constexpr int SLOT_PUZZLE_ITEM1_COMBO2 = 188;		// [188] slot
	inline constexpr int SLOT_PUZZLE_ITEM2_COMBO1 = 189;		// [189] slot
	inline constexpr int SLOT_PUZZLE_ITEM2_COMBO2 = 190;		// [190] slot
	inline constexpr int SLOT_PUZZLE_ITEM3_COMBO1 = 191;		// [191] slot
	inline constexpr int SLOT_PUZZLE_ITEM3_COMBO2 = 192;		// [192] slot
	inline constexpr int SLOT_PUZZLE_ITEM4_COMBO1 = 193;		// [193] slot
	inline constexpr int SLOT_PUZZLE_ITEM4_COMBO2 = 194;		// [194] slot
	inline constexpr int SLOT_PUZZLE_ITEM5_COMBO1 = 195;		// [195] slot
	inline constexpr int SLOT_PUZZLE_ITEM5_COMBO2 = 196;		// [196] slot
	inline constexpr int SLOT_PUZZLE_ITEM6_COMBO1 = 197;		// [197] slot
	inline constexpr int SLOT_PUZZLE_ITEM6_COMBO2 = 198;		// [198] slot
	inline constexpr int SLOT_PUZZLE_ITEM7_COMBO1 = 199;		// [199] slot
	inline constexpr int SLOT_PUZZLE_ITEM7_COMBO2 = 200;		// [200] slot
	inline constexpr int SLOT_PUZZLE_ITEM8_COMBO1 = 201;		// [201] slot
	inline constexpr int SLOT_PUZZLE_ITEM8_COMBO2 = 202;		// [202] slot
	inline constexpr int SLOT_KEY_ITEM1 = 203;		// [203] slot
	inline constexpr int SLOT_KEY_ITEM2 = 204;		// [204] slot
	inline constexpr int SLOT_KEY_ITEM3 = 205;		// [205] slot
	inline constexpr int SLOT_KEY_ITEM4 = 206;		// [206] slot
	inline constexpr int SLOT_KEY_ITEM5 = 207;		// [207] slot
	inline constexpr int SLOT_KEY_ITEM6 = 208;		// [208] slot
	inline constexpr int SLOT_KEY_ITEM7 = 209;		// [209] slot
	inline constexpr int SLOT_KEY_ITEM8 = 210;		// [210] slot
	inline constexpr int SLOT_KEY_ITEM9 = 211;		// [211] slot
	inline constexpr int SLOT_KEY_ITEM10 = 212;		// [212] slot
	inline constexpr int SLOT_KEY_ITEM11 = 213;		// [213] slot
	inline constexpr int SLOT_KEY_ITEM12 = 214;		// [214] slot
	inline constexpr int SLOT_KEY_ITEM1_COMBO1 = 215;		// [215] slot
	inline constexpr int SLOT_KEY_ITEM1_COMBO2 = 216;		// [216] slot
	inline constexpr int SLOT_KEY_ITEM2_COMBO1 = 217;		// [217] slot
	inline constexpr int SLOT_KEY_ITEM2_COMBO2 = 218;		// [218] slot
	inline constexpr int SLOT_KEY_ITEM3_COMBO1 = 219;		// [219] slot
	inline constexpr int SLOT_KEY_ITEM3_COMBO2 = 220;		// [220] slot
	inline constexpr int SLOT_KEY_ITEM4_COMBO1 = 221;		// [221] slot
	inline constexpr int SLOT_KEY_ITEM4_COMBO2 = 222;		// [222] slot
	inline constexpr int SLOT_KEY_ITEM5_COMBO1 = 223;		// [223] slot
	inline constexpr int SLOT_KEY_ITEM5_COMBO2 = 224;		// [224] slot
	inline constexpr int SLOT_KEY_ITEM6_COMBO1 = 225;		// [225] slot
	inline constexpr int SLOT_KEY_ITEM6_COMBO2 = 226;		// [226] slot
	inline constexpr int SLOT_KEY_ITEM7_COMBO1 = 227;		// [227] slot
	inline constexpr int SLOT_KEY_ITEM7_COMBO2 = 228;		// [228] slot
	inline constexpr int SLOT_KEY_ITEM8_COMBO1 = 229;		// [229] slot
	inline constexpr int SLOT_KEY_ITEM8_COMBO2 = 230;		// [230] slot
	inline constexpr int SLOT_PICKUP_ITEM1 = 231;		// [231] slot
	inline constexpr int SLOT_PICKUP_ITEM2 = 232;		// [232] slot
	inline constexpr int SLOT_PICKUP_ITEM3 = 233;		// [233] slot
	inline constexpr int SLOT_PICKUP_ITEM4 = 234;		// [234] slot
	inline constexpr int SLOT_PICKUP_ITEM1_COMBO1 = 235;		// [235] slot
	inline constexpr int SLOT_PICKUP_ITEM1_COMBO2 = 236;		// [236] slot
	inline constexpr int SLOT_PICKUP_ITEM2_COMBO1 = 237;		// [237] slot
	inline constexpr int SLOT_PICKUP_ITEM2_COMBO2 = 238;		// [238] slot
	inline constexpr int SLOT_PICKUP_ITEM3_COMBO1 = 239;		// [239] slot
	inline constexpr int SLOT_PICKUP_ITEM3_COMBO2 = 240;		// [240] slot
	inline constexpr int SLOT_PICKUP_ITEM4_COMBO1 = 241;		// [241] slot
	inline constexpr int SLOT_PICKUP_ITEM4_COMBO2 = 242;		// [242] slot
	inline constexpr int SLOT_EXAMINE1 = 243;		// [243] slot
	inline constexpr int SLOT_EXAMINE2 = 244;		// [244] slot
	inline constexpr int SLOT_EXAMINE3 = 245;		// [245] slot
	inline constexpr int SLOT_CROWBAR_ITEM = 246;		// [246] slot
	inline constexpr int SLOT_BURNING_TORCH_ITEM = 247;		// [247] slot
	inline constexpr int SLOT_CLOCKWORK_BEETLE = 248;		// [248] slot
	inline constexpr int SLOT_CLOCKWORK_BEETLE_COMBO1 = 249;		// [249] slot
	inline constexpr int SLOT_CLOCKWORK_BEETLE_COMBO2 = 250;		// [250] slot
	inline constexpr int SLOT_MINE_DETECTOR = 251;		// [251] slot
	inline constexpr int SLOT_QUEST_ITEM1 = 252;		// [252] slot
	inline constexpr int SLOT_QUEST_ITEM2 = 253;		// [253] slot
	inline constexpr int SLOT_QUEST_ITEM3 = 254;		// [254] slot
	inline constexpr int SLOT_QUEST_ITEM4 = 255;		// [255] slot
	inline constexpr int SLOT_QUEST_ITEM5 = 256;		// [256] slot
	inline constexpr int SLOT_QUEST_ITEM6 = 257;		// [257] slot
	inline constexpr int SLOT_MAP = 258;		// [258] slot
	inline constexpr int SLOT_SECRET_MAP = 259;		// [259] slot
	inline constexpr int SLOT_PUZZLE_HOLE1 = 260;		// [260] slot
	inline constexpr int SLOT_PUZZLE_HOLE2 = 261;		// [261] slot
	inline constexpr int SLOT_PUZZLE_HOLE3 = 262;		// [262] slot
	inline constexpr int SLOT_PUZZLE_HOLE4 = 263;		// [263] slot
	inline constexpr int SLOT_PUZZLE_HOLE5 = 264;		// [264] slot
	inline constexpr int SLOT_PUZZLE_HOLE6 = 265;		// [265] slot
	inline constexpr int SLOT_PUZZLE_HOLE7 = 266;		// [266] slot
	inline constexpr int SLOT_PUZZLE_HOLE8 = 267;		// [267] slot
	inline constexpr int SLOT_PUZZLE_HOLE9 = 268;		// [268] slot
	inline constexpr int SLOT_PUZZLE_HOLE10 = 269;		// [269] slot
	inline constexpr int SLOT_PUZZLE_HOLE11 = 270;		// [270] slot
	inline constexpr int SLOT_PUZZLE_HOLE12 = 271;		// [271] slot
	inline constexpr int SLOT_PUZZLE_DONE1 = 272;		// [272] slot
	inline constexpr int SLOT_PUZZLE_DONE2 = 273;		// [273] slot
	inline constexpr int SLOT_PUZZLE_DONE3 = 274;		// [274] slot
	inline constexpr int SLOT_PUZZLE_DONE4 = 275;		// [275] slot
	inline constexpr int SLOT_PUZZLE_DONE5 = 276;		// [276] slot
	inline constexpr int SLOT_PUZZLE_DONE6 = 277;		// [277] slot
	inline constexpr int SLOT_PUZZLE_DONE7 = 278;		// [278] slot
	inline constexpr int SLOT_PUZZLE_DONE8 = 279;		// [279] slot
	inline constexpr int SLOT_PUZZLE_DONE9 = 280;		// [280] slot
	inline constexpr int SLOT_PUZZLE_DONE10 = 281;		// [281] slot
	inline constexpr int SLOT_PUZZLE_DONE11 = 282;		// [282] slot
	inline constexpr int SLOT_PUZZLE_DONE12 = 283;		// [283] slot
	inline constexpr int SLOT_KEY_HOLE1 = 284;		// [284] slot
	inline constexpr int SLOT_KEY_HOLE2 = 285;		// [285] slot
	inline constexpr int SLOT_KEY_HOLE3 = 286;		// [286] slot
	inline constexpr int SLOT_KEY_HOLE4 = 287;		// [287] slot
	inline constexpr int SLOT_KEY_HOLE5 = 288;		// [288] slot
	inline constexpr int SLOT_KEY_HOLE6 = 289;		// [289] slot
	inline constexpr int SLOT_KEY_HOLE7 = 290;		// [290] slot
	inline constexpr int SLOT_KEY_HOLE8 = 291;		// [291] slot
	inline constexpr int SLOT_KEY_HOLE9 = 292;		// [292] slot
	inline constexpr int SLOT_KEY_HOLE10 = 293;		// [293] slot
	inline constexpr int SLOT_KEY_HOLE11 = 294;		// [294] slot
	inline constexpr int SLOT_KEY_HOLE12 = 295;		// [295] slot
	inline constexpr int SLOT_WATERSKIN1_EMPTY = 296;		// [296] slot
	inline constexpr int SLOT_WATERSKIN1_1 = 297;		// [297] slot
	inline constexpr int SLOT_WATERSKIN1_2 = 298;		// [298] slot
	inline constexpr int SLOT_WATERSKIN1_3 = 299;		// [299] slot
	inline constexpr int SLOT_WATERSKIN2_EMPTY = 300;		// [300] slot
	inline constexpr int SLOT_WATERSKIN2_1 = 301;		// [301] slot
	inline constexpr int SLOT_WATERSKIN2_2 = 302;		// [302] slot
	inline constexpr int SLOT_WATERSKIN2_3 = 303;		// [303] slot
	inline constexpr int SLOT_WATERSKIN2_4 = 304;		// [304] slot
	inline constexpr int SLOT_WATERSKIN2_5 = 305;		// [305] slot
	inline constexpr int SLOT_SWITCH_TYPE1 = 306;		// [306] slot
	inline constexpr int SLOT_SWITCH_TYPE2 = 307;		// [307] slot
	inline constexpr int SLOT_SWITCH_TYPE3 = 308;		// [308] slot
	inline constexpr int SLOT_SWITCH_TYPE4 = 309;		// [309] slot
	inline constexpr int SLOT_SWITCH_TYPE5 = 310;		// [310] slot
	inline constexpr int SLOT_SWITCH_TYPE6 = 311;		// [311] slot
	inline constexpr int SLOT_SWITCH_TYPE7 = 312;		// [312] slot
	inline constexpr int SLOT_SWITCH_TYPE8 = 313;		// [313] slot
	inline constexpr int SLOT_UNDERWATER_SWITCH1 = 314;		// [314] slot
	inline constexpr int SLOT_UNDERWATER_SWITCH2 = 315;		// [315] slot
	inline constexpr int SLOT_TURN_SWITCH = 316;		// [316] slot
	inline constexpr int SLOT_COG_SWITCH = 317;		// [317] slot
	inline constexpr int SLOT_LEVER_SWITCH = 318;		// [318] slot
	inline constexpr int SLOT_JUMP_SWITCH = 319;		// [319] slot
	inline constexpr int SLOT_CROWBAR_SWITCH = 320;		// [320] slot
	inline constexpr int SLOT_PULLEY = 321;		// [321] slot
	inline constexpr int SLOT_DOOR_TYPE1 = 322;		// [322] slot
	inline constexpr int SLOT_DOOR_TYPE2 = 323;		// [323] slot
	inline constexpr int SLOT_DOOR_TYPE3 = 324;		// [324] slot
	inline constexpr int SLOT_DOOR_TYPE4 = 325;		// [325] slot
	inline constexpr int SLOT_DOOR_TYPE5 = 326;		// [326] slot
	inline constexpr int SLOT_DOOR_TYPE6 = 327;		// [327] slot
	inline constexpr int SLOT_DOOR_TYPE7 = 328;		// [328] slot
	inline constexpr int SLOT_DOOR_TYPE8 = 329;		// [329] slot
	inline constexpr int SLOT_PUSHPULL_DOOR1 = 330;		// [330] slot
	inline constexpr int SLOT_PUSHPULL_DOOR2 = 331;		// [331] slot
	inline constexpr int SLOT_KICK_DOOR1 = 332;		// [332] slot
	inline constexpr int SLOT_KICK_DOOR2 = 333;		// [333] slot
	inline constexpr int SLOT_UNDERWATER_DOOR = 334;		// [334] slot
	inline constexpr int SLOT_DOUBLE_DOORS = 335;		// [335] slot
	inline constexpr int SLOT_BRIDGE_FLAT = 336;		// [336] slot
	inline constexpr int SLOT_BRIDGE_TILT1 = 337;		// [337] slot
	inline constexpr int SLOT_BRIDGE_TILT2 = 338;		// [338] slot
	inline constexpr int SLOT_SARCOPHAGUS = 339;		// [339] slot
	inline constexpr int SLOT_SEQUENCE_DOOR1 = 340;		// [340] slot
	inline constexpr int SLOT_SEQUENCE_SWITCH1 = 341;		// [341] slot
	inline constexpr int SLOT_SEQUENCE_SWITCH2 = 342;		// [342] slot
	inline constexpr int SLOT_SEQUENCE_SWITCH3 = 343;		// [343] slot
	inline constexpr int SLOT_SARCOPHAGUS_CUT = 344;		// [344] slot
	inline constexpr int SLOT_HORUS_STATUE = 345;		// [345] slot
	inline constexpr int SLOT_GOD_HEAD = 346;		// [346] slot
	inline constexpr int SLOT_SETH_DOOR = 347;		// [347] slot
	inline constexpr int SLOT_STATUE_PLINTH = 348;		// [348] slot
	inline constexpr int SLOT_PISTOLS_ITEM = 349;		// [349] slot
	inline constexpr int SLOT_PISTOLS_AMMO_ITEM = 350;		// [350] slot
	inline constexpr int SLOT_UZI_ITEM = 351;		// [351] slot
	inline constexpr int SLOT_UZI_AMMO_ITEM = 352;		// [352] slot
	inline constexpr int SLOT_SHOTGUN_ITEM = 353;		// [353] slot
	inline constexpr int SLOT_SHOTGUN_AMMO1_ITEM = 354;		// [354] slot
	inline constexpr int SLOT_SHOTGUN_AMMO2_ITEM = 355;		// [355] slot
	inline constexpr int SLOT_CROSSBOW_ITEM = 356;		// [356] slot
	inline constexpr int SLOT_CROSSBOW_AMMO1_ITEM = 357;		// [357] slot
	inline constexpr int SLOT_CROSSBOW_AMMO2_ITEM = 358;		// [358] slot
	inline constexpr int SLOT_CROSSBOW_AMMO3_ITEM = 359;		// [359] slot
	inline constexpr int SLOT_CROSSBOW_BOLT = 360;		// [360] slot
	inline constexpr int SLOT_GRENADE_GUN_ITEM = 361;		// [361] slot
	inline constexpr int SLOT_GRENADE_GUN_AMMO1_ITEM = 362;		// [362] slot
	inline constexpr int SLOT_GRENADE_GUN_AMMO2_ITEM = 363;		// [363] slot
	inline constexpr int SLOT_GRENADE_GUN_AMMO3_ITEM = 364;		// [364] slot
	inline constexpr int SLOT_GRENADE = 365;		// [365] slot
	inline constexpr int SLOT_SIXSHOOTER_ITEM = 366;		// [366] slot
	inline constexpr int SLOT_SIXSHOOTER_AMMO_ITEM = 367;		// [367] slot
	inline constexpr int SLOT_BIGMEDI_ITEM = 368;		// [368] slot
	inline constexpr int SLOT_SMALLMEDI_ITEM = 369;		// [369] slot
	inline constexpr int SLOT_LASERSIGHT_ITEM = 370;		// [370] slot
	inline constexpr int SLOT_BINOCULARS_ITEM = 371;		// [371] slot
	inline constexpr int SLOT_FLARE_ITEM = 372;		// [372] slot
	inline constexpr int SLOT_FLARE_INV_ITEM = 373;		// [373] slot
	inline constexpr int SLOT_DIARY_ITEM = 374;		// [374] slot
	inline constexpr int SLOT_COMPASS_ITEM = 375;		// [375] slot
	inline constexpr int SLOT_MEMCARD_LOAD_INV_ITEM = 376;		// [376] slot
	inline constexpr int SLOT_MEMCARD_SAVE_INV_ITEM = 377;		// [377] slot
	inline constexpr int SLOT_PC_LOAD_INV_ITEM = 378;		// [378] slot
	inline constexpr int SLOT_PC_SAVE_INV_ITEM = 379;		// [379] slot
	inline constexpr int SLOT_SMOKE_EMITTER_WHITE = 380;		// [380] slot
	inline constexpr int SLOT_SMOKE_EMITTER_BLACK = 381;		// [381] slot
	inline constexpr int SLOT_STEAM_EMITTER = 382;		// [382] slot
	inline constexpr int SLOT_EARTHQUAKE = 383;		// [383] slot
	inline constexpr int SLOT_BUBBLES = 384;		// [384] slot
	inline constexpr int SLOT_WATERFALLMIST = 385;		// [385] slot
	inline constexpr int SLOT_GUNSHELL = 386;		// [386] slot
	inline constexpr int SLOT_SHOTGUNSHELL = 387;		// [387] slot
	inline constexpr int SLOT_GUN_FLASH = 388;		// [388] slot
	inline constexpr int SLOT_BUTTERFLY = 389;		// [389] slot
	inline constexpr int SLOT_SPRINKLER = 390;		// [390] slot
	inline constexpr int SLOT_RED_LIGHT = 391;		// [391] slot
	inline constexpr int SLOT_GREEN_LIGHT = 392;		// [392] slot
	inline constexpr int SLOT_BLUE_LIGHT = 393;		// [393] slot
	inline constexpr int SLOT_AMBER_LIGHT = 394;		// [394] slot
	inline constexpr int SLOT_WHITE_LIGHT = 395;		// [395] slot
	inline constexpr int SLOT_BLINKING_LIGHT = 396;		// [396] slot
	inline constexpr int SLOT_LENS_FLARE = 397;		// [397] slot
	inline constexpr int SLOT_AI_GUARD = 398;		// [398] slot
	inline constexpr int SLOT_AI_AMBUSH = 399;		// [399] slot
	inline constexpr int SLOT_AI_PATROL1 = 400;		// [400] slot
	inline constexpr int SLOT_AI_MODIFY = 401;		// [401] slot
	inline constexpr int SLOT_AI_FOLLOW = 402;		// [402] slot
	inline constexpr int SLOT_AI_PATROL2 = 403;		// [403] slot
	inline constexpr int SLOT_AI_X1 = 404;		// [404] slot
	inline constexpr int SLOT_AI_X2 = 405;		// [405] slot
	inline constexpr int SLOT_LARA_START_POS = 406;		// [406] slot
	inline constexpr int SLOT_KILL_ALL_TRIGGERS = 407;		// [407] slot
	inline constexpr int SLOT_TRIGGER_TRIGGERER = 408;		// [408] slot
	inline constexpr int SLOT_SMASH_OBJECT1 = 409;		// [409] slot
	inline constexpr int SLOT_SMASH_OBJECT2 = 410;		// [410] slot
	inline constexpr int SLOT_SMASH_OBJECT3 = 411;		// [411] slot
	inline constexpr int SLOT_SMASH_OBJECT4 = 412;		// [412] slot
	inline constexpr int SLOT_SMASH_OBJECT5 = 413;		// [413] slot
	inline constexpr int SLOT_SMASH_OBJECT6 = 414;		// [414] slot
	inline constexpr int SLOT_SMASH_OBJECT7 = 415;		// [415] slot
	inline constexpr int SLOT_SMASH_OBJECT8 = 416;		// [416] slot
	inline constexpr int SLOT_MESHSWAP1 = 417;		// [417] slot
	inline constexpr int SLOT_MESHSWAP2 = 418;		// [418] slot
	inline constexpr int SLOT_MESHSWAP3 = 419;		// [419] slot
	inline constexpr int SLOT_DEATH_SLIDE = 420;		// [420] slot
	inline constexpr int SLOT_BODY_PART = 421;		// [421] slot
	inline constexpr int SLOT_CAMERA_TARGET = 422;		// [422] slot
	inline constexpr int SLOT_WATERFALL1 = 423;		// [423] slot
	inline constexpr int SLOT_WATERFALL2 = 424;		// [424] slot
	inline constexpr int SLOT_WATERFALL3 = 425;		// [425] slot
	inline constexpr int SLOT_PLANET_EFFECT = 426;		// [426] slot
	inline constexpr int SLOT_ANIMATING1 = 427;		// [427] slot
	inline constexpr int SLOT_ANIMATING1_MIP = 428;		// [428] slot
	inline constexpr int SLOT_ANIMATING2 = 429;		// [429] slot
	inline constexpr int SLOT_ANIMATING2_MIP = 430;		// [430] slot
	inline constexpr int SLOT_ANIMATING3 = 431;		// [431] slot
	inline constexpr int SLOT_ANIMATING3_MIP = 432;		// [432] slot
	inline constexpr int SLOT_ANIMATING4 = 433;		// [433] slot
	inline constexpr int SLOT_ANIMATING4_MIP = 434;		// [434] slot
	inline constexpr int SLOT_ANIMATING5 = 435;		// [435] slot
	inline constexpr int SLOT_ANIMATING5_MIP = 436;		// [436] slot
	inline constexpr int SLOT_ANIMATING6 = 437;		// [437] slot
	inline constexpr int SLOT_ANIMATING6_MIP = 438;		// [438] slot
	inline constexpr int SLOT_ANIMATING7 = 439;		// [439] slot
	inline constexpr int SLOT_ANIMATING7_MIP = 440;		// [440] slot
	inline constexpr int SLOT_ANIMATING8 = 441;		// [441] slot
	inline constexpr int SLOT_ANIMATING8_MIP = 442;		// [442] slot
	inline constexpr int SLOT_ANIMATING9 = 443;		// [443] slot
	inline constexpr int SLOT_ANIMATING9_MIP = 444;		// [444] slot
	inline constexpr int SLOT_ANIMATING10 = 445;		// [445] slot
	inline constexpr int SLOT_ANIMATING10_MIP = 446;		// [446] slot
	inline constexpr int SLOT_ANIMATING11 = 447;		// [447] slot
	inline constexpr int SLOT_ANIMATING11_MIP = 448;		// [448] slot
	inline constexpr int SLOT_ANIMATING12 = 449;		// [449] slot
	inline constexpr int SLOT_ANIMATING12_MIP = 450;		// [450] slot
	inline constexpr int SLOT_ANIMATING13 = 451;		// [451] slot
	inline constexpr int SLOT_ANIMATING13_MIP = 452;		// [452] slot
	inline constexpr int SLOT_ANIMATING14 = 453;		// [453] slot
	inline constexpr int SLOT_ANIMATING14_MIP = 454;		// [454] slot
	inline constexpr int SLOT_ANIMATING15 = 455;		// [455] slot
	inline constexpr int SLOT_ANIMATING15_MIP = 456;		// [456] slot
	inline constexpr int SLOT_ANIMATING16 = 457;		// [457] slot
	inline constexpr int SLOT_ANIMATING16_MIP = 458;		// [458] slot
	inline constexpr int SLOT_HORIZON = 459;		// [459] slot
	inline constexpr int SLOT_SKY_GRAPHICS = 460;		// [460] slot
	inline constexpr int SLOT_BINOCULAR_GRAPHICS = 461;		// [461] slot
	inline constexpr int SLOT_TARGET_GRAPHICS = 462;		// [462] slot
	inline constexpr int SLOT_DEFAULT_SPRITES = 463;		// [463] slot
	inline constexpr int SLOT_MISC_SPRITES = 464;		// [464] slot
	inline constexpr int SLOT_MOTOR_BOAT = 465;		// [465] slot
	inline constexpr int SLOT_MOTOR_BOAT_LARA = 466;		// [466] slot
	inline constexpr int SLOT_RUBBER_BOAT = 467;		// [467] slot
	inline constexpr int SLOT_RUBBER_BOAT_LARA = 468;		// [468] slot
	inline constexpr int SLOT_MOTORBIKE_LARA = 469;		// [469] slot
	inline constexpr int SLOT_FONT_GRAPHICS = 470;		// [470] slot
	inline constexpr int SLOT_PARALLEL_BARS = 471;		// [471] slot
	inline constexpr int SLOT_PANEL_BORDER = 472;		// [472] slot
	inline constexpr int SLOT_PANEL_MIDDLE = 473;		// [473] slot
	inline constexpr int SLOT_PANEL_CORNER = 474;		// [474] slot
	inline constexpr int SLOT_PANEL_DIAGONAL = 475;		// [475] slot
	inline constexpr int SLOT_PANEL_STRIP = 476;		// [476] slot
	inline constexpr int SLOT_PANEL_HALF_BORDER1 = 477;		// [477] slot
	inline constexpr int SLOT_PANEL_HALF_BORDER2 = 478;		// [478] slot
	inline constexpr int SLOT_PANEL_MIDDLE_CORNER = 479;		// [479] slot
	inline constexpr int SLOT_TIGHT_ROPE = 480;		// [480] slot
	inline constexpr int SLOT_LASER_HEAD = 481;		// [481] slot
	inline constexpr int SLOT_LASER_HEAD_BASE = 482;		// [482] slot
	inline constexpr int SLOT_LASER_HEAD_TENTACLE = 483;		// [483] slot
	inline constexpr int SLOT_HYDRA = 484;		// [484] slot
	inline constexpr int SLOT_HYDRA_MISSILE = 485;		// [485] slot
	inline constexpr int SLOT_ENEMY_SUB_MARINE = 486;		// [486] slot
	inline constexpr int SLOT_ENEMY_SUB_MARINE_MIP = 487;		// [487] slot
	inline constexpr int SLOT_SUB_MARINE_MISSILE = 488;		// [488] slot
	inline constexpr int SLOT_FROG_MAN = 489;		// [489] slot
	inline constexpr int SLOT_FROG_MAN_HARPOON = 490;		// [490] slot
	inline constexpr int SLOT_FISH_EMITTER = 491;		// [491] slot
	inline constexpr int SLOT_KAYAK = 492;		// [492] slot
	inline constexpr int SLOT_KAYAK_LARA = 493;		// [493] slot
	inline constexpr int SLOT_CUSTOM_SPRITES = 494;		// [494] slot
	inline constexpr int SLOT_BRIDGE_TILT3 = 495;		// [495] slot
	inline constexpr int SLOT_BRIDGE_TILT4 = 496;		// [496] slot
	inline constexpr int SLOT_BRIDGE_CUSTOM = 497;		// [497] slot
	inline constexpr int SLOT_ROBOT_CLEANER = 498;		// [498] slot
	inline constexpr int SLOT_ROBOT_STAR_WARS = 499;		// [499] slot
	inline constexpr int SLOT_MECH_WARRIOR = 500;		// [500] slot
	inline constexpr int SLOT_MECH_WARRIOR_LARA = 501;		// [501] slot
	inline constexpr int SLOT_UW_PROPULSOR = 502;		// [502] slot
	inline constexpr int SLOT_UW_PROPULSOR_LARA = 503;		// [503] slot
	inline constexpr int SLOT_MINE_CART = 504;		// [504] slot
	inline constexpr int SLOT_MINE_CART_LARA = 505;		// [505] slot
	inline constexpr int SLOT_NEW_SLOT5 = 506;		// [506] slot
	inline constexpr int SLOT_NEW_SLOT6 = 507;		// [507] slot
	inline constexpr int SLOT_NEW_SLOT7 = 508;		// [508] slot
	inline constexpr int SLOT_NEW_SLOT8 = 509;		// [509] slot
	inline constexpr int SLOT_NEW_SLOT9 = 510;		// [510] slot
	inline constexpr int SLOT_NEW_SLOT10 = 511;		// [511] slot
	inline constexpr int SLOT_NEW_SLOT11 = 512;		// [512] slot
	inline constexpr int SLOT_NEW_SLOT12 = 513;		// [513] slot
	inline constexpr int SLOT_NEW_SLOT13 = 514;		// [514] slot
	inline constexpr int SLOT_NEW_SLOT14 = 515;		// [515] slot
	inline constexpr int SLOT_NEW_SLOT15 = 516;		// [516] slot
	inline constexpr int SLOT_NEW_SLOT16 = 517;		// [517] slot
	inline constexpr int SLOT_NEW_SLOT17 = 518;		// [518] slot
	inline constexpr int SLOT_NEW_SLOT18 = 519;		// [519] slot
	inline constexpr int SLOT_NUMBER_OBJECTS = 520;		// [520] slot

	// ----------- define for SSLOT_ trigger constants -------------
	inline constexpr int SSLOT_PLANT0 = 0;		// [0] slot
	inline constexpr int SSLOT_PLANT1 = 1;		// [1] slot
	inline constexpr int SSLOT_PLANT2 = 2;		// [2] slot
	inline constexpr int SSLOT_PLANT3 = 3;		// [3] slot
	inline constexpr int SSLOT_PLANT4 = 4;		// [4] slot
	inline constexpr int SSLOT_PLANT5 = 5;		// [5] slot
	inline constexpr int SSLOT_PLANT6 = 6;		// [6] slot
	inline constexpr int SSLOT_PLANT7 = 7;		// [7] slot
	inline constexpr int SSLOT_PLANT8 = 8;		// [8] slot
	inline constexpr int SSLOT_PLANT9 = 9;		// [9] slot
	inline constexpr int SSLOT_FURNITURE0 = 10;		// [10] slot
	inline constexpr int SSLOT_FURNITURE1 = 11;		// [11] slot
	inline constexpr int SSLOT_FURNITURE2 = 12;		// [12] slot
	inline constexpr int SSLOT_FURNITURE3 = 13;		// [13] slot
	inline constexpr int SSLOT_FURNITURE4 = 14;		// [14] slot
	inline constexpr int SSLOT_FURNITURE5 = 15;		// [15] slot
	inline constexpr int SSLOT_FURNITURE6 = 16;		// [16] slot
	inline constexpr int SSLOT_FURNITURE7 = 17;		// [17] slot
	inline constexpr int SSLOT_FURNITURE8 = 18;		// [18] slot
	inline constexpr int SSLOT_FURNITURE9 = 19;		// [19] slot
	inline constexpr int SSLOT_ROCK0 = 20;		// [20] slot
	inline constexpr int SSLOT_ROCK1 = 21;		// [21] slot
	inline constexpr int SSLOT_ROCK2 = 22;		// [22] slot
	inline constexpr int SSLOT_ROCK3 = 23;		// [23] slot
	inline constexpr int SSLOT_ROCK4 = 24;		// [24] slot
	inline constexpr int SSLOT_ROCK5 = 25;		// [25] slot
	inline constexpr int SSLOT_ROCK6 = 26;		// [26] slot
	inline constexpr int SSLOT_ROCK7 = 27;		// [27] slot
	inline constexpr int SSLOT_ROCK8 = 28;		// [28] slot
	inline constexpr int SSLOT_ROCK9 = 29;		// [29] slot
	inline constexpr int SSLOT_ARCHITECTURE0 = 30;		// [30] slot
	inline constexpr int SSLOT_ARCHITECTURE1 = 31;		// [31] slot
	inline constexpr int SSLOT_ARCHITECTURE2 = 32;		// [32] slot
	inline constexpr int SSLOT_ARCHITECTURE3 = 33;		// [33] slot
	inline constexpr int SSLOT_ARCHITECTURE4 = 34;		// [34] slot
	inline constexpr int SSLOT_ARCHITECTURE5 = 35;		// [35] slot
	inline constexpr int SSLOT_ARCHITECTURE6 = 36;		// [36] slot
	inline constexpr int SSLOT_ARCHITECTURE7 = 37;		// [37] slot
	inline constexpr int SSLOT_ARCHITECTURE8 = 38;		// [38] slot
	inline constexpr int SSLOT_ARCHITECTURE9 = 39;		// [39] slot
	inline constexpr int SSLOT_DEBRIS0 = 40;		// [40] slot
	inline constexpr int SSLOT_DEBRIS1 = 41;		// [41] slot
	inline constexpr int SSLOT_DEBRIS2 = 42;		// [42] slot
	inline constexpr int SSLOT_DEBRIS3 = 43;		// [43] slot
	inline constexpr int SSLOT_DEBRIS4 = 44;		// [44] slot
	inline constexpr int SSLOT_DEBRIS5 = 45;		// [45] slot
	inline constexpr int SSLOT_DEBRIS6 = 46;		// [46] slot
	inline constexpr int SSLOT_DEBRIS7 = 47;		// [47] slot
	inline constexpr int SSLOT_DEBRIS8 = 48;		// [48] slot
	inline constexpr int SSLOT_DEBRIS9 = 49;		// [49] slot
	inline constexpr int SSLOT_SHATTER0 = 50;		// [50] slot
	inline constexpr int SSLOT_SHATTER1 = 51;		// [51] slot
	inline constexpr int SSLOT_SHATTER2 = 52;		// [52] slot
	inline constexpr int SSLOT_SHATTER3 = 53;		// [53] slot
	inline constexpr int SSLOT_SHATTER4 = 54;		// [54] slot
	inline constexpr int SSLOT_SHATTER5 = 55;		// [55] slot
	inline constexpr int SSLOT_SHATTER6 = 56;		// [56] slot
	inline constexpr int SSLOT_SHATTER7 = 57;		// [57] slot
	inline constexpr int SSLOT_SHATTER8 = 58;		// [58] slot
	inline constexpr int SSLOT_SHATTER9 = 59;		// [59] slot
	inline constexpr int SSLOT_EXTRA00 = 60;		// [60] slot
	inline constexpr int SSLOT_EXTRA01 = 61;		// [61] slot
	inline constexpr int SSLOT_EXTRA02 = 62;		// [62] slot
	inline constexpr int SSLOT_EXTRA03 = 63;		// [63] slot
	inline constexpr int SSLOT_EXTRA04 = 64;		// [64] slot
	inline constexpr int SSLOT_EXTRA05 = 65;		// [65] slot
	inline constexpr int SSLOT_EXTRA06 = 66;		// [66] slot
	inline constexpr int SSLOT_EXTRA07 = 67;		// [67] slot
	inline constexpr int SSLOT_EXTRA08 = 68;		// [68] slot
	inline constexpr int SSLOT_EXTRA09 = 69;		// [69] slot
	inline constexpr int SSLOT_EXTRA10 = 70;		// [70] slot
	inline constexpr int SSLOT_EXTRA11 = 71;		// [71] slot
	inline constexpr int SSLOT_EXTRA12 = 72;		// [72] slot
	inline constexpr int SSLOT_EXTRA13 = 73;		// [73] slot
	inline constexpr int SSLOT_EXTRA14 = 74;		// [74] slot
	inline constexpr int SSLOT_EXTRA15 = 75;		// [75] slot
	inline constexpr int SSLOT_EXTRA16 = 76;		// [76] slot
	inline constexpr int SSLOT_EXTRA17 = 77;		// [77] slot
	inline constexpr int SSLOT_EXTRA18 = 78;		// [78] slot
	inline constexpr int SSLOT_EXTRA19 = 79;		// [79] slot
	inline constexpr int SSLOT_EXTRA20 = 80;		// [80] slot
	inline constexpr int SSLOT_EXTRA21 = 81;		// [81] slot
	inline constexpr int SSLOT_EXTRA22 = 82;		// [82] slot
	inline constexpr int SSLOT_EXTRA23 = 83;		// [83] slot
	inline constexpr int SSLOT_EXTRA24 = 84;		// [84] slot
	inline constexpr int SSLOT_EXTRA25 = 85;		// [85] slot
	inline constexpr int SSLOT_EXTRA26 = 86;		// [86] slot
	inline constexpr int SSLOT_EXTRA27 = 87;		// [87] slot
	inline constexpr int SSLOT_EXTRA28 = 88;		// [88] slot
	inline constexpr int SSLOT_EXTRA29 = 89;		// [89] slot
	inline constexpr int SSLOT_EXTRA30 = 90;		// [90] slot
	inline constexpr int SSLOT_EXTRA31 = 91;		// [91] slot
	inline constexpr int SSLOT_EXTRA32 = 92;		// [92] slot
	inline constexpr int SSLOT_EXTRA33 = 93;		// [93] slot
	inline constexpr int SSLOT_EXTRA34 = 94;		// [94] slot
	inline constexpr int SSLOT_EXTRA35 = 95;		// [95] slot
	inline constexpr int SSLOT_EXTRA36 = 96;		// [96] slot
	inline constexpr int SSLOT_EXTRA37 = 97;		// [97] slot
	inline constexpr int SSLOT_EXTRA38 = 98;		// [98] slot
	inline constexpr int SSLOT_EXTRA39 = 99;		// [99] slot
	inline constexpr int SSLOT_EXTRA40 = 100;		// [100] slot
	inline constexpr int SSLOT_EXTRA41 = 101;		// [101] slot
	inline constexpr int SSLOT_EXTRA42 = 102;		// [102] slot
	inline constexpr int SSLOT_EXTRA43 = 103;		// [103] slot
	inline constexpr int SSLOT_EXTRA44 = 104;		// [104] slot
	inline constexpr int SSLOT_EXTRA45 = 105;		// [105] slot
	inline constexpr int SSLOT_EXTRA46 = 106;		// [106] slot
	inline constexpr int SSLOT_EXTRA47 = 107;		// [107] slot
	inline constexpr int SSLOT_EXTRA48 = 108;		// [108] slot
	inline constexpr int SSLOT_EXTRA49 = 109;		// [109] slot
	inline constexpr int SSLOT_EXTRA50 = 110;		// [110] slot
	inline constexpr int SSLOT_EXTRA51 = 111;		// [111] slot
	inline constexpr int SSLOT_EXTRA52 = 112;		// [112] slot
	inline constexpr int SSLOT_EXTRA53 = 113;		// [113] slot
	inline constexpr int SSLOT_EXTRA54 = 114;		// [114] slot
	inline constexpr int SSLOT_EXTRA55 = 115;		// [115] slot
	inline constexpr int SSLOT_EXTRA56 = 116;		// [116] slot
	inline constexpr int SSLOT_EXTRA57 = 117;		// [117] slot
	inline constexpr int SSLOT_EXTRA58 = 118;		// [118] slot
	inline constexpr int SSLOT_EXTRA59 = 119;		// [119] slot
	inline constexpr int SSLOT_EXTRA60 = 120;		// [120] slot
	inline constexpr int SSLOT_EXTRA61 = 121;		// [121] slot
	inline constexpr int SSLOT_EXTRA62 = 122;		// [122] slot
	inline constexpr int SSLOT_EXTRA63 = 123;		// [123] slot
	inline constexpr int SSLOT_EXTRA64 = 124;		// [124] slot
	inline constexpr int SSLOT_EXTRA65 = 125;		// [125] slot
	inline constexpr int SSLOT_EXTRA66 = 126;		// [126] slot
	inline constexpr int SSLOT_EXTRA67 = 127;		// [127] slot
	inline constexpr int SSLOT_EXTRA68 = 128;		// [128] slot
	inline constexpr int SSLOT_EXTRA69 = 129;		// [129] slot
	inline constexpr int SSLOT_EXTRA70 = 130;		// [130] slot
	inline constexpr int SSLOT_EXTRA71 = 131;		// [131] slot
	inline constexpr int SSLOT_EXTRA72 = 132;		// [132] slot
	inline constexpr int SSLOT_EXTRA73 = 133;		// [133] slot
	inline constexpr int SSLOT_EXTRA74 = 134;		// [134] slot
	inline constexpr int SSLOT_EXTRA75 = 135;		// [135] slot
	inline constexpr int SSLOT_EXTRA76 = 136;		// [136] slot
	inline constexpr int SSLOT_EXTRA77 = 137;		// [137] slot
	inline constexpr int SSLOT_EXTRA78 = 138;		// [138] slot
	inline constexpr int SSLOT_EXTRA79 = 139;		// [139] slot
	inline constexpr int SSLOT_EXTRA80 = 140;		// [140] slot
	inline constexpr int SSLOT_EXTRA81 = 141;		// [141] slot
	inline constexpr int SSLOT_EXTRA82 = 142;		// [142] slot
	inline constexpr int SSLOT_EXTRA83 = 143;		// [143] slot
	inline constexpr int SSLOT_EXTRA84 = 144;		// [144] slot
	inline constexpr int SSLOT_EXTRA85 = 145;		// [145] slot
	inline constexpr int SSLOT_EXTRA86 = 146;		// [146] slot
	inline constexpr int SSLOT_EXTRA87 = 147;		// [147] slot
	inline constexpr int SSLOT_EXTRA88 = 148;		// [148] slot
	inline constexpr int SSLOT_EXTRA89 = 149;		// [149] slot
	inline constexpr int SSLOT_EXTRA90 = 150;		// [150] slot
	inline constexpr int SSLOT_EXTRA91 = 151;		// [151] slot
	inline constexpr int SSLOT_EXTRA92 = 152;		// [152] slot
	inline constexpr int SSLOT_EXTRA93 = 153;		// [153] slot
	inline constexpr int SSLOT_EXTRA94 = 154;		// [154] slot
	inline constexpr int SSLOT_EXTRA95 = 155;		// [155] slot
	inline constexpr int SSLOT_EXTRA96 = 156;		// [156] slot
	inline constexpr int SSLOT_EXTRA97 = 157;		// [157] slot
	inline constexpr int SSLOT_EXTRA98 = 158;		// [158] slot
	inline constexpr int SSLOT_EXTRA99 = 159;		// [159] slot
	inline constexpr int SSLOT_NUMBER_STATIC_OBJECTS = 160;		// [160] slot

	// costanti per tipo barra
	inline constexpr int BAR_HEALTH = 0;
	inline constexpr int BAR_DASH = 1;
	inline constexpr int BAR_AIR = 2;
	inline constexpr int BAR_LOAD_LEVEL = 3;
	inline constexpr int BAR_CUSTOM1 = 4;
	inline constexpr int BAR_CUSTOM2 = 5;
	inline constexpr int BAR_CUSTOM3 = 6;
	inline constexpr int BAR_CUSTOM4 = 7;
	inline constexpr int BAR_DAMAGE = 8;
	inline constexpr int BAR_COLD = 9;
	inline constexpr int BAR_CUST_TOT = 10;

	// costanti per tipo di testo in tomb4, per poter alterare i colori
	inline constexpr int TT_ITEM_NAME = 0;
	inline constexpr int TT_ACTION_INVENTORY_MENU_OFF = 1; //combine examine
	inline constexpr int TT_ACTION_INVENTORY_MENU_ON = 2; // lampegiante
	inline constexpr int TT_AMMO = 3;
	inline constexpr int TT_EXAMINE1_TOP = 4;
	inline constexpr int TT_EXAMINE1_BOTTOM = 5;
	inline constexpr int TT_EXAMINE3 = 6;
	inline constexpr int TT_SELECT_LEVEL = 7;
	inline constexpr int TT_NEW_LEVEL_ARROWS = 8;
	inline constexpr int TT_LEVEL_NAME_OFF = 9;
	inline constexpr int TT_LEVEL_NAME_ON = 10;
	inline constexpr int TT_MAIN_MENU_OFF = 11;  // new game/ load game/option/exit
	inline constexpr int TT_LEGEND = 12;
	inline constexpr int TT_CREDITS = 13;
	inline constexpr int TT_SCREEN_TIMER = 14;
	inline constexpr int TT_SAVEGAME_PANEL_TITLE = 15;
	inline constexpr int TT_SAVEGAME_DESCRIPTION_OFF = 16;
	inline constexpr int TT_SAVEGAME_DESCRIPTION_ON = 17;
	inline constexpr int TT_OPTION_DESCRIPTIONS = 20;  //Text used to describe the option, like "Control Method"
	inline constexpr int TT_OPTION_VALUES = 21;        //Text of possible value for options, like "Joystick/Keboard"
	inline constexpr int TT_STATISTICS_DESCRIPTIONS = 22;  //Text used to describe the statistics, like "Distance Travelled"
	inline constexpr int TT_STATISTICS_VALUES = 23;  //Text of statistic values, like "43m", i.e. 43 meters for "Distance Travelled"
	inline constexpr int TT_PAUSED_MENU_TITLE = 24;  //Title of "Paused" menu. This text is the "Paused" word
	inline constexpr int TT_PAUSED_MENU_ITEMS = 25;    //Text for paused menu, "Statistics", "Options", "Exit to Title"
	inline constexpr int TT_MAIN_MENU_ON = 26;  // testi menu principale selezionati
	inline constexpr int TT_CAMERA_VIEW = 27;  // messaggio di LoadCamera quando si preme F1
	inline constexpr int TT_MAX_TEXT_TYPES = 28;

	inline constexpr int PANEL_START = 472;
	inline constexpr int PANEL_END = 479;

	// LIST OF CALLBACK THAT YOU CAN REQUIRE:

	// ------------ CALLBACKS WITH NO FLAGS, NO PARAMETERS --------------------------
	inline constexpr int CB_INIT_PROGRAM = 0; // DEFAULT. You have already it. Look for "cbInitProgram" procedure in Plugin_trng.cpp source
	inline constexpr int CB_SAVING_GAME = 1; // DEFAULT. You have already it. Look for "cbSaveMyData" procedure in Plugin_trng.cpp source
	inline constexpr int CB_LOADING_GAME = 2; // DEFAULT. You have already it. Look for "cbLoadMyData" procedure in Plugin_trng.cpp
	inline constexpr int CB_INIT_GAME = 3; // DEFAULT. You have already it. Look for "cbInitGame" procedure in Plugin_trng.cpp source
	inline constexpr int CB_INIT_LOAD_NEW_LEVEL = 4; // DEFAULT. You have already it. Look for "cbInitLoadNewLevel" procedure in Pluging_trng.cpp source
	inline constexpr int CB_FLIPEFFECT_MINE = 5; // DEFAULT. You have already it. Look for "cbFlipEffectMine" procedure in Pluging_trng.cpp source
	inline constexpr int CB_ACTION_MINE = 6; // DEFAULT. You have already it. Look for "cbActionMine" procedure in Pluging_trng.cpp source
	inline constexpr int CB_CONDITION_MINE = 7; // DEFAULT. You have already it. Look for "cbConditionMine" procedure in Pluging_trng.cpp source
	inline constexpr int CB_CUSTOMIZE_MINE = 8; // DEFAULT. You have already it. Look for "cbCustomizeMine" procedure in Pluging_trng.cpp source
	inline constexpr int CB_PARAMETER_MINE = 9; // DEFAULT. You have already it. Look for "cbParametersMine" procedure in Pluging_trng.cpp source
	inline constexpr int CB_CYCLE_BEGIN = 10; // DEFAULT. You have already it. Look for "cbCycleBegin" procedure in Plugin_trng.cpp
	inline constexpr int CB_CYCLE_END = 11; // callback called at end of every game cycle
	inline constexpr int CB_GLOBAL_TRIGGER = 12; // callback to give the result about a global trigger GT_... (yours or old of trng)
	inline constexpr int CB_INIT_OBJECTS = 13; // it will be called just completed the loading of object slots from tr4 level. (CALL_VOID) You can use it to initialise your objects (moveables) or to change the settings of other moveables
	inline constexpr int CB_PROGR_ACTION_MINE = 14; // DEFAULT: You have already it. Look for "cbProgrActionMine" procedure in Plugin_trng.cpp source
	inline constexpr int CB_PROGR_ACTION_DRAW_MINE = 15; // callback to perform your progressive actions that requires a direct draw on screen (meshes, images, windows font texts, sprites)
	inline constexpr int CB_INIT_LEVEL = 16; // DEFAULT: you have already it. Look for "cbInitLevel" procedure. it will be performed just a moment before entering in main game cycle. All items have already been initialized
	inline constexpr int CB_COMPLETED_PROGR_ACTION = 17; // callback called when a trng progressive action has been just completed.
	inline constexpr int CB_VEHICLE = 18; // callback for vehicle management
	inline constexpr int CB_ASSIGN_SLOT_MINE = 19; // DEFAULT: You have already it. Look for "cbAssignSlotMine() procedure. It receives and stores all AssignSlot= data about your OBJ_ values
	inline constexpr int CB_FMV_MANAGER = 20; // callback to replace playing fmv management
	inline constexpr int CB_INPUT_MANAGER = 21; // callback to read in advance input command and, optionally remove them
	inline constexpr int CB_SAVEGAME_MANAGER = 22; // callback for procedure to handle savegame list to load/save savegames
												   // it works like "replace": you replace the original/trng management
												   // about savegame selection
	inline constexpr int CB_PAUSE_MANAGER = 23; // callback to handle pause menu phase. it works as a replace callback
	inline constexpr int CB_STATISTICS_MANAGER = 24; // callback to the procedure to show statistics screen.
	inline constexpr int CB_TITLE_MENU_MANAGER = 25; // callback for the menu of title level
	inline constexpr int CB_WINDOWS_FONT_CREATE = 26; // callback to replace the creation of windows font for printing window text
	inline constexpr int CB_WINDOWS_UNICODE_CONVERT = 27; // callback to convert from text of script to unicode text for windows text printing
	inline constexpr int CB_WINDOWS_TEXT_PRINT = 28; // callback to replace print windows text trng function
	inline constexpr int CB_DIAGNOSTIC = 29; // callback to add own diagnostic on screen or to monitor current trng diagnostic text

	// --------- CALLBACKS WITH FLAGS (CBT_FIRST, CBT_AFTER,CBT_REPLACE) but NO PARAMETERS -----------------
	inline constexpr int CB_LARA_CONTROL = 33; // callback for main control procedure of lara that swap environment:
											   //                                      ground, water surface, underwater, vehicle
	inline constexpr int CB_LARA_DRAW = 34; // callback for draw lara procedure
	inline constexpr int CB_LARA_HAIR_DRAW = 35; // callback for draw hair procedure
	inline constexpr int CB_LARA_HAIR_CONTROL = 36; // callback for control hair procedure
	inline constexpr int CB_INVENTORY_MAIN = 37; // callback for procedure that shows inventory and handles it
	inline constexpr int CB_INVENT_BACKGROUND_CREATE = 38; // callback for procedure ( CreateMonoScreen) that creates a backgroup (allocating resources if necessary)
	inline constexpr int CB_INVENT_BACKGROUND_DRAW = 39; // callback for procedure (S_DisplayMonoScreen) that updates graphic for background
	inline constexpr int CB_INVENT_BACKGROUND_QUIT = 40; // callback for procedure (FreeMonoScreen) that free futher resource allocated by BACKGROUND_CREATE
	inline constexpr int CB_ANIMATE_LARA = 41; // callback for procedure AnimateLaran that update frames and change animations of lara
	inline constexpr int CB_OPTIONS_MANAGER = 42; // callback to the procedure to show/edit options
												  // note: it accepts only CBT_REPLACE and CBT_LOOPED flags

	// ---------- CALLBACKS WITH FLAGS AND PARAMETERS -----------------------------------------------------
	inline constexpr int CB_FLIPEFFECT = 100; // callback for a tomb_nextgeneration (old, not yours) FLIPEFFECT trigger
	inline constexpr int CB_ACTION = 101; // callback for a tomb_nextgeneration (old, not yours) ACTION trigger
	inline constexpr int CB_CONDITION = 102; // callback for a tomb_nextgeneration (old, not yours) CONDITION trigger. WARNING: condition triggers have a particular management, see infos about this kind of callback
	inline constexpr int CB_VEHICLE_CONTROL = 103; // calback for vehicles not handled by common slot control procedures
												   // set as parameter the slot of vehicle (jeep, sidecar or kayak)
	inline constexpr int CB_PROGR_ACTION = 105; // callback for a tomb_nextgeneration (old, not yours) PROGRESSIVE ACTION. Type the AZ_ constant to choose it.
	inline constexpr int CB_NUMERIC_TRNG_PATCH = 106; // callback affects a given MOV AX , Number  / Call dword [TrngPatcher]  patch of trng (see tomb4 patched code source for their position and target)
	inline constexpr int CB_SLOT_INITIALISE = 107; // callboack for Initialise procedure of given slot object
	inline constexpr int CB_SLOT_CONTROL = 108; // callback for Control procedure of given slot object
	inline constexpr int CB_SLOT_COLLISION = 109; // callback for Collision procedure of given slot object
	inline constexpr int CB_SLOT_DRAW = 110; // callback for Draw procedure of given slot object
	inline constexpr int CB_SLOT_FLOOR = 111; // callback for floor procedure of given slot object
	inline constexpr int CB_SLOT_CEILING = 112; // callback fro ceiling procedure of given slot object
	inline constexpr int CB_SLOT_DRAW_EXTRA = 113; // callback for drawextra procedure of given slot object
	inline constexpr int CB_STATE_ID_LARA_CTRL = 114; // callback for control state-id lara, parameter the state-id
	inline constexpr int CB_STATE_ID_LARA_COLLISION = 115; // callbacks for collision state-id lara, parameter the state-id

	// CallBack Types
	// note: not all callbacks support all following types
	inline constexpr int CBT_FIRST = 0x0001; // your callback code it will be performed FIRST of orginal trng code, then it will be performed original trng code
	inline constexpr int CBT_AFTER = 0x0002; // your callback code it will be performed AFTER that the original trng code has been performed
	inline constexpr int CBT_REPLACE = 0x0004; // this callback will REPLACE totally original trng code.
	inline constexpr int CBT_ASM = 0x0008; // this callback will be handled by your assembly code at low level.
										   //      CBT_ASM works only for CB_NUMERIC_TRNG_PATCH
										   //      if you omit the CBT_ASM flag, the callback should be handled
										   // by your c++ code (see the prototype for C++ callback to CB_NUMERIC_TRNG_PATCH
										   // in DefTomb4Funct.h file).
	inline constexpr int CBT_PRESENT = 0x0010; // do not use, reserved
	inline constexpr int CBT_LOOPED = 0x0020; // performed togheter with original code, it works with management that has not a precise start and end but when it is in progress
	inline constexpr int CBT_ANY = 0xFFFF; // do not use, reserved

	// flag NEF ossia flag ng per comando script Enemy=
	inline constexpr int NEF_NONE = 0;
	inline constexpr int NEF_EXPLODE = 0x0001;
	inline constexpr int NEF_EXPLODE_AFTER = 0x0002;
	inline constexpr int NEF_NON_TARGET = 0x0004;
	inline constexpr int NEF_HIT_DEFAULT = 0x0008;
	inline constexpr int NEF_SET_AS_CREATURE = 0x0010;
	inline constexpr int NEF_SET_AS_BRIDGE_FLAT = 0x0020;
	inline constexpr int NEF_SET_AS_BRIDGE_TILT1 = 0x0040;
	inline constexpr int NEF_SET_AS_BRIDGE_TILT2 = 0x0080;
	inline constexpr int NEF_EASY_HEAVY_ENABLING = 0x0100;
	inline constexpr int NEF_HIT_BLOOD = 0x0400;
	inline constexpr int NEF_HIT_SMOKE = 0x0800;
	inline constexpr int NEF_HIT_FRAGMENTS = 0x0C00;
	inline constexpr int NEF_ONLY_EXPLODE = 0x1000;
	inline constexpr int NEF_SET_AS_MORTAL = 0x2000;
	inline constexpr int NEF_SAVE_MESH_VISIBILITY = 0x4000;
	inline constexpr int NEF_SET_AS_SEMIGOD = 0x8000;

	inline constexpr int SCRIPT_IGNORE = 0xFFFF;

	// costranti per tipo di exe

	inline constexpr int EXE_TOMB4 = 1;
	inline constexpr int EXE_EDITOR = 2;
	inline constexpr int EXE_TOM2PC = 3;
	inline constexpr int EXE_TOMB5 = 4;
	inline constexpr int EXE_TOMB3 = 5;

	// flag per tipo di diagnostica
	inline constexpr int DGX_LARA = 0x0001;
	inline constexpr int DGX_ANIMATION = 0x0002;
	inline constexpr int DGX_SFX_SOUNDS = 0x0004;
	inline constexpr int DGX_FAR_VIEW = 0x0008;
	inline constexpr int DGX_AUDIO_TRACKS = 0x0010;
	inline constexpr int DGX_CHEATS = 0x0020;
	inline constexpr int DGX_FOG = 0x0040;
	inline constexpr int DGX_COMMON_VARIABLES = 0x0080;
	inline constexpr int DGX_STORE_VARIABLES = 0x0100;
	inline constexpr int DGX_FLYBY = 0x0200;
	inline constexpr int DGX_TEXT_VARIABLES = 0x0400;
	inline constexpr int DGX_LOG_SCRIPT_COMMANDS = 0x0800;
	inline constexpr int DGX_WEAPON_ANIMATION = 0x1000;
	inline constexpr int DGX_ADJUSTMENT_MODE = 0x2000;
	inline constexpr int DGX_FPS = 0x4000;
	inline constexpr int DGX_ERRORS = 0x8000;

	typedef void (__cdecl * TYPE_SalvaInBuffer) (void *pZona, int TotBytes);

#pragma pack(push, 1)
	struct StrRelocatedMem {
		DWORD Start; // new start address for this memory zone
		DWORD End; // new end address (excluded) for this memory zone
		DWORD TotItems; // number of items/recores that this zone is now able to host
	};

	struct StrBaseRemapMemory {
		// here there is a direct access to old/new address for extended memory zone
		// in tomb4
		StrRelocatedMem Old_80DE80;  // 0
		StrRelocatedMem Old_80DEA0;  // 1
		StrRelocatedMem Old_4BFD70;  // 2
		StrRelocatedMem Old_533290;  // 3
		StrRelocatedMem Old_8012E0;  // 4
		StrRelocatedMem Old_5C0678;  // 5
		StrRelocatedMem Old_660B60;  // 6
		StrRelocatedMem Old_660998;  // 7
		StrRelocatedMem Old_670B60;  // 8
		StrRelocatedMem Old_52A220;  // 9
		StrRelocatedMem Old_7F6DA8;  // 10
		StrRelocatedMem Old_7F57C8;  // 11
		StrRelocatedMem Old_532C70;  // 12
		StrRelocatedMem Old_7FFE40;  // 13
		StrRelocatedMem Old_804740;  // 14
		StrRelocatedMem Old_7F7769;  // 15
		StrRelocatedMem Old_7F5960;  // 16
		StrRelocatedMem Old_4ACAC0;  // 17
		StrRelocatedMem Old_660678;  // 18  	// aggiungte 1.3.0.0
		StrRelocatedMem Old_5C0350;  // 19
		StrRelocatedMem Old_4B09B4;  // 20
		StrRelocatedMem Old_532B60;  // 21
		StrRelocatedMem Old_533270;  // 22
		StrRelocatedMem Old_533278;  // 23
		StrRelocatedMem Old_53327C;  // 24
		StrRelocatedMem Old_533284;  // 25
		StrRelocatedMem Old_533288;  // 26
		StrRelocatedMem Old_53328C;  // 27
		StrRelocatedMem Old_7FE1E0;  // 28
		StrRelocatedMem Old_7FE100;  // 29
		StrRelocatedMem Old_4AB9B8;  // 30
		StrRelocatedMem Old_4ABB90; // 31
		StrRelocatedMem Reserved[80-14]; // sosttiuire -0 con nuove aggiunte (ultima era con indice = 17)
	};

	struct StrPrefTomb {
		DWORD Flags;
		int Reserved[80]; // to reduce when I add new fields to keep with same length the StrPrefTomb structure
	};

	struct StrBaseFog {
		short DefMinScript; // valori originali scritti in fogrange
		short DefMaxScript; // se -1 alloravalori originali
		short NowStartFog; // integer
		short NowEndFog;  // integer
		short NowFogBulbDistance;  // integer
		float FloatFogEnd;
		float FloatFogStart;
		bool TestHardFogEnabled;  // se false e' attualmene disattivata la fog hard
	};

	// usata per tareare posizione di detector
	struct StrCordDetectors {
		int DetOrgY;		// 0
		int BaseTargetY;		// 1
		float SizeTestoX;	// 2
		float SizeTestoY;	// 3
		int BaseVLineX;		// 4
		int BaseVLineY;		// 5
		int GapVLineX;		// 6
		float GapVLineY;	// 7
		int BaseTextX;		// 8
		int BaseTextY;		// 9
		int CompassLineY;   // 10   13845
		int KeyPadX;		// 11   11056
		int KeyPadY;		// 12   17685
		int KeyPadTextY;    // 13   2304
		int IndiceAttivo; // valore da 0 a MAX_TARA_ITEMS-1
		DWORD LastCambioVar;
	};

	struct StrBoatSinking {
		bool TestAffonda;
		bool TestGorgo;
		int CordY;
		short RoomNow;
		short RoomOld;
		short VOrient;
		bool TestFinito; // e' gia' affondata fino al punto di centroy
	};

	struct StrPosizione {
		int OrgX;
		int OrgY;
		int OrgZ;
	};

	struct StrPos3d {
		StrPosizione Posizione;   // offset 0
		short OrientV;        // offset 0C
		short OrientH;		  // offset 0E
		short OrientR;		  // offset 10
	};

	struct StrShowMeshAbs {
		StrPos3d PosData;
		short Mesh;
	};

	struct StrBaseShowMeshes {
		int TotMesh;
		StrShowMeshAbs VetMesh[MAX_SHOW_MESH];
	};

	struct StrSospendiLog {
		bool TestSospendi;
		bool TestRilasciatoF9;
		int SalvaDebugCounter;
	};

	struct StrBaseMissing {
		bool TestScriptPresenti; // se entrambi i file script sono presenti
		char MexMissing[1024]; // avvisi file mancanti o NULL
		char MexLoadCamera[256];
		bool TestErrori; // errori
		bool TestAvvisi;
		bool TestErroreLoadCamera;
		int Reserved[80]; // to change when I add new field to this structure
	};

	// struttura Item per tomb4
	struct StrItemTr4 {
		int HeightFloor;		// 00
		int ContactFlags;		// 04  (oggetto toccato lara (darts))
		DWORD MeshVisibilityMask; // 08
		WORD SlotID;			// 0C
		WORD StateIdCurrent;	    // 0E
		WORD StateIdNext;			// 10
		WORD StateIdAI;				// 12
		WORD AnimationNow;		    // 14
		WORD FrameNow;			    // 16
		short Room;					// 18
		short ItemIndexNext;	    // 1A
		short ItemIndexPrevious;     // 1C
		short SpeedH;			// 1E
		short SpeedV;			// 20
		short Health;				// 22
		WORD BoxZoneIndex;			// 24
		short ObjectTimer;			// 26
		WORD Objectbuttons;	// 28
		WORD Intensity1;			// 2a
		WORD OcbCode;				// 2c
		BYTE IdSprite1;				// 2e
		BYTE IdSprite2;				// 2f
		WORD Trasparency;			// 30
		WORD Mistery1;				// 32
		short Reserved_34;		    // 34
		short Reserved_36;				// 36
		short Reserved_38;				// 38
		short Reserved_3A;				// 3A
		void *pZonaSavegame;		// 3C	or pCreatureInfo structure for enemies
		DWORD  CordX;					// 40
		int  CordY;					// 44
		DWORD  CordZ;					// 48
		short OrientationV;  // 4c
		short OrientationH;  // 4e
		short OrientationT;		// 50
		DWORD LightRed;		//52
		DWORD LightGreen;		// 56
		DWORD LightBlue;		// 5A
		DWORD LightRGB;		// 5E
		DWORD LightDifferenceRed;		// 62
		DWORD LightDifferenceGreen;		// 66
		DWORD LightDifferenceBlue;		// 6A
		DWORD LightChangeDegrees;		// 6E
		BYTE Zone1[2730];		// 72
		BYTE Zone2[2758];		// B1C
		BYTE *pZone1;		// 15e2
		BYTE *pZone2;		// 15e6
		DWORD FlagsMain;		// 15ea (FITEM_.. flags)
		DWORD FlagsSwapMesh;	// 15ee
		DWORD Mistery5;		// 15f2
	};

	struct StrCercaStatic {
		WORD IndiceRoom;
		short IndiceStatic; // interno a stanza
	};

	struct StrAbsBoxCollision {
		int MinX;		//00
		int MaxX;		//04
		int MinY;		//08
		int MaxY;		//0C
		int MinZ;		//10
		int MaxZ;		//14
	};

	struct StrVetItemCollision {
		bool TestAttiva;
		StrItemTr4 *pVeicolo;
		WORD TotMoveables;
		WORD VetMoveables[100];
		WORD TotStatics;
		StrPosizione OldPos;
		short OldSpeed; // precedente velocita' di veicolo
		StrCercaStatic VetStatics[100];
		StrAbsBoxCollision OutCollisioneBox; // usato per collisione veicoli
		int NewFloorY; // valore restituito da AnalisiCollVeicoli
	};

	struct StrScaleItem {
		WORD IdScale;
		WORD Dynamic;
		short ItemIndex;
		WORD Flags;   // fst_
		short BeginPerc;
		short FinalPerc;
		short IncPerc;
	};

	struct StrBaseScaleItem {
		WORD TotScale;
		StrScaleItem VetScaleItem[MAX_SCALE_ITEM];
		short VetIdScale[MAX_SCALE_ITEM*10];
	};

	struct StrBasevehicles {
		int TotVeicoli;
		int VetIndiciVeicoli[MAX_VEICOLI];
	};

	struct StrRollBoat {
		short Indice;
		short SpeedPitch;
		short SpeedSwing;
		short SoundSfx;
		WORD Flags; // FRB
		DWORD OldCordX;
		DWORD OldCordZ;
		BYTE DerivaTotCicli;
		char DerivaIncX;
		char DerivaIncZ;
	};

	struct StrBaseRollBoat {
		WORD TotRollBoats;
		StrRollBoat VetRollBoats[MAX_ROLL_BOATS];
		// variabili per accesso rapido a presenza di rolling per
		// rubberboat o motorboat
		bool TestRubberBoat;
		bool TestMotorBoat;
	};

	struct StrLaraHp {
		short LastHpValue;
		WORD TotTargetLevels;
		short VetTargetLevels[MAX_TARGET_LEVELS];
	};

	struct StrBackupLara {
		WORD AnimationNow;
		WORD StateIdCurrent;
		WORD StateIdNext;
		WORD FrameNow;
		DWORD LaraX;
		int  LaraY;
		DWORD LaraZ;
		short LaraRoom;
		WORD Orient;
		short SpeedH;
		short SpeedV;
		DWORD CopiaOrientamento;
	};

	// usata in funzione MoveLaraPosition
	struct StrMovePosition {
		int RelX;
		int RelY;
		int RelZ;
	};

	struct StrRobaKayak {
		StrBackupLara PosLaraPrimaKayak;
		WORD OldAnim;
		int OldFrame;
		bool TestDestra;
		DWORD StartFrame;
		StrMovePosition PosIdeale;
		short OrientIdeale;
		bool TestMistIniziata;
		short ClickPausa;
		int IntensitaMist;
	};

	struct StrShowSprite {
		WORD IdShowSprite;
		WORD Dynamic;
		WORD Flags;  // FSS_
		RECT Posizione;
		WORD SlotSprite;
		WORD IndiceSprite;
		COLORREF Colore;
		short GridX;
		short GridY;
		short ExtraValue;
	};

	struct StrBaseShowSprite {
		WORD TotShowSprites;
		StrShowSprite VetShowSprites[MAX_SHOW_SPRITES];
		short VetIdShowSprites[MAX_SHOW_SPRITES*10];
	};

	struct StrPointFloat {
		float x;
		float y;
	};

	struct StrTriangolo {
		StrPointFloat A;
		StrPointFloat B;
		StrPointFloat C;
	};

	struct StrParamTriangle {
		short IdParam;
		StrTriangolo Tria;
		WORD Dynamic;
	};

	struct StrBaseParamTriangles {
		WORD TotTriangles;
		StrParamTriangle VetTriangles[MAX_TRIANGLES];
		short VetIdTriangles[MAX_TRIANGLES*10];
	};

	struct StrQuad {
		short IdParam;
		StrTriangolo Tria1;
		StrTriangolo Tria2;
		WORD Dynamic;
	};

	struct StrBaseQuads {
		WORD TotQuads;
		StrQuad VetQuads[MAX_QUADS];
		short VetIdQuads[MAX_QUADS*10];
	};

	struct StrCircle {
		short IdParam;
		short CenterX;
		short CenterY;
		WORD Radius;
		WORD Dynamic;
	};

	struct StrBaseCircle {
		WORD TotCircles;
		StrCircle VetCircle[MAX_CIRCLES];
		short VetIdCircle[MAX_CIRCLES*10];
	};

	struct StrScriptLaraStartPos {
		bool TestPresent;
		short Room;
		short OCB;
	};

	struct StrRecordAssSlot {
		WORD MioSlot;   // Slot Id
		WORD TipoSlot;  // OBJ o altro valore Slot
	};

	struct StrBaseAssignSlot {
		short TotNewAssign;
		StrRecordAssSlot VetNewAssign[MAX_ASSIGN_SLOT];
	};

	struct GAME_VECTOR {
		DWORD CordX;
		int CordY;
		DWORD CordZ;
		short Room;
	};

	struct StrGlobFish {
		bool TestImpostato; // false = bisogna ricalcolare tutto
		WORD TempoRitardo; // calcolare solo quando questo raggiunge zero
		StrAbsBoxCollision BoxCollisionLara; // creato da UpdateLocust
		bool TestLOS; // lara puntabile da pivot
		GAME_VECTOR LastLaraPos; // ultima coordinate di lara quando si poteva puntare
	};

	struct StrFloodRecord {
		WORD RoomAcqua;  // poi con +1 si trova la stanza sopra
		float OriginaleY; // valore originale di cordy di superfice acqua
		float PosYAcquaNow; // valore usato dopo load savegame
	};

	struct StrBaseFloodRooms {
		WORD TotFloods;
		StrFloodRecord VetFloods[MAX_FLOODS];
		float GapY;  // valore da sommare
		float OriginaleY; // ai vertici con questa coordinata.
		bool TestAcqua;
	};

	struct StrRecordFreeze {
		WORD ItemIndex;
		WORD Tempo;  //0xffff = ininito
	};

	struct StrBaseFreeze {
		WORD TotFreeze;
		StrRecordFreeze VetFreeze[MAX_FREEZE];
	};

	struct StrScriptStandBy {
		short IdStandBY;
		WORD TipoStandby;
		DWORD LimiteCicli;
		WORD Flags;
		short FirstText;
		WORD NumTexts;
		short AudioTrack;
		WORD VerticalOrient;
		short OrientSpeed;
		WORD Distanza;
		short IdTriggerGroupStart;
		short IdTriggerGroupEnd;
	};

	struct StrSetCamera {
		short IdCamera;
		WORD Flags; // FSCAM_...
		short Distance;
		short HOrient;
		short VOrient;
		WORD Speed;
		WORD Dynamic;
	};

	// dati per gestione di standby
	struct StrBaseStandBy {
		int TotStandBY;
		short VetID[MAX_STANDBY*10];
		StrScriptStandBy VetStandBy[MAX_STANDBY];
		int IndiceSetCamera;
		WORD IdNow;
		bool PrimaEsecuzione;
		bool TestFlipEffect; // = true, attivato con flipeffect
		DWORD LimiteCicli; // INPUT raggiunto si avvia standby
		bool TestPresente; // se c'era comando in script  per standby
		bool TestIniziato; // siamo gia' in modo standby
		short OrientSpeed; // INPUT velocita' rotazione
		short VerticalSpeed; // velocita rotazione verticale
		short IncOrientSpeed;
		short DistanzaSpeed; // velocita' percambiare distanza
		short MaxDistanza;
		short MaxVAngle;
		short MaxHOrient;	// usato solo per portrait con flip horient
		short MaxHSpeed;
		short MinHSpeed;
		short MinDistanza;
		short MinVAngle;
		short MinHOrient;
		short IdTriggerGroupStart; // trigger group da chimare in avvio
		short IdTriggerGroupEnd; // trigger group da chiamare alla fine
		int TotStringhe;     // numero testi
		short AudioTrack; // traccia audio da suonare al posto al posto, o sopra suono attuale
		short IndicePrimaStringa;
		short VerticalOrient; // INPUT ma forse non lo uso
		WORD TipoStandby; // INPUT TSB_ valore per il tipo di movimenti
		WORD Flags;		 // INPUT FSB_..
		short Distanza;   // INPUT distanza da tenere da lara
		int OldIndiceSetCamera;
		bool OldTestSetCamera;
		bool OldDisableCombat;
		DWORD OldTastiDaBloccare;
		bool OldTestFreezeAll;
		int OldTimerScreen;
		short OldAriaDisponibile;
		WORD OldTempoFlare;
		WORD OldValOscilla;
		DWORD OldContatoreSchermo;
		int ContaStringhe; // 0,1,2 ecc
		DWORD ContaTempoStringa;
		StrSetCamera OldSetCamera; // dati di camera di gioco prima dello standby
		int Reserved[40]; // to change when I modify this structure
	};

	struct StrSavegameInfos {
		WORD Flags; // FSAV_ ... flag per savegame
		WORD ShatterInizio; // primo slot statico per shatter
		WORD ShatterFine;  // ultimo slot statico per shatter
		WORD LaraStateId; // state id di lara
		short LaraVitality; // vitalita' di lara
		char Tr4Name[32]; // solonome di file .tr4 a cui si lega questo savegame
		short Veicolo; // VEC_ ... oppure -1 se non e' su un veicolo
		BYTE Copy_057_0F3[0x9d]; // copia prima parte savegame
		BYTE Copy_169_1AC[0x44]; // copia secondo blocco savegame
		WORD FlagsRoom; // flag di stanza dove si trova lara
		DWORD OffsetLara; // offset in inizio savegae di dove parte strutturalara
		BYTE SegretiTrovati_1FB; // bytre di segreti
		BYTE NonUsato;
		DWORD Distanza;
		BYTE ByteAlign;
		WORD Reserved[114]; // ulteriori sviluppi futuri
	};

	struct StrRecordFlip {
		WORD  Numero;  // numero del flipeffect
		WORD Timer; // valore argomento timer
		WORD Flags; // dati peridentificare in modo univoco questo trigger  SCANF_... scanf flags

		DWORD OffsetFloorData;
		// distanza da inizio floor data di record
		//						<TRIGGER WHAT=flipeffect> <NUMERO FLIP>
		WORD Indice; // indice item che ha eseguito questo flipeffect
		WORD PluginId; // 0= trng, or id of plugin owner of this trigger
	};

	struct StrGroupLongVar {
		union {
			int Long;
			union {
				short Short1;
				short Short2;
			};
			union {
				BYTE Byte1;
				BYTE Byte2;
				BYTE Byte3;
				BYTE Byte4;
			};
		};
	};

	struct StrVariableNames {
		StrGroupLongVar Alfa;
		StrGroupLongVar Beta;
		StrGroupLongVar Delta;
		int Timer;
	};

	struct StrBloccoNumVar {
		union {
			int VetNumeriLong[4];
			short VetNumeriShort[8];
			BYTE VetNumeriByte[16];
			StrVariableNames Name;
		};
	};

	struct StrText80 {
		char Text[80];
	};

	struct StrVariabiliGlobTRNG {
		// variabili numeriche

		StrBloccoNumVar NumWar;
		// variabili di testo
		StrText80 VetTextVar[4];


		// variabili store per savegame
		union {
			int VetStoreLong[16];
			short VetStoreShort[32];
			BYTE VetStoreByte[64];
		};

		// variabili speciali
		char LastInputText[80];
		int LastInputNumber;
		int CurrentValue;
		char TextBig[320];
		// valori per usi futuri
		DWORD VetExtra[20];
	};

	struct StrBaseVarAll {
		StrVariabiliGlobTRNG Globals;
		StrBloccoNumVar Locals;
	};

	struct StrEventoNow {
		short GlobalTrigger; // trigger avventuo
		short Parameter;  // valore in parameter
	};

	struct StrBaseEventiNow {
		int TotEventi;
		StrEventoNow VetEventi[MAX_EVENTI_NOW];
	};

	struct StrSuoni {
		int RubberBoatRun;
		int RubberBoatFolle;
		int MotorBoatRun;
		int MotorBoatFolle;
		int ElevatorMove;
		int ElevatorStop;
		int DetectorBeep;
		int Rain[4];
	};

	struct StrWindowsFont {
		HFONT hFont;
		HFONT hFontOld;
		WORD IdFont;
		WORD FlagsWFF;
		int CharSet;
		HDC HdcConFont;
		int OutSizePixel; // ottenuto da calcolo proporzionale
		COLORREF ColoreText;
		COLORREF ColoreShadow;
		short SizeFont;
		char NomeFont[80];
	};

	struct StrTempWindowsFont {
		HFONT hFontInTombHdc;
		StrWindowsFont FontNow;
	};

	struct StrBaseWindowsFonts {
		int TotFonts;
		StrWindowsFont VetFonts[MAX_FONTS];
		short VetID[MAX_FONTS*10];
		bool TestUsaWindowsFont;
		StrWindowsFont DefWindowsFont; // this is the windowsfont for all prints
		WORD FlagDWF;
		StrTempWindowsFont TempFont;  // used by current single print string
		short VetOffsetPosY[POFF_COUNTER]; // changes for y position of system menus
		short LineSpacing;  // value to modify height of character row
	};

	struct StrComPage {
		char *pTesto; // allocato dinamicamente  (lista savegames per panello)
		char *pTitolo; // allocato dinamicamente (non usata in pannello savegame)
		char *pInfoSave; // allocato dinamicamente, usata solo da panello savegame
		RECT FrameText1;  // se saveagame panel lista savegame
		RECT FrameText2;  // se savegame panel info text
		RECT FrameTitle;  // solo in savegame panel
		RECT FrameImg;
		WORD FlagsPL; // page layout
		short BgImage; // numero di immagine da usare come sfondo
		short NImage;  // o -1 se assente
		short CbBack; // suono cd di fondo (-1 niente)
		bool TestFrameText2; // true se c'e' anche il secondo text frame
		StrWindowsFont FontTitle;  // non usati in savegame panel
		StrWindowsFont FontText;  // non usati in savegame panel
		short NumeroPaginaNow;
	};

	struct StrBaseDiario {
		short ID_Diario;
		WORD TotStringhe;
		WORD VetStringhe[MAX_STRINGHE_DIARIO]; // indici ng
		int SizeTestoDiario;
		char* pTestoDiario;
		StrWindowsFont FontTitle;
		StrWindowsFont FontText;
		StrWindowsFont FontInfoSave; // usato solo per panello savegame
		int IndicePaginaToShow;  // questo in panello save significa
								 // indice savegame attualmete selezionato
		bool TestWideScreen; // ci sono premesse per fix widescreen
		WORD TotPagine; // calcolato in modo dinamico
		WORD FlagsPL; // page layout
		WORD FlagsLDF;  // flag LDF per diario
		WORD SlotDiario; // numero slot che azionera' diario in inventario
		WORD IdImage; // background image
		StrComPage PaginaNow;
		short CdIsPlaying; // suono cd di canale 1 che si sta suonando
	};

	struct StrVetDiari {
		int TotDiari;
		StrBaseDiario VetBaseDiario[MAX_DIARI];
	};

	struct StrRecordSwitch {
		WORD IdSwitch;
		WORD Flags;  // SWT_....
		WORD Variable; // place folder
		WORD TotIndici;
		short VetIndici[MAX_TRIGGER_GROUPS];
	};

	struct StrBaseSwitch {
		WORD TotSwitch;
		StrRecordSwitch VetSwitch[MAX_SWITCH];
		short VetID[MAX_SWITCH*10];
	};

	struct StrPanelloSavegame {
		bool TestPresente;
		WORD FlagsSPF;   // SPF_...
		short IdImage;  // id image savegame (o -1 se assente)
		WORD TotSave;
		WORD TotVisibili;
		WORD TipoLayout; // SPL_...
		DWORD StartTime; // contatore perlampeggio
		bool TestLampeggio; // se true mostrare altrimenti no
		WORD IndiceStringa; // testo formattato
		RECT FrameListMicros; // valori in microunits originali
		bool TestInfoSavegames; // mostrareinfo
		int IndicePrimoVisibile;
		int TotCarLinea; // numero di caratteri di linea list
		int IndiceSelezionato;
		int IndiceOldSelezionato;
		int IndiceOldPrimoVisibile;

		bool TestLoad;
		bool TestInCorso;  //mostrato attualmente
		char *pFormatta; // testo di formattazione per info savegame
						 // stringa originale non allocata e con place-folders
		char TitoloPanello[80]; // qui va copiata la string attuale
								// di "Load game" o "save game"
		StrBaseDiario MioDiario;
	};

	struct StrExtractNG {
		int Result;
		DWORD SizeHeader;
		DWORD StartOffset;
		DWORD NWords;
		WORD *pNGArray;
	};

	struct StrMiniNG_Header {
		WORD NumeroLivello;
		WORD TotWords;
		WORD *pVetWords;
	};

	struct StrBaseNG_Hub {
		WORD TotHub;
		WORD LastIndex; // indice dove era stato salvato l'ultimo livello
		StrExtractNG LaraHUB; // StrExtractNG per lara
		StrMiniNG_Header VetNG[10];
	};

	// mantiene le setting originali che possono venire cambiate
	// da funzioni trng
	struct StrSalvaSettings {
		bool TestCambiate; // usarto solo per setting usate da softfullscreen
		int Setting_VMode;
		int Setting_WindowX;
		int Setting_WindowY;
		int FlagsSettingRegistro;
		WORD DefMinFog;
		WORD DefMaxFog;
		BYTE DefVolumetricFX; // valore di setup
		BYTE DefBumpMapping;
		int Reserved[80]; // to change when I modify this structure
	};

	struct StrRecordImage {
		HDC MemHdc;  // hdc compatibile con gia' inserita l'immagine
		HANDLE hBitMap; // handle del bitmap
		HANDLE hOldBitMap; // handle del bitmap che era nell'hdc
		DWORD SizeX; // dimensione x
		DWORD SizeY; // dimensione y
		int NImage;
		bool TestUsata; // true ci sono dati singiicativi
		bool TestPreload; // immagine in preload, non scartalra finco a chiusura livello
	};

	struct StrPopUp {
		WORD NImage;
		RECT Zona;
		WORD Contatore;
		WORD IdImageCmd;
		bool TestTrasparente;
		bool TestSopraFlyBy;
		bool TestSopraFixed;
	};

	struct RectFloat {
		float OrgX;
		float OrgY;
		float SizeX;
		float SizeY;
	};

	struct StrEffettoImage {
		RectFloat Inizio;
		RectFloat Fine;
		RectFloat Inc;
		int TotFrames;
		bool TestAttivo;
		StrRecordImage  EffectImage;
	};

	struct StrShowImage {
		StrRecordImage ImageBackGround;      // 0
		StrRecordImage ImageLittle;          // 1
		StrRecordImage ImageOverlap;         // 2
		StrRecordImage Temp;                 // 3
		StrRecordImage ImageMonoScreen;      // 4
		StrRecordImage ImageLoadLevel;       // 5
		StrRecordImage ImageTitle;           // 6
		StrRecordImage ImageBinocular;		// 7
		StrRecordImage ImageLaserSight;     // 8
		StrRecordImage ImagePageDiario;     // 9
		StrRecordImage ImageBinocCompass;   // 10
		StrRecordImage ImageBinocSextant;   // 11
		StrRecordImage VetImages[MAX_IMAGE_RECORDS];
		bool TestTempHdc;
		RECT ZonaImageLittle;
		HDC HdcTomb;
		bool TestPopUp;
		StrPopUp PopUp;
		bool TestWideScreen;
		RECT ZonaSchermoTomb;
		bool TestFullScreen;
		bool TestTombAllocato;
		bool TestHdcBack;
		bool TestWriteHdc;
		StrEffettoImage Effetto;
	};

	// struttura per dati relativi a formattazione printstring
	struct StrPrintString {
		WORD Colore;   // CL_...
		WORD Unused;
		WORD Posizione; // STRING_...
		WORD Flags;  // FT_...
		BYTE BlinkSpeed;   // default era 0x10
		BYTE FlagsMicro;
		BYTE DefFlagsMicro;  // per livello al di fuori di setting per ogni flipeffect
		BYTE DefALLFlagsMicro;  // per title e roba menu
		WORD DefColore;
		WORD Unused2;
		WORD DefPosition;
		BYTE DefBlinkSpeed;
		WORD DefFlags;
		BYTE Unused3;
	};

	struct StrParamPrintText {
		StrPrintString Formatting;
		short IdPrint;
		short  DurateTime;
		short  OrgX;
		short  OrgY;
		WORD Dynamic;
	};

	struct StrBasePrintText {
		int TotPrintText;
		StrParamPrintText VetPrint[MAX_PARAM_PRINT_TEXT];
		short VetID[MAX_PARAM_PRINT_TEXT*10];
	};

	struct StrBoxCollisione {
		short MinX;			// 0x00
		short MaxX;			// 0x02
		short MinY;			// 0x04
		short MaxY;			// 0x06
		short MinZ;			// 0x08
		short MaxZ;			// 0x0A
	};

	struct StrBoxOrienting {
		short OrientVMin;	// 0x0C
		short OrientVMax;	// 0x0E
		short OrientHMin;	// 0x10
		short OrientHMax;	// 0x12
		short OrientRMin;	// 0x14
		short OrientRMax;	// 0x16
	};

	struct StrTestPosition {
		StrBoxCollisione Distance;
		StrBoxOrienting Orienting;
	};

	// strutture per memorizzare dati di comando script TestPosition
	struct StrTestPositionCmd {
		short IdTestPosition;
		WORD Flags;   // TPOS_ flags
		WORD Slot;    // slot of item to detect or index
		StrTestPosition  DatiPosition;
		WORD Dynamic;
	};

	struct StrBaseTestPosition {
		int TotTestPositions;
		StrTestPositionCmd VetTestPosition[MAX_TEST_POSITION];
		short VetId[MAX_TEST_POSITION*10];
	};

	struct StrScriptImage {
		WORD IdCommand;
		WORD NumeroImage;
		WORD Flags;
		WORD EffectTime;
		short AudioTrack;
		RECT RectZona;
	};

	struct StrBaseScriptImages {
		int TotScriptImages;
		StrScriptImage VetImages[MAX_IMAGES];
		short VetID[MAX_IMAGES*10];
	};

	struct StrBaseSetCamera {
		int TotSetCamera;
		StrSetCamera VetSetCamera[MAX_SET_CAMERA];
		short VetID[MAX_SET_CAMERA*10];
	};

	struct StrPreloadImage {
		WORD ImageId; // numero immagine
		HANDLE hBitMap; // handle del bitmap caricato
	};

	struct StrBasePreload {
		int TotPreload;
		StrPreloadImage VetPreload[MAX_IMAGES];
	};

	struct StrVersionHeader {
		WORD VetVersione[4];
		WORD Flags;	// VER_... flags
	};

	struct StrCheatNG {
		BYTE LastChars[4];
		DWORD FrameCount;
	};

	struct StrMiniShot {
		bool TestRGB;
		DWORD ShotSizeX;
		DWORD ShotSizeY;
		bool TestSalvaMiniShot; // salva in savegame i mini shot
		BYTE *pMemMiniShot; //ptr memoria per minishot catturato all'ingresso di inventario
		DWORD SizeMemMiniShot; // dimensione dei dati di file bmp
		DWORD LastTimeScreenShot;
	};

	struct StrRecordSospensione {
		int NumeroCD;
		DWORD Posizione;
		int TestLoop;
		int NuovoCD;
		int NuovoTestLoop;
	};

	struct StrAudioSospeso {
		int CountSuspend; // incremntato di 1 per ogni sospensione e -1 per ogni riprendiaudio
		StrRecordSospensione VetSospeso[10];
	};

	struct StrScriptTrigger {
		WORD PluginId;
		WORD Flags;
		WORD Object;
		union {
			WORD Timer;
			short TimerSigned;
		};
	};

	struct StrTriggerGroup {
		WORD IdGroup;
		WORD TotTriggers;
		StrScriptTrigger VetTriggers[MAX_TRIGGERS_IN_THE_GROUP];
		WORD Dynamic;
	};

	struct StrBaseTriggerGroups {
		int TotTriggerGroups;
		StrTriggerGroup VetTriggerGroups[MAX_TRIGGER_GROUPS];
		short VetID[MAX_TRIGGER_GROUPS*10];
	};

	struct StrItemGroup {
		WORD IdGroup;
		int TotIndici;
		short VetIndici[84];
	};

	struct StrBaseItemGroup {
		int TotGroups;
		StrItemGroup VetItemGroup[MAX_ITEM_GROUPS];
		short VetRemapFlipActions[256];
		short VetID[MAX_ITEM_GROUPS*10];
	};

	struct StrColoraItem {
		WORD IdColItem;
		WORD Flags; // COLTYPE_
		WORD ItemIndex;
		short IdColore1;
		short IdColore2;
		WORD Speed;
		WORD Dynamic;
	};

	struct StrBaseColoraItem {
		int TotColoraItem;
		StrColoraItem VetColoraItem[MAX_COLORA_ITEM];
		short VetID[MAX_COLORA_ITEM*10];
	};

	struct StrLastPosAlign {
		DWORD CordX;
		int  CordY;
		DWORD CordZ;
		short HOrient;
		short VOrient;
		short ROrient;
	};

	// strutturas per aggiustamento automatico di un'animazione
	struct StrAdjustAnim {
		bool TestAdjust; // solo se true c'e' adjust in corso
		short Animazione; // numero animazione
		short ItemIndex; // indice di item su cui si sta facendo aggiustamento
		StrItemTr4 *pItem; // item con cui interagisce
		short IdTestPosition; // id del test position usato
		WORD OldAnimazione;
		WORD OldFrame;

		short OrientIdeal; // e' l'orientamento effettivo da usare per il calcolo
		StrMovePosition DatiMovPos;
		StrLastPosAlign LastPosizione; // ultima posizione
	};

	struct StrAdaptiveFarView{
		float VetLastFps[3];
		float BlocchiFar;
		float MaxFarView;
		float Incremento;
		float FPStoKeep;
		DWORD LastTime; // per calcolare il passaggio di 1 secondo
	};

	struct StrPtrBars {
		DWORD *pColor1;
		DWORD *pColor2;
		union {
			int *pSizeX;
			int SizeX;
		};
		union {
			BYTE *pSizeY;
			int SizeY;
		};
		DWORD DefColor1;
		DWORD DefColor2;
	};

	struct StrHeaderTimer {
		DWORD ContaQuindicesimi;
		WORD ValOscilla;
	};

	// salva i dati di temporizzazione di acluni oggetti
	// particolari come i flame emitter
	struct StrTimerOggetti {
		WORD ItemIndex;
		WORD Campo34;
		WORD Campo36;
		WORD Campo38;
		WORD Campo3A;
	};

	struct StrBaseTimerOggetti {
		WORD TotOggetti;
		StrHeaderTimer Header;
		StrTimerOggetti VetOggetti[MAX_TIMER_OGGETTI];
	};

	struct StrMoveParameters {
		WORD IdMove;
		WORD Dynamic;
		WORD Flags;
		WORD ItemIndex;
		WORD Direzione;
		WORD Distanza;
		WORD Speed;
		short Extra;
		short SuonoMovimento;
		short SuonoFinale;
	};

	struct StrBaseMove {
		int TotMove;
		StrMoveParameters VetMove[MAX_MOVE_PARAM];
		short VetID[MAX_MOVE_PARAM*10];
	};

	struct StrParBar {
		int JumpPower;
		int GiriCompleti;
		WORD ParallelBarFlags; //copiati da customize
		DWORD TotFrames;  //numero di frame in fase di rotazione
		short SpeedSlide; // muove left / right
		bool TestMostraBarra;
	};

	// struttura mesh info che in pratica e'
	// struttura per oggetti statici
	struct StrMeshInfo {
		DWORD  x;			// 0
		int    y;			// 4
		DWORD  z;			// 8
		WORD  Orient;		// C
		WORD Color;	// E
		WORD OCB;	// 10 OCB
		WORD SlotId;		// 12
	};

	struct StrCollisionAbsBox {
		int MinX;
		int MaxX;
		int MinY;
		int MaxY;
		int MinZ;
		int MaxZ;
	};

	struct StrBaseCollisione {
		bool TestCollideStatic;
		bool TestStillCollision;
		bool TestSbattiMuro;
		StrMeshInfo *pMesh;
		WORD RoomStaticObject;
		StrCollisionAbsBox TempColBox;
		StrCollisionAbsBox BoxAbsStatic;
		StrCollisionAbsBox BoxAbsMoveable;
		WORD OrientMoveable;
		WORD SlotMoveable;
		DWORD OrgXMoveable;
		DWORD OrgZMoveable;
		int OldLaraX;
		int OldLaraZ;
		DWORD OldFrame;
		WORD OldAnimazione;
		WORD OldStateId;
	};

	struct StrInfoChar {
		float OrgX;			// 0x00
		float OrgY;			// 0x04
		WORD XSizeDestinazione;  // 0x08
		WORD YSizeDestinzione;			// 0x0A
		short BaseLine;		// 0x0C
		BYTE IndicePattern;		// 0x0E
		BYTE IndicePattern2;	// 0x0F
	};

	struct StrBaseTurbo {
		WORD Flags;
		bool TestPriorita;
		int IndicePriorita;
		bool TestAsync;
		WORD TotArg;
		WORD VetArg[255];
	};

	struct StrRotateItem {
		WORD IdMove;
		WORD Flags;
		short ItemIndex;
		short DirezioneH;
		WORD AngoloH;
		WORD SpeedH;
		short DirezioneV;
		WORD AngoloV;
		WORD SpeedV;
		short SoundMoving;
		short SoundFinal;
		WORD Dynamic;
	};

	struct StrBaseRotate {
		int TotRotate;
		StrRotateItem VetRotate[MAX_ROTATE_PARAM];
		short VetID[MAX_ROTATE_PARAM*10];
	};

	struct StrIndiciFont {
		short IndiceRedirect;
		short IndiceTexture;
	};

	struct StrSalvaStatic {
		StrCercaStatic Indici;
		WORD Flags;
		int OrgX;
		int OrgY;
		int OrgZ;
		WORD Orient;
		WORD Colore;
	};

	struct StrBaseSalvaStatic {
		WORD TotStatics;
		StrSalvaStatic VetStatics[4096];
	};

	struct StrBaseFPS {
		DWORD VetTempi[MAX_TEMPI_FPS];
		DWORD VetFrameCount[MAX_TEMPI_FPS];
		int IndiceNow;
		int LastIndice;
		int LastFps;
		DWORD TotCicli; // < o = MAX_TEMPI_FPS per sapere quanti sono disponibili
		float FPS;
	};

	// struttura record per formattazione nuovo font
	struct StrFontSetting {
		WORD Status;    // 0x00
		WORD IndiceTex; // 0x02 indice a texture 256x256
		BYTE OrgX;      // 0x04 offset ripsetto a tex256x256per riquadro carattere
		BYTE OrgY;      // 0x05
		BYTE OffX;      // 0x06 spostamento da riquadro a zona pixel effettivi
		BYTE OffY;      // 0x07
		short BaseLineY; // 0x08 adattamento di cordy
		BYTE SizeX;  // 0x0A  dimensione effettiva di zona pixel
		BYTE SizeY;  // 0x0B
	};

	struct StrFontBaseSetting {
		BYTE CheckSum;
		short TotTextures;
		WORD RapportoSize;
		short TotCaratteri;
		WORD Flags;
		BYTE SizeFont;
		int TotListFont;
		StrFontSetting VetFontList[256];
	};

	struct StrRecordClimbPush {
		WORD Indice;
		WORD TestClimb;
	};

	struct StrBaseClimbPush {
		WORD TotPush;
		StrRecordClimbPush VetPush[200];
	};

	struct StrBasePushables {
		bool TestCadutaPushable;
		WORD TotPushables;
		StrItemTr4 *VetPushables[1024];
		int VetPushablesIndex[1024];
		BYTE VetCollisionePushable[MAX_ITEMS];
		StrBaseClimbPush BaseClimbPushable;
		short IndicePushSpinto; // mentre lara spinge -1 se non sta spingendo
	};

	struct StrSingleColors {
		BYTE Red;
		BYTE Green;
		BYTE Blue;
		BYTE Unused;
	};

	struct StrColorRGB {
		WORD IdColor;
		union {
			DWORD Colore;
			StrSingleColors Single;
			WORD Dynamic;
		};
	};

	struct StrBaseColorRGB {
		int TotColori;
		StrColorRGB  VetColori[MAX_COLORI_RGB];
		short VetID[MAX_COLORI_RGB*10];
	};

	struct StrImportFile {
		WORD Id;
		DWORD Size;
		WORD Tipo;
		short NumeroFile;
		BYTE *pData;
	};

	struct StrBaseImportFile {
		int TotFiles;
		StrImportFile VetFiles[MAX_IMPORT_FILES];
		short VetID[MAX_IMPORT_FILES*10];
	};

	struct StrEnemiesNotAimable {
		int TotSlot;
		WORD VetSlotNonPuntabili[MAX_ITEMS];
	};

	struct StrRecordSFXSuonato {
		short Suono;
		DWORD FrameStart;
	};

	struct StrSFXSuonati {
		int TotSuonati;
		StrRecordSFXSuonato VetSuonati[MAX_SUONATI];
	};

	struct StrTempRoomFlags {
		WORD TotRooms;
		WORD VetRoomFlags[512];
	};

	struct StrCanaleBass {
		DWORD Canale;  //   0x00  handle of open channel or 0 if missing
		short NumeroCd; //  0x04  number of track in progress or -1 if it is missing
		int Loop;       //  0x06  when audio track is looped
	};

	struct StrProcBassDllExtra {
		// only example: then it will be replace and integrated with new bass proc:
		TYPE_BASS_ChannelGetPosition BASS_ChannelGetPosition;
	};

	struct StrProcBassDll {
		TYPE_BASS_Init BASS_Init;
		TYPE_BASS_Free BASS_Free;
		TYPE_BASS_ChannelSlideAttribute  BASS_ChannelSlideAttribute;
		TYPE_BASS_ChannelSetAttribute BASS_ChannelSetAttribute;
		TYPE_BASS_StreamCreateFile BASS_StreamCreateFile;
		TYPE_BASS_ChannelPlay BASS_ChannelPlay;
		TYPE_BASS_ErrorGetCode 	BASS_ErrorGetCode;
		TYPE_BASS_Pause BASS_Pause;
		TYPE_BASS_Start BASS_Start;
		TYPE_BASS_ChannelFlags BASS_ChannelFlags;
		TYPE_BASS_ChannelStop BASS_ChannelStop;
		TYPE_BASS_Stop BASS_Stop;
		TYPE_BASS_ChannelSetPosition BASS_ChannelSetPosition;
		TYPE_BASS_ChannelIsActive  BASS_ChannelIsActive;
		TYPE_BASS_ChannelGetPosition BASS_ChannelGetPosition;
		TYPE_BASS_StreamGetFilePosition  BASS_StreamGetFilePosition;
	};

	struct StrBassHandles {
		StrCanaleBass VetCanali[4];  // reduced by [1] the channel array to host following pointer for extra Proc
		StrProcBassDllExtra * pProcExtra; // point to new list of bass procedures
		BYTE Reserved[6];  // placefolder to preserve offset of following "CanaleNow" field
		int CanaleNow; // 0 o 1 used to set what channel we are using
		DWORD StartOffset;
		float VolumeMusica;
		short OldCdLoop; // Last cd audio track on 0 channel
		bool TestPresente;
		HINSTANCE  HandleDll;
		StrProcBassDll Proc;
	};

	struct StrAddDeadAnim {
		short Indice;
		WORD AnimIndex;
	};

	struct StrBaseDeadAnim {
		int TotDeadAnim;
		StrAddDeadAnim VetDeadAnim[MAX_DEAD_ANIM];
	};

	struct StrSoundSettings {
		WORD MusicQuality;
		short VolumeMusic;
		short VolumeSFX;
	};

	struct StrFlipMapRooms {
		int TotFlipRooms;
		short VetRoomMain[512];  // access with index of fliproom. example MainRoomIndex = VetRoomMain[FlipRoomIndex]
	};

	struct StrMoveAdvance {
		WORD IdMove;
		WORD Flags;
		WORD Direction;
		WORD Distance;
		WORD Speed;
		short IndiceTriggerGroup;
		short SoundStart;
		short SoundMoving;
		short SoundFInal;
		WORD Dynamic;
	};

	struct StrBaseMovAdvance {
		int TotMoveAdvance;
		StrMoveAdvance VetMove[MAX_MOVE_ADVANCE];
		short VetID[MAX_MOVE_ADVANCE*10];
	};

	// struttura per salvari tutti i mesh swap effettuati
	struct StrFlipSwapMesh {
		WORD TipoSwapMesh;  // se c'e il bit 0x4000 allora e' solo un copy
		short SlotItem; // se 0 allora e' swap per lara
		short SlotAltroSlot;
	};

	struct StrBaseFlipSwap {
		WORD TotMeshSwap;
		StrFlipSwapMesh VetMeshSwap[MAX_SWAP_MESH];
	};

	struct BaseNewObjects {
		int IndiceAnimRubberBoat;	// dati per nuovo oggetto RUBBER BOAT
		int IndiceRubberBoat;
		int IndiceAnimMotorBoat;
		int IndiceMotorBoat;
	};

	struct StrDatiDiagAnim {
		short NumAnim;
		short ReplaceAnim; // only for animslot
		bool TestEsito;
		WORD Slot;         // only for animslot
		short ItemIndex;   // only for animslot
	};

	struct StrAnimDiag {
		int TotAnim;
		StrDatiDiagAnim VetDiag[MAX_ANIM_DIAGNOSTIC];
	};

	struct StrRollingPush {
		WORD Animation; //usata per pushing rollingball
		WORD AnimFallito; // usata quando lara non puo' spingere rolling
		WORD FrameStartPush; // frame da cui si inizia a spingere passivamente rolling
		WORD FrameStartActivation; // frame di quando viene attivato il rolling
		WORD Distance; // usata per calcolo distanza corretta da rolling
		WORD FrameInvulnerabile; // numero di frame senza ferire lara
		WORD SpeedPushing; // relativo a spostamento passivo
	};

	struct StrBassDll {
		WORD Frequenza; // default 44100
		WORD TimeFadeOut; // default 1000
		WORD TimeFadeOutCorto; // default 300
		WORD Flags; // NSE_ ... flags
		WORD TipoEstensione;  // SEXT_ ... costanti
	};

	// Dati specifci per ogni munizione
	struct StrCustAmmo {
		WORD Flags;  // AMMO_...   00
		short DamageNormale;	// 02
		short Pickup;           // 04
		short PickupRegalo;     // 06
		short DamageEsplosivo;  // 08
		short IdTriggerHitEnemy;// 0A
		short Speed;            // 0C
		short Gravity;          // 0E
		short IdAddEffect;      // 10
		short IdTriggerAtEnd;   // 12
		short Extra;            // 14
	};

	// contiene tutti i dati trovati nel comando script
	struct StrCustWeapon {
		WORD Flags;      // WEAP_...
		short SoundShot;
		BYTE FramesRicarica;
		BYTE SizeShell;
		WORD DistanceAiming;
		BYTE  FrameToTakeWeapon;
		BYTE  FrameToLetWeapon;
		WORD Dispersion;
		short Extra;
		short VPositionOfWeapon;
		WORD Unknow; // DatoArmaEstratta
		BYTE FrameCounter; // VetDatiOggettiMano[2]
		BYTE FrameMinRange; // VetDatiOggettiMano[3]
		BYTE FrameMaxRange; // VetDatiOggettiMano[5]
		short OrigX;  // origine
		short OrigY;  // di proiettili
		short OrigZ;  // visibili
		WORD Orient;
	};

	struct StrBaseInvItems {
		int TotInvItems;
		WORD VetInvItems[256];
	};

	struct StrTwoBytes {
		BYTE AlfaByte;
		BYTE BetaByte;
	};

	struct StrDoublePosition {
		StrPosizione From;
		StrPosizione To;
	};

	struct StrRectXY {
		RECT Rect;
		int XCord;
		int YCord;
	};

	// structure of progressive action
	// size 36 (0x24)
	struct StrProgressiveAction {
		WORD ActionType;  // AXN_ code

		short ItemIndex;  // Index of item to manage
		WORD Arg1;  // durate of the action: number of frames or 0xffff for endless
		union {
			WORD Arg2;    //  variable for customizable targets
			StrTwoBytes Bytes;
		};
		union {
			int  VetArg[6];  // 6 numbers of int type (32 signed bits)
			float VetArgFloat[6];
			WORD VetArgWord[12];
			short VetArgShort[12];
			BYTE VetArgBytes[24];
			char VetArgSignedBytes[24];
			DWORD VetArgDword[6];
			StrDoublePosition Coords;
			StrRectXY Box;
		};
	};

	struct StrShowAmmoCounter {
		StrPrintString TexAmmoCounter;
		bool TestShowAmmoCounter;
		StrProgressiveAction AzioneTestoCounter;
		char Testo[80];
		WORD Flags;
	};

	struct StrAnimMorte {
		short Slot;
		short AnimIndex;
	};

	struct StrBaseAnimMorte {
		WORD TotCustAnimMorte;
		StrAnimMorte VetAnimMorte[MAX_ANIM_MORTE];
	};

	struct StrBarraCust {
		short OrgX;   // 0x00
		short OrgY;   // 0x02
		WORD SizeX;   // 0x04
		BYTE SizeY;   // 0x06
		WORD Flags;   // 0x07
		DWORD Color1;  // 0x09 (non piu' id ma colore rgb gia' espanso)
		DWORD Color2;  // 0x0D (non id ma colore)
		short Extra;  // 0x11 valore originale di script
		DWORD ExtraLong; // 0x13 valore riealborato se colore 3
		short OrgYUpdated; // 0x17  valore aggiornato in modo corretto
	};

	struct StrCustCamera {
		WORD Flags;  // FCAM_ ...
		short ChaseDistance;
		short ChaseHeight;
		WORD ChaseHOrient;
		short CombatDistance;
		short CombatHeight;
		short LookDistance;
		short LookHeight;
		WORD Speed;
	};

	struct StrCustInnerShot {
		WORD FlagQSF;
		bool TestAddInnerShot;
	};

	struct StrBaseHarpoon {
		bool TestArpione; // al posto di balestra
		WORD ArpioneFlags; // ARP_...
		WORD OrientX;
		WORD OrientY;
		WORD OrientZ;
		short Distance;
		short TopY;
		short HSpeed;
		WORD Gravity;
	};

	struct StrCustLightItems {
		int Rosso;
		int Verde;
		int Blue;
		int Intensita;
		int Time;
	};

	struct StrCatturaShot {
		WORD Secondi;
		WORD FrameGap;
		short QaulitaImage;
		bool TestInCorso;
	};

	struct StrDartCustomize {
		short IdCustomize;    // 0x0000
		WORD Flags;			  // 0x0002   DRT_ ...
		short IdAddEffect;    // 0x0004
		short Speed;          // 0x0006
		short EmittingTimer;  // 0x0008
		COLORREF ColorMain;   // 0x000A
		COLORREF ColorSecondary; // 0x000E
		short IdTriggerGroup;  // 0x0012
	};

	struct StrBaseDartCustomize {
		WORD TotCust;
		StrDartCustomize VetCust[MAX_DART_CUST];
	};

	struct StrCustFlare {
		WORD Flags;  // FFL_
		WORD Durata; // -1 = infinita
		WORD Rosso;
		WORD Verde;
		WORD Blu;
		WORD Intensita;
		DWORD Valore810;
		DWORD Valore876;
	};

	struct StrStillCollision {
		WORD Flags; // COLL_...
		short LowerHeight;
		BYTE VetSlotStillCollisions[SLOT_NUMBER_OBJECTS];
	};

	struct StrRollBoatScript {
		WORD Slot;
		WORD Flags; // FRB_...
		short SpeedSwing;
		short SpeedPitch;
		short SoundSfx;
	};

	struct StrBaseRollBoatScript {
		WORD TotRollBoatScript;
		StrRollBoatScript VetRollBoatsScript[MAX_ROLL_BOAT_SCRIPT];
	};

	struct StrSlotVehicleCollide {
		int TotSlotCollide;
		WORD VetSlotCollide[MAX_SLOT_COLLIDE];
	};

	struct StrCustBinocular {
		bool TestPresente;  // when there is a Customize=CUST_BINOCULARS in current level
		WORD Flags;   // BINF_... flags
		short Parameter;   // option value that could work in according with some BINF_ flag
		short CompassImage;  // direct number, not image ID  (1024x768)
		short CompassRect;   // Id rect + BINT_...
		short SextantImage;  // direct number of image
		short SextantRect;    // Id rect+ BINT_...
		short LightnessRect;       // lightness rect id
		short ZoomRect;    // id rect + BINT_ for zoom-in factor
		short LighSwitchRect;  // zone of light switch and BINT_ type
		int FontId;   // id of font used for typing operation
	};

	struct StrCustSlotFlag {
		WORD Slot;
		WORD Flags; // FFS_... flags
	};

	struct StrBaseSlotFlags {
		int TotSlotFlags;
		StrCustSlotFlag VetSlotFlags[MAX_SLOT_FLAGS];
	};

	struct StrShaterCustSpecific {
		int TotSpecific;
		short VetSpecific[256];
	};

	struct StrBaseCustomize {
		bool TestDisabilitaDoppiaTesta; // def = false
		short SecretsAmount;			    // def = 70
		short CreditsLevel;				// def = 39
		bool TestDisableAnim96;
		WORD ShatterInizio;  // def = 0x32
		WORD ShatterFine;    // def = 0x3b (ma usare -1)
		StrRollingPush RollingBallPush;
		StrBassDll BassDll;
		StrLaraHp BaseHpLara;

		DWORD SlotChiaveJeep; // def= 175
		WORD SpeedMoving; // def=32 usata per velocita' movimgneot oggetto
		StrCustAmmo AmmoPistols;
		StrCustAmmo AmmoRevolver;
		StrCustAmmo AmmoFucileNormale;
		StrCustAmmo AmmoFucilePotenziate;
		StrCustAmmo AmmoUZI;
		StrCustAmmo AmmoBalestraNormali;
		StrCustAmmo AmmoBalestraEsplosive;
		StrCustAmmo AmmoBalestraVelenose;
		StrCustAmmo AmmoGranateNormali;
		StrCustAmmo AmmoGranateEsplosive;
		StrCustAmmo AmmoGranateLuminose;

		StrCustWeapon WeaponPistols;
		StrCustWeapon WeaponUzi;
		StrCustWeapon WeaponFucile;
		StrCustWeapon WeaponBalestra;
		StrCustWeapon WeaponLanciaGranate;
		StrCustWeapon WeaponRevolver;
		StrBaseInvItems BaseInvItems;
		StrShowAmmoCounter ShowAmmoCounter;
		DWORD TrasparenzaGlass;
		DWORD TrasparenzaIce;
		WORD DamageStatic;
		WORD PoisonStatic;
		bool TestNoTransparencyLara;
		WORD HairType;
		bool TestKeepNemiciMorti;
		bool TestOldCDTrigger;
		bool TestEscapeFlyCamera;
		WORD TastoEsciFlyCamera;
		bool TestPauseFlyCamera;
		WORD TastoPauseFlyCamera;
		bool TestPrintOnFlyby;
		bool TestNoTimeInSaveList;
		short TipoCDM; // CDM_...
		StrBaseAnimMorte BaseAddAnimMorte;
		StrBarraCust VetBar[BAR_CUST_TOT];
		WORD ParallelBarFlags; // PB_...
		WORD ParalledSpeedSlide;
		WORD ParallelMaxTurns;
		DWORD BugsToFix;  // BUGF_...
		StrCustCamera CameraCust;
		bool TestDisableMissingSounds;
		StrCustInnerShot ScreenShotInner;
		WORD FlagsFMV;  // FMV_ ...
		bool TestFixWaterFogBug;
		bool TestSaveLocust;
		StrBaseHarpoon BaseHarpoon;

		StrCustLightItems AmberLight;
		StrCustLightItems WhiteLight;
		StrCustLightItems BlinkingLight;

		StrCatturaShot BaseCatturaShot;
		bool TestTr5Collisions;
		StrBaseDartCustomize BaseDartCustomization;
		StrCustFlare BaseFlare;
		BYTE VetTTColors[TT_MAX_TEXT_TYPES];
		StrStillCollision BaseStillCollision;
		char WaterfallSpeed;
		StrBaseRollBoatScript BaseRollScript;
		short VetCustSFX[MAX_CUST_SFX];
		short TitleFmv;  // -1 = no fmv
		bool TitleTestMultiply;
		StrSlotVehicleCollide BaseSlotCollideVehicles;
		bool TestDisablePushAway;
		StrCustBinocular CustBinoculars;
		StrBaseSlotFlags BaseSlotFlags;
		StrShaterCustSpecific BaseShatterSpecific;
	};

	struct StrCoppiaPerform {
		WORD Secondi;
		WORD IdGroup;
	};

	struct StrScriptOrganizer {
		WORD Id;
		WORD Flags;
		WORD Parameter;
		int  TotCoppie;
		StrCoppiaPerform VetCoppie[MAX_ORGANIZE_COPPIE];
	};

	struct StrStatusOrganizer {
		WORD Status;   // 0 disabled / 1 enabled
		WORD indiceNow;
		DWORD StartPerformed;  // secondi di ultima esecuzione o abilitazione
	};

	struct BaseScriptOrganizer {
		WORD TotOrganizer;

		DWORD CounterGame;  // tempo assoluto di gioco in frame
		StrScriptOrganizer VetOrganizer[MAX_ORGANIZERS];
		StrStatusOrganizer VetStatusOrganizer[MAX_ORGANIZERS]; // da salvare in savegame
		short VetID[MAX_ORGANIZERS*10];
	};

	struct StrDoppiaWord {
		short WordBassa;
		short WordAlta;
	};

	struct StrGlobalTrigger {
		short GlobalTrigger;
		union {
			long Parameter;
			StrDoppiaWord ParamWords;
		};
		WORD Id;
		WORD Flags;
		short IndiceConditionGroup;
		short IndicePerformGroup;
		short IndiceFalseGroup;
	};

	struct StrBaseGlobalTriggers {
		int TotTriggers;
		StrGlobalTrigger VetTriggers[MAX_GLOBAL_TRIGGERS];
		short VetID[MAX_GLOBAL_TRIGGERS*10];
		bool TestPresoLittleMedipack;
		bool TestPresoBigMedipack;
		bool TestSalvatoSavegame;
		bool TestCaricatoSavegame;
	};

	struct StrSalvaCollisioni {
		StrItemTr4 *pNemico;
		WORD Flags;
	};

	struct StrBaseSalvaCollisioni {
		int TotCollisioni;
		StrSalvaCollisioni VetCollisioni[MAX_COLLISIONI];
	};

	struct StrWideScreen {
		int SizeX;
		int SizeY;
		float RapportoSchermo;
	};

	struct StrRemapTailInfo {
		WORD IndiceTom;
		WORD IndiceTr4;
	};

	struct StrBaseRemapTailInfo {
		WORD TotTails;
		StrRemapTailInfo VetRemapTail[MAX_TAIL_INFOS*2];
	};

	// dati per animare texture in tomb4

	struct StrAnimUVRotate {
		float VetOrgY[MAX_TEX_PER_FRAME]; // posizione OrgY originale di texture in pagine 256x256
		WORD  VetTailIndex[MAX_TEX_PER_FRAME]; // indice tail da modificare

		int TotTextures;
		float Height;  // altezza texture (sara' la meta' di originale)
		int UvRotate; // valore da aggiungere a ScrollPos per movimento
		int   Maschera; // maschera per valore massimo di posy (0x1f, 0x3f o 0x7f)
		DWORD LastTime; // tickcount di ultima esecuzione
		DWORD DelayTime;  // numero di tick oltre il quale si deve eseguire un altro
						  // scroll se 0, eseguire sempre
		int ScrollPos;  // posizione di inquadratura attuale da aggiungere a OrgY
		bool TestStop; // per bloccare scrorrimento (da usare con flipeffect)
		bool TestTriangolo; // e' un triangolo
		int IndiceVerticeTop; // indice dove c'e' cordy piu' in alto del triangolo
		WORD TipoAnim; // per tipo di scroll
		int IndiceRangeNG; // indice range originale
	};

	struct StrTexInfoTr4 {
		WORD Attribute;			// 0
		WORD Tail;				// 2
		WORD Flags;				// 4
		float TopLeft[2];		// 6
		float TopRight[2];		// 0E
		float BottomRight[2];	// 16
		float BottomLeft[2];	// 1E
								// 26
	};

	struct StrAnimFrame {
		DWORD LastTime;
		DWORD DelayTime;
		bool TestStop;
		int  TotTextures;
		WORD TipoAnim;
		WORD VetTailIndex[MAX_TEX_PER_FRAME];  // indici originali
		WORD VetChangedPos[MAX_TEX_PER_FRAME]; // indici d'ordine dopo modifiche
		StrTexInfoTr4 VetTexInfoRecords[MAX_TEX_PER_FRAME]; // valori originali dei tex info
		int  FrameToSet;  // usato solo per p-frame animazione
		int IndiceToSet;  // indice (da 0..) della texture da sostituire.
						  // se -1 farlo con tutte le texture.
		int IndiceScrollRiver;
		int IndiceRangeNG;
	};

	struct StrBaseAnimTr4 {
		StrAnimUVRotate VetUVRanges[MAX_TAIL_INFOS]; // dati per animazione tex uv range
		StrAnimFrame VetFrameRanges[MAX_TAIL_INFOS]; // dati per animazioni di tipo frame
		int TotUvRanges;  // numero di uv ranges salvati in VetUvRanges[]
		int TotFrameRanges; // numro di fram range salvati in vetframe range
	};

	struct StrEnvMultCondtion {
		WORD EnvCondition;
		short DistanceEnv;
		WORD Extra;
	};

	struct StrScriptEnvMultCondition {
		WORD TotEnvCondition;
		WORD IdEnvScript;
		StrEnvMultCondtion VetEnvCondition[MAX_ENV_CONDITIONS];
		WORD Dynamic;
	};

	struct StrBaseScriptEnvCondition {
		int TotScriptEnvCondition;
		StrScriptEnvMultCondition VetScriptEndCondition[MAX_ENV_SCRIPT_CONDITIONS];
		short VetID[MAX_ENV_SCRIPT_CONDITIONS*10];
	};

	struct StrTexSequence {
		WORD IdSequenza;
		WORD Flags; // SEQ_ .. flags
		WORD FPS;
		WORD TotFrames;
		WORD FrameDelay;
		BYTE VetFrames[1200];
	};

	struct StrBaseTexSequence {
		int TotSequenze;
		StrTexSequence VetSequenze[MAX_TEX_SEQUENCE];
		short VetID[MAX_TEX_SEQUENCE*10];
	};

	struct StrEquipItem {
		WORD Slot;
		short Quantita;
	};

	struct StrBaseEquipItem {
		int TotEquip;
		StrEquipItem VetEquip[MAX_EQUIP_ITEM];
	};

	struct structStrDoorTr4 {
		WORD IndiceRoom;
		short VisiblePoint[3];
		short VetCorners[12];
	};

	struct StrBaseDoors {
		WORD TotDoors;
		structStrDoorTr4 VetDoors[256];
	};

	struct Tipo_CollGridTr4 {
		WORD FloorDataIndex;   // 00
		WORD BoxZoneIndex;     // 02
		char BelowRoomIndex;   // 04
		char FloorHeight;	   // 05
		char AboveRoomIndex;   // 06
		char CeilingHeight;		// 07
	};

	// structure for tr4 room light
	struct StrLigthTr4 {
		DWORD OrigX;    // 00
		int OrigY;      // 04
		DWORD OrigZ;    // 08
		BYTE ColorRed;   // 0c
		BYTE ColorGreen; // 0d
		BYTE ColorBlue;  // 0e
		BYTE LightType;  // D3D_ values
		BYTE lgh_Mistery1;  // usually  255  (0xFF)
		BYTE Intensity;   // 11
		float LightIn;    // 12
		float LightOut;   // 16
		float LightLenght;  // 1A
		float LightCutOff;  // 1e
		float TargetX;   // targets are not absolute coordinates but they seem degrees
		float TargetY;  // 26
		float TargetZ;  // 2a
	};

	struct Tipo_VerticeRoom {
		float x;
		float y;
		float z;
	};

	// strutture room per tr4 (size 0x94)
	struct StrRoomTr4 {
		void *pStaticDataRoom;   // 00
		StrBaseDoors *pDoors; 	// 04
		Tipo_CollGridTr4 *pCollsionSectors; // 08
		StrLigthTr4 *pLights;           // 0c
		StrMeshInfo *Ptr_StaticMesh;  // 10
		int  OriginX;                 // 14
		int  OrgYMistery;           // 18 roba per superfice acqua
		int  OriginZ;                 // 1C
		int  OrigYBottom;           // 20
		int  OrigYTop;              // 24
		WORD Z_SizeSectors;         // 28
		WORD X_SizeSectors;         // 2A
		DWORD ColorIntensityLight;  // 2C
		WORD TotLights;             // 30
		WORD TotStaticMesh;         // 32
		BYTE WaterIntensity;		// 34
		char FlipMapIndex;    // 35
		char IndexTabWater;			// 36
		BYTE TestFlagsBound;        // 37
		short  SizeXScreenOther;           // 38
		short rm_Mistery3A;			// 3A
		short  SizeYScreenOther;		    // 3C
		short rm_Mistery3E;			// 3E
		short  rm_Mistery40;			// 40
		short SizeXScreen;			// 42
		short  rm_Mistery44; 			// 44
		short  SizeYScreen;		// 46
		short FirstItemIndex;		// 48
		short FirstEffect;		// 4A
		short  AlternateRoom;		// 4C  -1 se non c'e' o e' stanza flippata?
		WORD  FlagsRoom;		    // 4E
		int  VerticesAmount;			// 50
		int  VerticesWaterAmount;				// 54  solo centrali e mobili
		int  VerticesDryAmount;				// 58  numero dei vertici non acqua
		void* pDirect3dVertexBuffer; // 5C  vertici passati per creare la stanza
		void* pRectangles;			// 60
		float floatOrigX;			// 64
		float floatOrigY;			// 68
		float floatOrigZ; 			// 6C
		int VerticesOffset;				// 70 accede a vetverticifloat per inizio vertici di qualche tipo
		void *pTriAndQuads;		// 74
		void *pQuadVertices;  //78
		void *pTriVertices;  // 7C
		int  rm_Mistero80; 			// 80
		Tipo_VerticeRoom *pVetVerticiFloat;    // 84
		int  TrianglesAmount; 			// 88
		int  RectanglesAmount;			// 8C
		void *pLightObjects;		// 90  directx object created with light data
	};

	struct StrInventoryItems {
		BYTE WeaponPistols;		//  FWEAP_ values to test with & operator (bit flags)
		BYTE WeaponUZI;		//  FWEAP_ values to test with & operator (bit flags)
		BYTE WeaponShotGun;		//  FWEAP_ values to test with & operator (bit flags)
		BYTE WeaponCrossBow;		//  FWEAP_ values to test with & operator (bit flags)
		BYTE WeaponGrenadeGun;		//  FWEAP_ values to test with & operator (bit flags)
		BYTE WeaponRevolver;		//  FWEAP_ values to test with & operator (bit flags)
		BYTE LaserSight;		//  0 / 1
		BYTE Binoculars;		//  0 / 1
		BYTE Crowbar;		//  0 / 1
		BYTE ClockWorkBeetle;		//  CBEET_ values to test with & operator (bit flags)
		BYTE WaterSkinSmall;		//  WSKIN_ values to test in mixed way, sometimes with == and other flag with &
		BYTE WaterSkinLarge;		//  WSKIN_ values to test in mixed way, sometimes with == and other flag with &
		BYTE ExamineItem1;		//  0 / 1
		BYTE ExamineItem2;		//  0 / 1
		BYTE ExamineItem3;		//  0 / 1
		BYTE PuzzleItem1;		//  quantity
		BYTE PuzzleItem2;		//  quantity
		BYTE PuzzleItem3;		//  quantity
		BYTE PuzzleItem4;		//  quantity
		BYTE PuzzleItem5;		//  quantity
		BYTE PuzzleItem6;		//  quantity
		BYTE PuzzleItem7;		//  quantity
		BYTE PuzzleItem8;		//  quantity
		BYTE PuzzleItem9;		//  quantity
		BYTE PuzzleItem10;		//  quantity
		BYTE PuzzleItem11;		//  quantity
		BYTE PuzzleItem12;		//  quantity
		WORD ComboItems;		//  COMBO_ values to test with "&" operator (bit flags)
		WORD Keys;				//  EX16_ values to test with "&" operator (bit flags)
		WORD KeyCombo;			//  KCOMBO_ values to test with "&" operator (bit flags)
		short PickupItems;		//  EX16_ values to test with "&" operator (bit flags)
		short PickupCombo;		//  PCOMBO_ values to test with "&" operator (bit flags)
		short QuestItems;		//  EX16_ values to test with "&" operator (bit flags)
		short MediPackSmall;		//  quantity (-1 = unlimited)
		short MediPackLarge;		// quantity (-1 = unlimited)
		short Flares;		// quantity (-1 = unlimited)
		short AmmoPistols;		// quantity (-1 = unlimited)
		short AmmoUZI;		//  quantity (-1 = unlimited)
		short AmmoRevolver;		// quantity (-1 = unlimited)
		short AmmoShotgunNormals;		//  quantity multiple by 6 (-1 = unlimited)
		short AmmoShotgunWideShot;		//  quantity multiple by 6 (-1 = unlimited)
		short AmmoGrenadeNormals;		// quantity (-1 = unlimited)
		short AmmoGrenadeSuper;		//  quantity (-1 = unlimited)
		short AmmoGrenadeFlash;		// quantity (-1 = unlimited)
		short AmmoCrossBowNormals;		// quantity (-1 = unlimited)
		short AmmoCrossBowPoison;		// quantity (-1 = unlimited)
		short AmmoCrossBowExplosive;		// quantity (-1 = unlimited)
		BYTE ClockWorkBeetleAvailUsage;		// available times to use it. When it becomes 0 it will explode but it is 0 also when beetle has not yet been picked up
	};

	struct StrSlot {
		WORD  TotMesh;		// 0
		WORD  IndexFirstMesh;	// 2
		int   IndexFirstTree;	// 4
		int   IndexFirstFrame;  // 8
		void *pProcInitialise;	// 0C
		void *pProcControl;		// 10
		void *pProcFloor;		// 14
		void *pProcCeiling;		// 18
		void *pProcDraw;		// 1C
		void *pProcCollision;   // 20
		WORD  DistanceForMIP;      // 24
		WORD  IndexFirstAnim;   // 26
		short Vitality;			// 28
		WORD DistanceDetectLara;		// 2A
		WORD ss_Unknown3;		// 2C
		WORD FootStep;			// 2E
		WORD  TestGuard;		// 30
		WORD Flags;				// 32  (FSLOT_ flags)
		void *pProcDrawExtras;	// 34
		int  ShatterableMeshes;		// 38
		int  ss_Unknown5;		// 3C
	};

	struct StrBaseHandle {
		HANDLE hThread;
		HANDLE hProcess;
	};

	// struttura singolo record animation
	struct StrAnimationTr4 {
		DWORD FrameOffset;		// 0x00
		BYTE  FrameRate;		// 0x04
		BYTE  FrameSize;		// 0x05
		WORD  StateId;			// 0x06
		int   Speed;			// 0x08  (speed multiplied by 65536)
		int   Accel;			// 0x0C  (accel multiplied by 65536)
		int   SpeedSide;		// 0x10  (speed multiplied by 65536)
		int   AccelSide;		// 0x14  (accel multiplied by 65536)
		WORD  FrameStart;		// 0x18
		WORD  FrameEnd;			// 0x1A
		WORD  NextAnimation;	// 0x1C
		WORD  NextFrame;		// 0x1E
		WORD  NumStateChanges;	// 0x20
		WORD  StateChangeOffset; // 0x22
		WORD  NunAnimCommands;	// 0x24
		WORD  AnimCommand;		// 0x26
	};

	// size = 0x1c
	struct StrStaticSlot {
		WORD IndiceMesh;   // 00
		WORD SlotStatic;   // 02
		StrBoxCollisione ViewBox;  // 04
		StrBoxCollisione CollisionBox;  // 10
	};

	struct StrDatiCollSettore {
		int FloorDist;
		int CeilingDist;
		int Inclinatura;
	};

	// super mega struttura per dati collisione
	struct StrCollisionLara {
		StrDatiCollSettore  VetInfoSettori[6];  // 0x000
		int LaraSizeX;		// 0x048
		int LaraBottomY;		// 0x04C
		int LaraTopY;			// 0x050
		int LaraSizeZ;			// 0x054

		int GridShiftX;			// 0x058 ??
		int GridShiftY;			// 0x05C  ??
		int GridShiftZ;			// 0x060  ??

		int LaraOldX;		// 0x064
		int LaraOldY;		// 0x068
		int LaraOldZ;		// 0x06c

		WORD StateIdOld;		// 0x070
		WORD AnimNowOld;		// 0x072
		WORD FrameNowOld;		// 0x074
		WORD OrientHOld;		// 0x076
		WORD Direzione;		// 0x078
		WORD EsitoColl;		// 0x07A  1=hang bordo
		WORD *pFloorData;	// 0x07C
		char ClickSlopeAlfa;		// 0x080
		char ClickSlopeBeta;  // 0x81
		BYTE Flag1;		// 0x082
		BYTE TestBlocca;  // 0x83
		WORD Flags2;		// 0x084   ;0x5 = climb girando angolo
	};

	struct StrMeshTr4 {
		short CenterX;		// 0x00
		short CenterY;		// 0x02
		short CenterZ;		// 0x04
		WORD SphereRadius;  // 0x06
		WORD Collision;		// 0x08
		short NVertici;		// 0x0A
	};

	struct StrAIDataTr4 {
		WORD SlotAI;  // valore di slot id
		WORD RoomIndex;
		DWORD CordX;
		int  CordY;
		DWORD CordZ;
		WORD Ocb;
		WORD Buttons;
		DWORD Orientation;
	};

	struct StrCameraTr4 {
		DWORD CordX;		// 0X00
		int  CordY;			// 0X04
		DWORD CordZ;		// 0X08
		WORD Room;			// 0X0c
		WORD Flags;			// 0X0e
	};

	struct StrAdrCamera {
		StrCameraTr4 *pVetCamera;
		short *pIndexCameraNext;
		short *pIndexCameraNow;
		StrItemTr4 **pTargetCameraNext;
		StrItemTr4 **pTargetCameraNow;
		GAME_VECTOR *pCameraSrc;
		GAME_VECTOR *pCameraTarget;

		short *pSecondsTimerCamera;
		WORD *pButtonTriggerCamera;
		int *pModeCameraNext;
		int *pModeCameraNow;
		int *pTotCameras;
	};

	struct StrAdrFlipMap {
		int *pVetEnabledFlipMaps;
		int *pVetButtonFlipMaps;
	};

	struct StrFlyByTr4 {
		DWORD OrgX;				// 0x00
		int OrgY;				// 0x04
		DWORD OrgZ;				// 0x08
		DWORD TargetX;			// 0x0C
		int TargetY;			// 0x10
		DWORD TargetZ;			// 0x14
		BYTE Seq;				// 0x18
		BYTE Num;				// 0x19
		WORD FrameOffset;		// 0x1A
		WORD Mistery1;			// 0x1C
		WORD Mistery2;			// 0x1E
		WORD Speed;				// 0x20
		WORD CameraButtons;		// 0x22
		WORD RoomIndex;			// 0x24
		WORD Mistery3;			// 0x26
	};

	struct StrCustDatiOggettoMano {
		WORD SlotAnim;			// 0x00
		BYTE FrameCounter;		// 0x02
		BYTE FrameMinRange;		// 0x03
		BYTE FrameChangeArma;  // 0x04
		BYTE FrameMaxRange;   // 0x05
	};

	struct StrDatoInventario {
		WORD Slot;		// 0x00
		short OffsetY;       // 0x02
		WORD Distance;    // 0x04
		WORD OrientX;      // 0x06
		WORD OrientY;      // 0x08
		WORD OrientZ;      // 0x0A
		WORD Flags;    	// 0x0C
		WORD IndiceStringa;    // 0x0E
		int  Mistero;    // 0x10 passato a drawinventoryitemme
	};

	// record di 7FE890h    ;Ptr_VetBoxInfos
	struct StrBoxZones {
		BYTE x1;		// 0x00
		BYTE x2;		// 0x01
		BYTE z1;		// 0x02
		BYTE z2;		// 0x03
		WORD Flags;		// 0x04
		WORD OverlapIndex;  // 0x06
	};

	// struttura per record pesci (e simile a quella di scarabei
	struct StrFish {
		int CordX;		// 00
		int   CordY;		// 04
		int CordZ;		// 08
		short OrientV;		// 0C
		short OrientH;		// 0E
		BYTE IndicePivot;	// 10  (era OrientR)
		BYTE Tempo;			// 11 (Aggressivo=0x80 / MeshTipo 0x60 / TempoFase 0x1f
		BYTE Room;			// 12
		BYTE FlagFish;      // 13
		short SpeedH;	// 14
		short SpeedV;	// 16
		BYTE TipoUsato;		// 18  0=no, 1=scrable, 2 = fish
		BYTE TipoFase;		// 19 status attuale
	};

	struct StrCombine {
		void *pProcedura;
		WORD PrimoItem;
		WORD SecondoItem;
		WORD ItemFinale;
	};

	// structure inside tomb raider about sfx infos
	struct StrZonaSound {
		DWORD  Volume;
		DWORD  FrequenzaHigh;    // <= 32767
		DWORD  CameraAngle;      // (horient?)
		DWORD  FrequenzaLow;     // >6000
		int    IndiceRel;      // (restituito da VetSoundIndices[SfxIndex] )
		DWORD  CameraAngle2;      // (sembra uguale a cameraAngle)
		DWORD  CordX;
		int    CordY;
		DWORD  CordZ;
	};

	// contiene alcuni valori globali di tomb4 che vengono usati spesso
	struct StrGlobAddress {
		StrItemTr4 *pLara;
		StrRoomTr4 *pVetRooms;
		StrItemTr4 *pVetItems;

		int *pTotItemsAtBegin;
		int *pTotItems; // era "AncoraTotItems"
		StrInventoryItems *pInventory;
		StrSlot* pVetSlot;
		int *pSlopeType; // SLOPE_ values
		int *pSlopeX;
		int *pSlopeZ;
		StrBaseHandle BaseHandles;
		StrAnimationTr4 *pVetAnimations;
		StrTexInfoTr4 *VetTexInfo;
		StrStaticSlot *pVetEditObjects;
		StrCollisionLara *pCollisionLara;
		StrMeshTr4 **VetMeshPointer; // tutte le mesh del wad
		StrMeshTr4 **VetMeshLara; // punta alle 15 mesh che formano corpo di lara
		WORD *pFlagsLaraHands;
		WORD *pObjInLaraHandsNow;
		WORD *pObjInLaraHandsNext;
		WORD *pWeaponSelected;
		WORD *pLaraLocationFlags;  // LLF_ values to test with == operator
		short *pVehicleIndex;
		short *pWeaponHolding;
		short *pDashBarValue;
		BYTE *pVetDrip;
		WORD *pPoison1;
		WORD *pPoison2;
		DWORD *pInputExtGameCommands;
		int *pRopeNowIndex;
		BYTE *pVetInputKeyboard;
		StrAIDataTr4 *pVetAIData;
		int *pTotAIData;
		WORD *pInputGameCommands;
		BYTE *pFlagsLara;
		BYTE *pFlagsLara2;
		int *pObjectActive;
		WORD *pFlareLifeTime;
		WORD *pLaraIndex;
		int *pTimerScreen;
		short *pSizeScreenX;
		short *pSizeScreenY;
		short *pRowCharHeight;
		int *pEarthQuake;
		HWND  *pWindowHandle;
		BYTE *pLevelNow;
		WORD *pScriptLevelFlags;
		BYTE *pScriptMainFlags;
		char *pScriptDat;
		BYTE *pTotSecrets;
		short *pAirAvailable;
		WORD *pTotRooms;
		StrAdrCamera Camera;
		StrAdrFlipMap Remap;
		int *pTotFlyBy;
		StrFlyByTr4 *pVetFlyBy;
		int *pTestFlybyInProgress;
		BYTE *pTestLoadOrNewLevel;
		DWORD *pFrameCounter;
		int *pSetting_MusicVolume;
		int *pSetting_SFXVolume;
		int *pSetting_SoundQuality;
		StrItemTr4 **p2CurrentEnemyTarget;
		DWORD *pColorLayer1;
		DWORD *pColorLayer2;
		BYTE *pSpeedLayer1;
		BYTE *pSpeedLayer2;
		WORD *pVetLightningColors;
		WORD *pVetLightningSourceColors;
		BYTE *pVetSavegameItems; // ZonaSave_169_ArmaPistola
		short *pVetAmmos; // costanti MUN_...
		StrCustDatiOggettoMano *pVetCustObjectsHand;
		WORD *pVetRoomOfDestroyedShatter;
		StrMeshInfo **pVetStructOfDestroyedShatter;
		WORD *pTotDestroyedShatters;
		int *pAudioTrackLoop;
		BYTE *pTestAudioTrackLoop;
		BYTE *pTestWorkingOnMoveables;
		float *pStartFog;
		BOOL *pTestDisableFogBulbs;
		BYTE *pSetting_Volumetric;
		StrDatoInventario *pVetStructInventoryItems;
		WORD *pVetFlagsInventoryItems;
		int *pZonaRecord30;
		StrBoxZones *pVetBoxZones;
		StrFish *pVetFish;
		int *pInclinationType;
		int *pInclinationX;
		int *pInclinationZ;
		StrCombine *pVetNewCombine;
		short *pSetCameraHOrient;
		short *pSetCameraVOrient;
		short *pSetCameraDistance;
		WORD *pSetCameraSpeed;
		BOOL *pTestOverPlatform;
		StrZonaSound *pVetSfxSoundInfos;
		bool *pTestLaserSight;
		int *pZoomFactor;  // while there is binocular or lasersight
		bool *pTestGrayScreen; // pause, inventory, load/save, options
		bool *pTestLoading; // loading level in progress
		short *pFadeScreen;
		int *pCDTrackNow;
		int *pTestCdLoop;  // true= loop mode for pCDTrackNow
		short *pTurnHLaraHeadEnd;
		short *pTurnVLaraHeadEnd;
		short *pTurnRLaraHeadEnd;

		short *pTurnHLaraHeadNow;
		short *pTurnVLaraHeadNow;
		short *pTurnRLaraHeadNow;
		WORD *pFlashRed;
		WORD *pFlashGreen;
		WORD *pFlashBlue;
		WORD *pFlashDurate; // it affects also the intensity,
							// value in tick frames 1/30 of seconds, only even numbers
		BYTE *pLevelNext; // new level that is going to be loaded
		DWORD *pInputCommandFlags; // altra variabile con tasti premuti
		DWORD *pFadeCurtain;
		StrMeshTr4 *pVonCroyMeshFreeHand; // right free hand
		StrMeshTr4 *pVonCroyMeskKnifeHand; // right hand with knife
		int TotItemsMax; // tot moveable + new created items
		int *pInventoryRequiredSlotItem; // item that lara requires to engage some moveable: example: crowbar, jeep's key
		int *pInventoryChosenItem; // item selected in inventory
	};

	struct StrEnvPosition {
		WORD Orient;
		DWORD CordX;
		int CordY;
		DWORD CordZ;
	};

	// dati per eventuale breakpoint condizionata

	struct StrHardwareB {
		bool Attivo;
		int m_index;
		void *pOffset;
		int NBytes;
		int TipoThread; // tth_ tipo thread handle
		int NLivello;  // numero livello dove applicarla
		int Valore; // da usare come confronto in condizione
		DWORD NControlli;
		char Descrizione[60];
		int TipoOperazione; //  tpob_
		int CodiceCostante; // OFF_
		HANDLE hThread;
		DWORD RecSizeStruct;
		DWORD VetOffset[MAX_OFFSET_HARD_BREAK];
		DWORD VetCount[MAX_OFFSET_HARD_BREAK];
		int  VetLastValue[MAX_OFFSET_HARD_BREAK];
		int TotOffset;
	};

	struct StrTexParziali {
		WORD  IndiceRange; // indice range
		WORD  IndiceFull; // indice della texture full di cui fa parte questo frammento
		WORD IndiceFrammento;
		WORD  OffX;
		WORD  OffY;
	};

	struct StrBaseParziali {
		WORD TotRecords;
		StrTexParziali VetParziali[4096];
	};

	// informazioni per animazioni di palline colorate sul detector
	// in modalita' radar
	struct StrTargetDetector {
		short Fase;  // FTR_ 0= nascita / 1 = lampeggio fisso / -1 non attivo
		short DifY;  // distanza da floor sotto lara
		WORD  Orient; // orient rispetto a lara nord
		short DifX;   // distanza su cord x in metri da lara
		short DifZ;   // distanza su cordz
		int Distanza3d; // distanza 3d in metri (valore assoluto)
		short VPos;  // 0 = piano di lara, +1 = sopra lara, -1 = sotto lara
		short Incremento; // usato per lampeggio fisso
		short DurataFase; // GlobTomb4.Adr.VetTexInfomentare e azionare prossima fase solo a 0
		short DurataTotale; // click ancora da eseguire con target visibile
		WORD Frame; // numero di sprite mostrato in ultima operazione
	};

	struct StrDetector {
		bool TestMostra;  // se mostrato sullo schermo
		bool TestAttivo; // se impostato in script
		int Distanza; // distanza in metri
		int DistanzaY; // minore di zero se target e' piu' in alto
		WORD OrientLast; // ultimo orientamento impostato (magari diverso per oscillazione)
		WORD OrientRealLast;  // orientamento effettivo di ago
		WORD OrientRealNow;  // orientamento effetivo attuale
		WORD ScalaMetrica; // per ogni segno
		DWORD LastFrame; // dipressione f8
		short IncOscillazione;
		WORD RangeMetri; // mostrarlo quando si e' entro i...metri
		WORD MaxDifVMetri;
		WORD MaxDifHMetri;
		WORD Indice;
		WORD SlotDetector;
		WORD Flags;  // dtf_ flags
		WORD TotIndici;
		WORD VetIndici[200];
		StrTargetDetector VetTargets[200];
	};

	// struttura per qazioni rilevate durante un ciclo di gioco (in modo
	// simile a quanto avviene per flipeffects)
	struct StrScanAction {
		WORD Timer; // valore argomento timer
		WORD ItemIndex;
		WORD Flags; // dati peridentificare in modo univoco questo trigger
					//Byte basso: numero stanza
					//  Byte alto: flags
					//		0x0100 = attivato con heavy
					//		0x0200 = One-shot solo temporaneo
					//      0x0400 = Pulsante one-shot di trigger del flipeffect
					//      0x0800 = Ancora da eseguire
		DWORD OffsetFloorData;
		// distanza da inizio floor data di record
		//						<TRIGGER WHAT=Action>
		WORD PluginId; // 0= trng, or plugin owns this trigger
	};

	struct StrAddEffect {
		WORD Id;
		WORD Type;    // ADD_
		WORD Flags;   // FADD_
		WORD Joint;   // JOINT_
		short DispX;
		short DispY;
		short DispZ;
		WORD DurateEmit;
		WORD DuratePause;
		int  TotExtra;
		WORD VetExtra[MAX_EXTRA_EFFECT];
		WORD Dynamic;
	};

	struct StrBaseEffects {
		int TotEffects;
		short VetID[MAX_ADD_EFFECTS*10];
		StrAddEffect VetEffects[MAX_ADD_EFFECTS];
	};

	struct StrOldTrigger {
		WORD Flags;
		DWORD OffsetFloorData;
	};

	struct StrFMV {
		int SalvaBloccatiFMV;
		DWORD LastFMVSoundObject;
		int LastCdSound;
		int LastCdLoop;
		DWORD LastCdPosizione;
		int IndiceFmvAttivato;
		int IndiceFmvInCorso;
		int IndiceUltimoFMVAttivato; // usato per global trigger
		BYTE VetFmv[MAX_FMV];
		char NomeFmv[256];  // nome fmv corrente da attivare
		BYTE VetFmvEseguiti[MAX_FMV];
		DWORD TempoInizioFmv;
		DWORD TempoFineFmv;
		HINSTANCE Istanza;
		bool BreakEnabled;
		HRESULT HR;
		bool TestFattoFadeOut;
		int OperazioneAltEnter;  // OAE_...
		bool TestIgnoraTutto;
		bool TestFullScreen;
		bool TestFMVInCorso;
		bool TestFinitoFmv;
		bool TestTombSotto;
		bool TestFinitoAltEnv;
		HWND WindowBlack;
		int TotFmv;
	};

	struct StrDatiExtraAnimazioni {
		bool TestPresente;
		BYTE Tot_UV_Rotate; // numero di animation range con uv rotate
		WORD TotaleRangeNG; //numero originale di animation ranges
		WORD VetInfoRangeAnim[40]; // ogni valore contiene info su velocita frame
								   // di ogni record animazione range
		WORD VetFromTex[40];
		WORD VetToTex[40];
		// usati solo per esport in headerng di file tom
		WORD SizeDefault; // 64 o 128
	};

	// record per salvataggio orientamento di animating
	// da salvare e ripristinare da savegame per mantenere
	// le rotazioni effettuate con flipeffects

	struct StrSalvaCords {
		WORD OrientingH;
		WORD OrientingV;
		WORD FlagInvisibile;
		DWORD CordX;
		int   CordY;
		DWORD CordZ;
		WORD  Room;
	};

	struct StrBaseSalvaCords {
		WORD TotSalvati;
		WORD VetIndici[MAX_SALVA_CORD];
		StrSalvaCords VetSalvati[MAX_SALVA_CORD];
	};

	struct StrDatiXRain {
		int  LastRoomCamera;
		float Rain_Float_1;
		float Rain_Float_2;
		float Rain_Float_4;
		float Rain_Float_8;
		float Rain_Float_16;
		float Rain_Float_20480;
		WORD Max_Rain;
		WORD Min_Rain;
		WORD Flags; // FR_ ...
		short SoundSFX;
		int  LastIntensita;
		DWORD SplashRain;
	};

	struct StrDatiXSnow {
		WORD Max_Snow;
		WORD Min_Snow;
		int LastRoomCamera;
		int LastIntensita;
	};

	struct StrExtraInfoRoom {
		BYTE  WaterIntensity; // usato per pioggia e neve
		BYTE  Reserved[7]; // altri 8 byte da usare in futuro
	};

	struct StrExtraLangugage {
		WORD Indice;
		char *pTesto;
	};

	// dati relativi a sezione Options di scrip.dat, valide per tutti i livelli
	struct StrScriptOpzioni {
		WORD MainFlags;   // valori ngfm_...
		WORD DisablePatchMem;  // valori DPM_ ...
		WORD Reserved[80]; // to change when I add new fields to this structure
	};

	struct StrIndiciAssign {
		int IndiceAnimRubberBoat;	// dati per nuovo oggetto RUBBER BOAT
		int IndiceRubberBoat;
		int IndiceAnimMotorBoat;
		int IndiceMotorBoat;
	};

	struct StrScriptLevel {
		WORD LevelFlags; // valori fngl_
		StrIndiciAssign  AssignSlot;
	};

	struct StrRecordPoint {
		int Valore; // usato per #POINT#
		int Operazione; // usato per #POINT#
		DWORD OffsetBreak;
		BYTE Originale; // valore originale
		short Registro; // numero di indice registro oppure -1 se non e' un registro
		bool TestAttiva; // se e' stato messo 0xcc e' attiva
	};

	struct StrRecordDGN {
		void *pIndirizzo;  //
		int  OldValue; // per confronto con precedente scansione
		int CodiceCostante; // se e' una variabile mnemonica qui c'e' OFF_...
		WORD FlagsType;  // (mascherato a byte, word, long o struct)
		DWORD StructOffset;  // offset da inizio struttura
		int  Indice; // indice di vettore (usati solo se pointer)
		WORD MaxIndice;  // (se si  deve stampare la serie di un vettore)
		WORD SizeStruct;  // (se e' un vettore di strutture questa e' la dmensione)
		bool TestPoint;  // se true allora e' una POINT
		StrRecordPoint Point; // dati point
		char Descrizione[40]; // (stringa descrittiva)
	};

	// dati per comandi script LogItem=
	struct StrLogItem {
		WORD Flags; // FLI_...
		short ItemIndex;  // indice da controllare
	};

	struct StrDgxInfoSlot {
		WORD Slot;
		WORD PrimaAnimazione;
		WORD UltimaAnimazione;
	};

	struct StrBaseDiagnostica {
		int TotRecord;
		bool TestPrimaEsecuzione;
		bool TestCaricato;
		bool TestPremutoF7;
		int TotPoints;
		WORD VetSFXMancanti[MAX_SFX_MANCANTI];
		int TotSFXMancanti;
		bool TestErrore;  // se = true non provare piu' a caricare file
		bool TestSospendiBreakCond; // se true ignora modifiche finche questo true
		WORD When;   // FWN_...
		WORD Flags;  // FLAG_...
		DWORD LastTime; // usato per esecuzione ogni secondo
						//usati per point_media e point time
		DWORD Tempo; // usato per POINT_TIME e POINT_START_TIME
		DWORD SommaTempo; // usato per le medie
		int TotCicli;  // numero di cicli scanditi
		WORD FlagsDgx; // DGX_.. cosa mostrare e cosa no
		WORD DgxExtra; // eventuale parametro extra
		StrRecordDGN  VetWatch[MAX_WATCH];
		StrLogItem  LogItem;
		StrDgxInfoSlot  InfoSlot;
		short LivelloExtractSFX; // estrarre sfx di livello
		int TotTiming;
		DWORD LastTiming;
		DWORD VetTiming[MAX_TIMING];  // conserva le ultime differenze di tick frames tra attivazioni trigger
	};

	struct StrDamage {
		DWORD Colore;
		WORD Flags;   // FDM_..
		WORD SecondiMorte;
		short IndiceStringa; // o -1 se non presente
		WORD SecondiRicrescita;
		// fino a qui era valori presi da script, dopo questa riga
		// ci sono valori impostati nel corso della gestione damage
		int DamValue; // da salvare e ripristinare in savegame (moltiplicato * 100)
		int BlinkTime;
		WORD FlagProgresso;  // FPD_..
		WORD Percentuale; // valore eprcentuale da mostrare (a volte zero per lampeggio)
		WORD QuotaRiduzione; // numero da sottrarre a ogni frame di gioco
		WORD QuotaRicrescita; // numero da aggiungere per ripristino barra piena
		WORD QuotaRiduzioneRapida; // di vita, quando barra e' finita
		WORD PercentualeBeep;
	};

	// dati fissi da salvre in savegame per salvare molti dati modificati
	// nel corso del gioco
	// 32 word + 32 dword
	struct StrDatiVariabili {
		WORD  ValoreCold;
		WORD  FlagProgressoCold;
		WORD ValoreDamage;
		WORD FlagProgressoDamage;
		int KeysToStop;
		DWORD StatusNG;  // flags SNG_...

		WORD TestDisableFeatures;  // flags DF_....
		DWORD CounterGame;
		WORD FlagLivelloNow; // valore con i valori attuali di flag livello script
		DWORD ColoreLayer1;
		DWORD ColoreLayer2;
		BYTE SpeedLayer1;
		BYTE SpeedLayer2;
		short CdLoopSecondario;
		WORD LevelNGFlags;
		short CdSingleSecondario;
		DWORD Canale2StartPos;
		short CdLoopMain;
		short CdSingleMain;
		DWORD Canale1StartPos;
		float FloatFogStart;
		BOOL  NonUsato;
		DWORD Unused;
		short IndicePushSpinto;
		WORD ParBarGiri;
		DWORD ParBarFrames;
		WORD TestPopUp;  // se = 1 esiste un'immagine popup visualizzata
		WORD PopUpContatore;	// numero di tick frame di visualizzazione (o 0xffff per infinito)
		WORD PopUpIndiceImageCmd; // indice dell'immagine comando da visualizzare
		BYTE SalvaVolumetric; // salva stato prima di sospensione all fog
		BYTE TestHardFog; // usare questo solo come segnalato di esistnza di campi
						  // successivi e usare in futuro questa tecnica
		BYTE TestMostraDetector;
		BYTE NonUsatoByte;
		short FogEnd;
		BYTE FogColors[4];  // in realta' solo i primi 3 sono usati
		short FogDistanceNow;  // che sarebbe il nuovo fog start
		short FogBulbMaxDistance; // poi creato con calcolo gigantesco
								  //fino blocco che eiste solo se c'e' testhardfog diverso da zero
		DWORD Reserved[100]; // to change when I add new fields
	};

	struct StrJiga {
		int TotAnim;
		bool TestLaraBalla;
		WORD VetAnim[100];
	};

	struct StrRecordEnemyScript {
		WORD  SlotId;
		WORD  FlagsNEF;  // NEF_...
		WORD  Health;
		short  Damage;  // danno arrecato a lara
		WORD  TombFlags;  //TCF_ in campo flags di slot
		short Extra; // word extra per setting particolari
		int  TotDamage; // numero di argomenti extra
		short  VetDamage[6];  // eventuali valori extra damage o segnali particolari
	};

	struct StrBaseEnemyScript {
		int TotEnemy;
		StrRecordEnemyScript VetEnemy[MAX_ENEMY_SCRIPT];
	};

	struct StrAnimScript {
		short AnimIndex;
		WORD  Key1;
		WORD  Key2;
		WORD  Flags;  // FAN_ flags
		WORD  Environment;  // ENV_ costanti
		short DistanceEnv; // distanza per environment
		WORD  Extra;
		int  TotStateId;
		short VetStateId[32];
	};

	struct BaseAnimScript {
		int TotAnimazioni;
		StrAnimScript VetAnimations[MAX_ANIM_SCRIPT];
	};

	struct RecordMirror{
		WORD MirrorRoom;		// 0x00
		WORD HiddenRoom;		// 0x02
		WORD MirrorType;		// 0x04
		int CordMirror;			// 0x06
		int MinCordMirror;      // 0x0A usate solo per
		int MaxCordMirror;      // 0x0E mirror inverso
		int TotAnimating;		// 0x12
		WORD TestAttivo;		// 0x16
		WORD VetAnimMain[256];   // 0x18
		WORD VetAnimMirror[256]; // 0x58
		int VetFixX[256];  // valore da aggiungere a x per fixing
		int VetFixZ[256];  // valore da aggiungere a z per fixing
	};

	struct BaseMirrors {
		WORD TotMirror;
		RecordMirror VetMirror[MAX_MIRRORS];
		WORD MirrorType;
		int  CordMirror;
		int MinCordMirror;
		int MaxCordMirror;
		int IndiceNow;
		RecordMirror *pRecNow;
		DWORD CordX;
		int CordY;
		DWORD CordZ;
		short OrientH;
		short OrientV;
		short OrientR;
	};

	struct StrStaticMIP {
		short Slot; // main slot
		short DistanceB;
		short SlotB;
		short DistanceC;
		short SlotC;
	};

	// structure to host all StaticMIP script command of current level section
	struct StrBaseStaticMIP {
		int TotStaticMIP;
		StrStaticMIP VetStaticMIP[MAX_STATIC_MIP];
		StrStaticMIP *pStaticNow;  // the further pointer to StaticMip command of current static (if the MainSlot is right)
	};

	struct StrInfoAnimDoor {
		short Incremento;
		int CordChiusa;
		int CordAperta;
		WORD FlagsMov;
	};

	struct StrRectPos {
		DWORD MinX;
		DWORD MaxX;
		DWORD MinZ;
		DWORD MaxZ;
	};

	struct StrScriptElevator {
		WORD IndiceElevatore;
		int  FirstFloorY;   // cordy originale di ascensore e primo piano.
		WORD ClickDistance;
		WORD TotFloors;
		WORD Flags;  // EF_... flags
		WORD IndexFirstDoor;
		WORD IndexFirstDoorSecodnary;
		WORD KeyPadIndex;
		WORD ImagePrompt;
		WORD TotDoors;
		StrInfoAnimDoor AnimDoor;
		StrInfoAnimDoor AnimDoorSecondary;
		WORD VetDoors[MAX_ELEVATOR_DOORS];
		WORD VetDoorsSecondary[MAX_ELEVATOR_DOORS];
		WORD TotFrameItems;
		WORD VetFrameItems[MAX_FRAME_ITEMS];
		StrRectPos LimitiBloccoKeypad;
		WORD OrientLaraPerKeyPad;
		WORD Speed;
		StrItemTr4 *pItem;
		int MaxYFloor;
		short MaxRoom;
	};

	// struttura con dati dinamici di ascensore da salvare in savegame
	struct StrElevator {
		int  IncY;  // praticamente velocita', positiva o negativa
		int OrgYTarget; // coordinata y da raggiungere
		BYTE Status;  // EST_ .. in attesa, in movimento, in pausa, in partenza
		BYTE FloorNow; // 0 = primo piano
		BYTE FloorTarget; // a che piano si  sta andando
		int Soffitto;  // zero o 0x800 a secona se collisione sul soffitto o meno
		BYTE NextStatus;  // prossima cosa da fare, usto solo per delay
		BYTE Delay;  // numero di click di attesa per fase delay
		short LastIncy; // escludendo assestamento
		BYTE StoppedStatus; // valore di status nel momento in cui e' stato stoppato
		int FirstFloorY; // coordinata y salvata in savegame
		int VetCordYFrame[30]; // cordy di tutti i frame
		int CordYElevator; // per salvare in savegame cordy attuale
		StrInfoAnimDoor SalvaAnimDoor; // non piu' usata
	};

	struct StrBaseElevator {
		WORD TotElelevators;
		StrScriptElevator VetScriptElevators[MAX_ELEVATORS];
		StrElevator VetAscensori[MAX_ELEVATORS];
		int GapSoffittoY;
	};

	// setting (eventuali) per keypad impostate da comando script keypad=
	struct StrKeyPadScript {
		WORD IndexFirstAnim;
		WORD FrameFirstAnim;
		WORD IndexAfterAnim;
		WORD ClickSound;
	};

	struct StrKeyPad {
		bool TestAttivo;
		int  Fase;  // FKP  valori
		int IndiceTasto;
		int IndiceTastoOld;
		WORD Slot;
		DWORD LastFrameKey;
		DWORD LastFrameExit;
		int CordYAnimazione;
		bool TestAttivaTriggerSwitch;
		int IncYAnimazione;
		DWORD OldTastiBloccati;
		int TipoKeyPad;
		int ValoreInserito;
		int TotInseriti;
		int ValoreAtteso; // solo per switch
		int *pStartMeshTree;
		int IndiceKeypad; // indice di item switch
		StrKeyPadScript ScriptSettings;
		DWORD LaraX;
		DWORD LaraZ;
		char BufOldText[10];
		BYTE VetInseriti[4];
	};

	struct StrAnimObjScript {
		short Slot;
		short ActionType; // AXT_... or  negative value
		StrAnimScript Animation;
	};

	struct BaseAnimObjScript {
		int TotAnimObj;
		StrAnimObjScript VetAnimObj[MAX_ANIM_OBJ_SCRIPT];
	};

	struct StrCheckPoint {
		short Orient;
		WORD Distance;
	};

	struct StrEnvForEnemy {
		bool TestLara; // se = false allora e' nemico
		StrBoxCollisione EnemyBox; // relative collision box
		StrItemTr4 *pOggetto;
		int IndiceOggetto;
		DWORD FirstAnim;
		int TotExtraCheckPoints; // further point to check
		StrCheckPoint VetExtraCheckPoints[16];
	};

	// struttura per gestione di triggergroup con flag TGROUP_SINGLE_SHOT_RESUMED
	struct StrSingleShotResumTG {
		int TotTGResumed; // id dei tg with flag resumed nello script
		WORD VetTGResumed[MAX_TRIGGER_GROUPS];
		int TGEseguiti; // id dei triggergroup eseguiti nell'ultimo ciclo da F118
		WORD VetTGEseguiti[MAX_TRIGGER_GROUPS];
	};

	struct StrRecordParamLgtn {
		short IdParamLgtn;
		short Flags;  // LGTN_
		short IndexSource;
		short IndexTarget;
		DWORD Color;
		short Intensity;
		WORD SoundEffect;
		short Size;
		short ParticleDurate;
		short Arg1;
		short Arg3;
		short IntervalMask;
		WORD Dynamic;
	};

	struct StrBaseLightning {
		int TotParamLgtn;
		StrRecordParamLgtn VetRecordLgtn[MAX_PARAM_LIGHTNING];
		short VetId[MAX_PARAM_LIGHTNING*10];
	};

	struct StrBaseImgMonoScreen {
		bool TestBackGround; // se c'era in scropt comando "BackGround="
		bool TestImageMonoscreen;  // true= custom image to free
		int NumeroImage;  // numero, non ID
		int Cd_Track;   // -1 = no audio track
		WORD Flags;   // BKGDF_ flags
		short Parameter;
		bool TestLoop;
		bool TestTrasparente;
	};

	struct StrBaseImgBackGround {
		bool TestEnabled;
		bool TestAllocatedImage;
		int ImageNumber;
		WORD Flags; // BKGDF_ flags
		short Parameter;
		bool TestTransparent;
	};

	// used for compute the origin of system strings of tomb4
	struct StrOffsetRanges {
		DWORD Start;
		DWORD End;
	};

	struct StrParamWText {
		short IdParam;
		WORD Flags;
		WORD Durate;
		WORD ExtraParam;
		short WindowsFontId;
		RECT MyRect;
		WORD Dynamic;
	};

	struct StrBaseParamWText {
		int TotParamWText;
		StrParamWText VetParamWText[MAX_PARAM_WTEXT];
		short VetIds[MAX_PARAM_WTEXT*10];
	};

	struct StrRecNewError {
		char *pMex;
		int FrameTicks;
	};

	struct StrBaseDgxErrors {
		int TotOld;
		char *pVetMexOld[MAX_DGX_OLD_ERRORS];
		int TotNew;
		StrRecNewError VetMexNew[MAX_DGX_NEW_ERRORS];
	};

	struct StrDisablePushAway {
		int TotDisable;
		short VetAnimNumber[MAX_ANIM_SCRIPT]; // number of animation where disable push away for lara
	};

	struct StrMyRect {
		short Id;
		short OrgX;
		short OrgY;
		WORD SizeX;
		WORD SizeY;
		short ForeColor;
		short BackColor;
		WORD Dynamic;
	};

	struct StrBaseMyRect {
		int TotMyRect;
		StrMyRect VetMyRect[MAX_MY_RECT];
		short VetId[MAX_MY_RECT*10];
	};

	struct StrMyInputBox {
		short IdInputBox;
		short IdImage;
		short IdWFont;
		WORD MaxChars;
		short SfxSound;
		WORD RIB_Flags; // FIB_ flags, in the script
		int ExtraParam;
	};

	struct StrExtraCode {
		BYTE  VetScanCodes[3];
		BYTE  ValAscii;
		WORD TotScanCodes;
	};

	struct StrBaseInputBox {
		int TotInputBox;
		StrMyInputBox VetInputBox[MAX_INPUT_BOX];
		StrMyInputBox *pInputBoxNow; // pointer to current Input Box
		int TotExtraCodes;
		StrExtraCode VetExtraCodes[MAX_EXTRA_SCAN_CODES];
		short VetId[MAX_INPUT_BOX*10];
	};

	struct StrTiming {
		char *pLastMex;
		DWORD LastTime;
		DWORD NCicli;
		DWORD ValoreMedio;
	};

	struct StrGlobalBinoculars {
		int LastYSextant;
		int LastXCompass;
		int MaxOscilla;
		int LastIncX;
		int MaxOscillaY;
		int LastIncY;
		int ValoreZoomProgresso; // viene usato sempre in codice tomb4
		float ZoomInc;
		float ZoomInc2;
		float ZoomMax;
		DWORD OldTastiPremuti;
	};

	struct SalvaSliderInput {
		bool TestUsed;
		DWORD Parameters[8];
	};

	struct StrAnchoredBoat {
		WORD Slot;  // slot about posizione of frozen boat
		StrEnvPosition OldPosition;  // used with OCB_BOAT_ANCHORED ocb
	};

	struct StrMiniItemData {
		DWORD MeshVisibilityMask; // 08
		WORD StateIdCurrent;	    // 0E
		WORD StateIdNext;			// 10
		WORD StateIdAI;				// 12
		WORD AnimationNow;		    // 14
		WORD FrameNow;			    // 16
		short Room;					// 18
		short SpeedH;			// 1E
		short SpeedV;			// 20
		short Health;				// 22
		BYTE IdSprite1;				// 2e
		BYTE IdSprite2;				// 2f
		WORD Trasparency;			// 30
		DWORD  CordX;					// 40
		int  CordY;					// 44
		DWORD  CordZ;					// 48
		short OrientationV;  // 4c
		short OrientationH;  // 4e
		short OrientationT;		// 50
		DWORD FlagsMain;		// 15ea
		DWORD FlagsSwapMesh;	// 15ee
	};

	struct StrSalvaDatiLara {
		StrMiniItemData Lara;
		int VetMeshLaraOffset[15];  // differenza tra indirizzo prima mesh di lara e valori impostati nelle varie mesh di lara
		int InventoryItemIndex; // item currently selected
		BYTE pLevelNow;
		BYTE VetDrip[16];  // status gocce lara
		WORD FlagsLaraHands;
		WORD ObjInLaraHandsNow;
		WORD ObjInLaraHandsNext;
		WORD WeaponSelected;
		WORD LaraLocationFlags;
		short VehicleIndex;
		short WeaponHolding;
		WORD Poison1;
		WORD Poison2;
		BYTE FlagsLara;
		BYTE FlagsLara2;
		int ZonaSave_9d_CordYDaPeloAcqua;
		int ObjectActiveIndex;
		WORD FlareLifeTime;
		int TimerScreen;
		int EarthQuake;
		short AirAvailable;
		int TestFlybyInProgress;
		WORD VetBloccoOrient[14];
		int Reserved[500]; // per futuri sviluppi
						   // aggiungere dati per rotazione testa e busto
	};

	// recording
	struct StrRecording {
		WORD Status;   // RECF_...
		WORD Version;  // first is 100 (1.00)
		StrSalvaDatiLara DatiLara;
		int IndexFrame; // for playing
		int TotFrames;
		DWORD VetFrames[MAX_DEMO_FRAMES];
	};

	// data for fake managemnt of updateinput (directinput)
	struct StrMyDirectInput {
		DWORD LastCheckTime; // last ms when perfromed the check
		DWORD LastCheckFlags; // keyboard  input value read at least check
	};

	// struttura per demo
	struct StrDemo {
		WORD Flags; // DEMF_...
		short Parameter;
		short StringInfoTextIndex;
		short StringDemoLegendIndex;
		short WaitingTime;
		short LastIdPlayed; // or -1 se no demo yet played
		int TotDemoIDs;
		int SalvaSfxVolume; // per title
		int SalvaMusicVolume; // per title
		StrScriptOrganizer *pOrganizer;  // se c'e'un organizer linked with this demo (oppure NULL)
		DWORD LastInputTime; // in framecounts to check countdown
		WORD VetDemoIDs[MAX_DEMO_IDS];
		BYTE VetDemoPlayed[MAX_DEMO_IDS]; // only for title demo
		bool TestLoadAndPlay;  // impostato prima di caricare un livello (da title) dove eseguire subito uno o piu' demo
		bool TestDemoInProgress; // when a demo is in progress because launched from a Demo script command
		bool TestTornaATitle; // alla fine di un demo lanciato da title si ritorno a title
		DWORD CtrlSign; // when already loaded 0x615274F1 (only for title)
	};

	struct StrSaveActorSlot {
		WORD Slot;
		void *pOriginalCtrl;
		int ItemIndex;
	};

	struct StrBaseSaveActors {
		int TotActors;
		StrSaveActorSlot VetActors[MAX_ACTORS];
	};

	struct StrCutsceneCamera {
		bool TestAllocata; // catturata una fixed camera (poi si dovra' ripristinarla)
		bool TestAttiva; // attualmente si sta usando cutscene camera
		bool TestFreeze; // sospesa esecxuzione
		WORD Flags; // FCT_...
		DWORD FreezeEndFrame; // momento di fine freeze
		int IndexCamera; // indice di camera usata per cutscene
		int TargetIndex; // indice di target attuale
		StrCameraTr4 Original; // posizione originale di fixed camera (da ripristinare)
		StrCameraTr4 *pCamera; // puntatore a camera usata come cutscene camera
		int AngleViews;  // posizione rispetto a target (stessi valori di F381/382/383 triggers)
		int Distance; // distanza attuale da target
		int DistanceInc; // incremento per modificare distanza
		DWORD DistanceEndFrame; // se c'e' effetto zoom a tempo questo ci dice quando sara' terminato l'effetto
		int Height; // differenza Y rispetto a punto piu' alto di target
		int HeightInc; // valore da aggiungere ad ogni frame per effetto di movimento su /giu
		DWORD HeightEndFrame; // quando sara'finito l'effetto di movimento up/down in demo frames
		int Rotate;  // new degree to add to have a rotation around the target
		int RotateInc;  // change of Rotate increment
		DWORD RotateEndFrame;

		DWORD LastPerformedFrame; // to avoid double performing in same frame number
		StrCameraTr4 CameraNow; // used only to save in savegaem position of cutscene camera and then restore it
		BYTE Reserved[41];
	};

	struct StrTextActors {
		WORD Colore;
		WORD Posizione;
	};

	struct StrBaseCutscene {
		bool TestDemoIntroDone; //gia' eseguita prima esecuzione di cutscene intro
		StrBaseSaveActors BaseSaveActors;
		StrCutsceneCamera BaseCamera;
		int LeadingActorIndex;
		StrTextActors TextLeading;
		int ExtraActorIndex;
		StrTextActors TextExtra;
		StrTextActors TextLara;
		int TotBasicCollision;
		short VetBasicCollisionIndices[MAX_BASIC_COLLISIONS]; // indices of moveable whom add basic collision
	};

	struct StrSalvaGlobFloor {
		int InsideCondition;
		int InsideDummyTrigger;
		DWORD FloorDataNow;
		int TipoInclinatura;
		int InclinaturaX;
		int InclinaturaZ;
		int Reserved[100]; // to change when I add fields to the structure
	};

	struct StrSwapAnim {
		short Id;
		WORD FirstSourceAnim;
		WORD FirstTargetAnim;
		short NumberOfAim;
		WORD Dynamic;
	};

	struct StrBaseSwapAnim {
		int TotSwapAnim;
		StrSwapAnim VetSwapAnim[MAX_SWAP_ANIM];
		short VetId[MAX_SWAP_ANIM*10];
	};

	struct StrMemSwapAnim {
		short IdParamSwap;
		WORD Slot;
	};

	struct StrBaseMemSwapAnim {
		int TotMemSwap;
		StrMemSwapAnim VetMemSwapAnim[MAX_MEM_SWAP_ANIM];
	};

	struct StrSpeechActor {
		short IdSpeech;
		WORD Dynamic; // if different by 0 it has been allocated dynamically and this number is the id of plugin
		WORD Flags;
		WORD Parameter;
		short FrameRate;
		WORD SpeechSlot;
		WORD HeadSlotMesh;
		WORD FirstSpeechMesh;
		WORD TotSpeechMesh;
		int TotCommands;
		WORD VetCommands[MAX_SPEECH_COMMANDS];
	};

	// variabili globali per mantenenere effetto speech
	struct StrPlaySpeech {
		bool TestAttivo;
		WORD Flags;  // SPCF_ flags
		int TotSpeech;   // numero di mesh usate per apertura bocca
		int ItemIndex;
		int IndexMeshActorHead;
		int IndexFirstMeshSpeech;  // slot dove sono contenute le facce
		int IndexLastString; // se 0 vuol dire che non c'e' alcuna stringa
		StrTextActors TextSettings;
		WORD SlotActor;
		StrSpeechActor *pParam;
		WORD IndexCommandNow;
		DWORD LastFramePerformed; // to avoid to repeat performing with same frame
		bool TestAbs;  // se mesh in SpeechIndexNow e' di tipo assoluto (comando MESH o comando SEQUENCE) = true

		int IndiceSecondarioSpeech; // da 0 incrementato di uno dopo ogni fase
		int IndiceSecondarioRotateH; // da 0 a 1 tipo fase
		int IndiceSecondarioRotateV;  // da 0 a 1 tipo fase: muovi tieni fermo in quella posizione
		int FrameRateSpeech;  // impostato da utente o uguale a framerate standard

		bool TestLara;
		bool TestPause;

		DWORD RemovedMeshAdr; // mesh adr presente per testa prima della modifica (da ripristinare)

		int SpeechIndexNow;    // indice mesh impostata come testa attualmente
		int SpeechIndexInc;
		int SpeechTotSequence; // numero di diverse teste da cambiare nel corso della sequenza
		int SpeechTotSyll; // totale syllable, movimento da apri e chiudi o viceversa
		DWORD FrameEndSpeech; // frame when complete current speech command

		int  OrientHTurnNow;
		int	 OrientHTurnInc;
		int  OrientHTurnEnd;
		int OrientHLastCommand;
		int OrientHTimes;
		DWORD FrameEndHTurn;  // frame when complete current horizontal turn head (shake)

		int  OrientVTurnNow;
		int  OrientVTurnInc;
		int OrientVTurnEnd;
		int OrientVLastCommand;
		int OrientVTimes;
		DWORD FrameEndVTurn;  // frame when complete current vertical turn head (nod)
		DWORD FrameEndLoop; // continuare ad eseguire finche' non si raggiungono i frame finali
	};

	struct StrBaseSpeechActor {
		int TotSpeechActor;
		StrSpeechActor VetSpeechActor[MAX_SPEECH_PARAM];
		short VetId[MAX_SPEECH_PARAM*10];
		StrPlaySpeech VetPlay[MAX_ACTOR_SPEECHING];
	};

	struct StrFlipMesh {
		WORD Slot;
		WORD Mesh;
	};

	struct StrBaseFlipMesh {
		int TotFlipMesh;
		StrFlipMesh VetFlipMesh[MAX_FLIP_MESH];
	};

	// to store new items created in last cycle
	struct StrCreatedItems {
		int TotNewItems;
		short VetNewItems[MAX_NEW_ITEMS];
	};

	struct StrPluginNames {
		int PluginId;
		char Nome[80];
		DWORD TotUsato;
	};

	struct StrTablePluginIdFloor {
		int TotTable;
		BYTE VetTable[0x10000];
	};

	// fille with data from Plugin= script commands
	struct StrRecPluginScript {
		WORD PluginId;
		char Name[80];
		int MainPluginSettings;  // MPS_.. flags
		short TotDisable;
		WORD VetDisable[256];
	};

	struct StrTableScriptPlugin {
		int TotPlugins;
		StrRecPluginScript VetPlugins[MAX_PLUGINS_NGLE];
	};

	struct StrAdrMemory {
		union {
			BYTE *pByte;
			short *pShort;
			int *pLong;
		};
		char TipoSize; // B  S L
		char *pDescrizione;
	};

	struct StrCollisionLast {
		int ItemIndex; // returned by IsCollidingWithSomeItem() function: index of moveable with whome there is collision or -1 if missing
		int StaticIndex; //  returned by IsCollidingWithSomeItem() function: index of static item with whome there is collision or -1 if missing
		int StaticIndexRoom; //  room of above static index
		StrAbsBoxCollision BoxItem;  // abs collision box of primary item
		StrAbsBoxCollision BoxSecondary; // abs collision box of secondary item (or static)
	};

	// structure for miscellanous, different global variable
	struct StrGlobMisc {
		StrCollisionLast CollisionLast;
		int TotMaxAIRecords;
		int TotOldAIRecords;
		int TotItemOlds; // original number of moveables loaded from tr4 file
		int TotAsmTtngPatches; // number of numeric trng patches
	};

	// global structure with all data for tomb4 and trng

	struct StrGlobaliTomb4 {
		StrBaseRemapMemory BaseRemap; // remapped memory zones in tomb4
		DWORD FlagsLevel;   // valore FL_...
		StrPrefTomb MyPrefTomb;
		StrBaseFog BaseFog;
		StrCordDetectors BaseCordDetector;
		StrBoatSinking BoatSinking;
		StrBaseShowMeshes BaseShowMesh;
		StrSospendiLog BaseSospendiLog;
		StrBaseMissing BaseMissing;
		WORD *pIndiceFirstAnimBike;
		StrVetItemCollision BaseCollItem; // per collisione con veicoli
		StrBaseScaleItem BaseScaleParam;
		StrBasevehicles BaseVeicoli;
		StrBaseRollBoat BaseRollBoats;
		StrLaraHp BaseOldHpLara;
		StrRobaKayak BaseKayak;
		bool TestFmvTitlePerformed;
		StrBaseShowSprite BaseShowSprites;
		StrBaseParamTriangles BaseTriangles;
		StrBaseQuads BaseQuads;
		StrBaseCircle BaseCircles;
		StrScriptLaraStartPos BaseLaraPosScript;
		bool TestExtraKayak;
		StrBaseAssignSlot BaseAssignSlot;
		BYTE DatiExtraKayak[0x30];
		DWORD SlowMotionDelay;
		bool TestFixLaraMovPos;
		bool TestDummyFalse; // conditional frag trigger
		bool TestDummyBlockForward;
		short OrientFixLaraMovPos;
		WORD VetSalvaFlagItems[120];
		int TotCombinabili;
		DWORD DummyX;
		int DummyY;
		DWORD DummyZ;
		short HealthLaraOld;
		WORD VetCombinabili[120];
		StrGlobFish GlobFish;
		DWORD LastTempoF12;
		bool TestObjectIsNotLara; // usato in TestTriggers per attiva con oggetti trigger normale
		StrBaseFloodRooms BaseFloodRooms;
		StrBaseFreeze BaseFreeze;
		WORD  HangForbidden;  // 0 se e' permesso, altrimnti bit NO_HANG_....
		WORD HangCounter; // se 0 azzera a inizio ciclo, altrimenti decremnta
		int DebugModeCounter; // se > 0 mostra debug
		int TotBigNumbers;
		WORD VetBigNumbers[256];
		DWORD StartTimeHideDiagnostic;
		StrBaseStandBy BaseStandBy;
		StrSavegameInfos BaseSaveGameInfos;
		StrRecordFlip VetScanFlipEffects[64];
		StrBaseVarAll *pBaseVariableTRNG;
		StrBaseEventiNow BaseEventiNow;
		WORD  TotItemNoCollisions;
		short VetItemNoCollisions[MAX_COLL_DISABLED];
		StrSuoni Suoni;
		bool TestFogRange; // c'era un comando fogrange in lviello
		bool TestSetup; // tomb4' -setup
		StrBaseWindowsFonts BaseFonts;
		short VetRemapRooms[MAX_ROOMS];
		short LevelFarView; // valore preso da script
		short WorldFarView; // valore da script
		StrVetDiari BaseDiari;
		bool TestSoftFullScreen;
		StrBaseSwitch BaseSwitch;
		ANIMATIONINFO OldInfoAnimazione;
		bool TestCambiataAnim;
		StrPanelloSavegame *pBasePanello;
		StrBaseNG_Hub BaseHub_NG;
		StrSalvaSettings DefSettings;
		bool TestHubLara;
		bool TestHubLevel;
		bool TestAsSavegame; // se savegame o minihub
		StrShowImage BaseImages;
		bool TestFreezeAll;
		StrBasePrintText BaseParamPrint;
		bool TestFirstTime;
		StrBaseTestPosition BaseTestPosition;
		StrBaseScriptImages *pBaseScriptImages;
		StrBaseSetCamera BaseSetCamera;
		StrBasePreload BasePreloadImages;
		StrVersionHeader VersioneProject;
		StrCheatNG CheatNG;
		bool TestSetCamera;
		bool TestDisableCombatCamera;
		int IndiceSetCamera;
		StrVersionHeader BaseVersione;
		StrVersionHeader VersioneTr4;
		StrVersionHeader VersioneSavegame;
		StrMiniShot ScreenShot;
		StrAudioSospeso AudioSospeso;
		short TriggerGroupInProgress;  // usato per triggergroup lanciati da Animation
		StrBaseTriggerGroups *pBaseTriggerGroups;
		short ScrollingEndIndex;  // indice di stringa ng (senza 0x8000) appena terminata
		short ScrollingLastIndex; // indice di ng string con ultima riga visibile
		StrBaseItemGroup BaseItemGroup;
		StrBaseColoraItem BaseColoraItem;
		short TestPosLastID;  // -1 o indice di ultimo testposition di script usato
		StrItemTr4 *TestPosLastItem; // item detected in ultima TestLaraPosition
		short TestPosLastIndex; // idice di item
		short TestPosOrientIdeal; // orientamento effetivo uato con test position ok
		DWORD TestPosXIdeal;	// usati solo con TPOS_ROUND_HORIENT
		DWORD TestPosZIdeal;	// ....
		bool TestFeetInQuickSand;
		StrAdjustAnim BaseAdjustAnim;
		char WindowNome[256];
		DWORD StartFromGame; // da inizio livello o da carica savegame in tick
		StrAdaptiveFarView BaseAdaptiveFar;
		StrPtrBars VetBarDefault[8];
		StrBaseTimerOggetti BaseTimerOggetti;
		StrBaseMove BaseMoveItem;
		int TextCordXCarattere2;
		StrParBar ParallelBar;
		int TextCordYRiga2;
		StrBaseCollisione BaseCollisione;
		StrInfoChar VetFontInfos[256];
		float FontRapportoX;	// usato con flag FT_USE_FLOAT
		float FontRapportoY;
		float FontRemapLittleX;	// impostate a inizio print string
		float FontRemapLittleY; // per avere caratteri sempre ugualmente piccoli
		StrBaseTurbo BaseTurbo;
		StrBaseRotate BaseRotateItem;
		StrIndiciFont VetFontIndici[256];
		BYTE VetFontGraphics[256];
		bool TestFontNew;
		StrBaseSalvaStatic BaseSalvaStatic;
		StrBaseFPS BaseFPS;
		StrFontBaseSetting BaseFontBinary;
		StrBasePushables BasePushables;
		StrBaseColorRGB BaseColoriRGB;
		StrCercaStatic VetRemapStatics[6000+1];
		int TotScanFlipEffects;
		StrBaseImportFile BaseImportedFiles;
		StrEnemiesNotAimable BaseEnemiesNotAimable;
		WORD FlagsRoom;
		StrSFXSuonati BaseSfxPlayed;

		DWORD FlagsKeysOld;
		bool TestShootingInProgress;
		BYTE *pMemoriaTexture;
		int LastVerticalSpeed;
		StrTempRoomFlags TempRoomFlags;
		StrBassHandles BaseBassHandles;
		int TotScanActions;
		StrBaseDeadAnim BaseDeadAnim;
		StrSoundSettings SoundSettings;
		bool TestSecondoCrash;
		StrFlipMapRooms FlipMapRooms;
		StrBaseMovAdvance BaseMoveAdvance;
		StrBaseFlipSwap BaseMeshSwap;
		BaseNewObjects BaseIndiciNew;
		StrAnimDiag BaseDiagnosiAnim;
		StrAnimDiag BaseDiagnosiAnimSlot;
		StrBaseCustomize *pBaseCustomize;
		StrBaseCustomize *pBaseCustomizeDefault;
		BaseScriptOrganizer *pBaseOrganizer;
		StrItemTr4 *pTarget;
		WORD TestDisableFeatures;  // flags DF_...
		WORD OldDFPerCamera;  // flags DF_
		DWORD StatusNG;  // flags SNG_...
		StrBaseGlobalTriggers *pBaseGlobalTriggers;


		int TestNoDamageRollingBallIndex; // disattiva danni a lara con rolling ball
										  // di valore indice
		StrBaseSalvaCollisioni  BaseSalvaCollisioni;
		StrBaseSalvaCollisioni  BaseSalvaOldCollisioni;
		bool TestDiagnosticaNow;  // attivato quando in watch.txt c'e'
								  // when = ON_FLAG_ATTIVO
		void *pAdrDiagnostica; // punta a memoria da controllare
							   // quando tipo e'
		int OperazioneNext;  // ON_...
		int OperazioneNext2;

		StrWideScreen BaseWideScreen;
		int OperazioneArg; // argomento per operazione next
		int OperazioneArg2; // usata per OperazioneNext2
		int OperazioneCount; // numero di tick prima di eseguire operazione
		StrBaseRemapTailInfo BaseRemapTail;
		StrBaseAnimTr4 BaseAnimTr4;
		StrBaseScriptEnvCondition  *pBaseEnvConditions;
		WORD TotPedane;
		StrBaseTexSequence BaseTexSequence;
		StrItemTr4 *VetPlatforms[1024];
		StrBaseEquipItem BaseEquipItem;
		StrGlobAddress *pAdr;
		WORD ClimbFlags;
		StrEnvPosition EnvPosition;
		StrHardwareB HardwareB;
		StrBaseParziali BaseTexParziali;
		StrDetector BaseDetector;
		int TotSizeDemoData;  // numero di suoni solo se tabella estesa
		StrScanAction VetScanActions[64];
		StrBaseEffects *pBaseEffects;
		int VetInventory[128];  // slot di item inventario
		StrOldTrigger VetOldFlipEffects[MAX_OLD_FLIPEFFECT];
		int TotOldFlipEffects;
		StrOldTrigger VetOldActions[MAX_OLD_ACTIONS];
		int TotOldActions;
		StrFMV BaseFMV;
		HMODULE ModuloDll;
		short ScreenSizeX;  // dimensioni
		short ScreenSizeY; // di modo video
		StrOldTrigger VetOldCondizioni[MAX_OLD_CONDITIONS];
		int TotOldConditions;
		bool TestConditionFound; //basta che venga trovata una condizone nel ciclo game
		DWORD SaveTriggerButtons;  // per trigger condizione con extra buttons
		short ItemIndexCurrent;   // item che ha eseguito trigger attuale heavy
		short ItemIndexEnabledTrigger;  // ultimo item che ha eseguito` un trigger
		short ItemIndexLastMoved;  // ultimo item mosso
		short ItemIndexTgroup; // indice da usare per trigge group oppure -1
		short ItemIndexAnimCommand; // indice di item che ha eseguito un animcomamnd
		short IndiceItemCondizione; // item trovato in una condizione env positiva
									// on una collision globale
		short ItemIndexSelected; // indice stabilito con un trigger action
		short ItemIndexUsedByLara; // indice di oggetto con cui lara sta interagendo
		short CurrentSlotIndex; // usato per accedere a memoria slot
		short CurrentAnimationIndex; // usato per memoria di record animazione
		short CurrentInventoryIndex; // usato per memoria record inventario
		StrExtractNG HeaderNG_Savegame;
		StrExtractNG HeaderNG_Language;
		StrExtractNG HeaderNG_Script;
		WORD *pBaseFloorTriggerNow;
		bool TestBloccaCritical;
		int SalvaTestHeavy;
		bool TestSavegameConHeaderNG;
		short VetRemapObjects[6000];        // index=ngle index to get the tomb4 item
		short VetRemapInverseObjects[4096]; // index=tomb4 to get the ngle item
		bool TestTr4ConHeaderNG;
		StrDatiExtraAnimazioni TexAnimate;

		DWORD LastGameCommandTime;

		WORD *pVetSalvaSizeMesh;
		WORD TotDisabledMirrors;
		WORD VetDisabledMirrors[MAX_MIRRORS]; //numero stanza hidden
		char MexExtFMV[10];
		char LastTombMexage[1024];

		int LastTimerTrigger;
		StrBaseSalvaCords BaseSalvaCoordinate;
		WORD TotProgressiveActions;
		StrProgressiveAction VetProgressiveActions[MAX_ACTIONS];
		char SavegameLastName[256];
		int SavegameLastNumber;
		int KeysToSend;	//usano riferimenti CMD_..
		int KeysToStop;
		int KeysToStopBackup;  // valore precedente, usato per crossfade image

		bool TestTakeAwayWeapons;
		bool TestChangeTransparencyLara;
		DWORD TransparencyLaraIntensity;
		int KeySingleToSend; // usa riferimenti cmd_
		int KeysStopped; // valori che l'utente ha premuto ma sono stati bloccati
		BYTE VetKeysToStop[256]; // status di tasti singoli premuti ma bloccati
								 // usato solo se keypad e' attivo

		bool TestNoUpdate; // se true impedisce ogni aggiornamento della superfice

		StrDatiXRain DatiRain;
		StrDatiXSnow DatiSnow;

		WORD TotExtraInfoRoom; // numero di stanze effettivamente presenti
		StrExtraInfoRoom VetExtraInfoRoom[0x400];
		int TotExtraStrings;
		StrExtraLangugage VetExtraStrings[0x400];
		char LinguaNow[30];  // conterra' "italian" o "english" ecc.
		StrScriptOpzioni ScriptOptions;
		StrScriptLevel *pScriptLevelNow;

		WORD FlagsLevelTr4;   // FLT_
		WORD Flags2LevelTr4;  // FLT2_
		StrPrintString PrintString;

		StrBaseDiagnostica *pDiagnostica;
		StrDamage DamageRoom;
		StrDamage DamageColdWater;
		StrDatiVariabili *pDatiVariabili; //level o lara
		StrDatiVariabili *pDatiVarLara; // solo lara
		StrJiga DatiJiga;
		StrBaseEnemyScript BaseEnemys;
		BaseAnimScript *pBaseAnimations;
		BaseMirrors BaseMirror;
		StrBaseStaticMIP BaseStaticMIP;
		StrBaseElevator BaseElevator;
		WORD Settings; // flag SET... di comando script Settings=
		StrKeyPad BaseKeyPad;

		bool TestDebuggerInProgress;

		short *pVehicleIndex;
		DWORD CordX;
		char *pMascheraSavegame;
		int  CordY;
		bool TestSuspendObjectShowing;
		WORD SlotSwitchKeyPad;
		DWORD CordZ;
		StrSlot *pSlotDefaultSprite;
		BaseAnimObjScript BaseAnimObj;
		StrEnvForEnemy BaseEnvEnemy; // extra check points when the env is for enemy
		StrSingleShotResumTG BaseTG_SingleShotResumed;
		StrBaseLightning BaseParamLightning;
		StrBaseImgMonoScreen BaseImgMonoScreen;
		StrBaseImgBackGround BaseImgLoadingLevel;
		StrBaseImgBackGround BaseImgTitle;
		StrBaseImgBackGround BaseImgBinocular;
		StrBaseImgBackGround BaseImgLaserSight;
		COLORREF VetTextColors[9];  // colors used for print string with windowsfont (index to FC_ color constants)
		short  ColorWhiteStep;  // signed incrfement to change color FC_BIANCO_MOD (1), from white and black slowly
		short  ColorGradientNow; // from 0 to 255 to use for any gradient of pulsing white
		StrOffsetRanges VetStringOffsets[POFF_COUNTER]; // ranges of origin code for system strings
		int TotStringOffset;  // number of ranges of above vector
		StrBaseParamWText BaseParamWText;
		StrBaseDgxErrors BaseDgxErrors;
		int TestStopNotifyThread;  // for sound audio track
		bool TestOldLaserSight; // in previous cycle it was enabled
		bool TestOldBinoculars;	 // in previous cycle it was enabled
		bool TestFirstLoadTitle; // true = showing load.bmp from boot strap game, otherwise
								 // coming back to title from some level
		bool TestWindowedModeRegister; // se nel registro era imposta modo windowed (se false=exlcusive full screen)
		StrDisablePushAway BaseDisablePushAway; // anim about when disable push away animation
		DWORD BackAdrOutputPolyList;  // to know from what zone has been called the outputpolylist
		StrBaseMyRect BaseParamMyRects;
		StrBaseInputBox BaseInputBoxes;
		bool TestStartDiary;  // required to show diary (waiting to be in main initpolylist()/outputpolylist() cycle)
		int DiaryIDToStart;   // id of diary to show
		int DiaryPage;       // first page to show for diary
		DWORD LastAdrFloorData; // saved at begin of testtrigger, usato da catturaflipeffect
		GAME_VECTOR TargetBinoculars; // last point find before obstacle

		StrTiming Timing;  // used for performance analyses about timing
		int EmergencySettings; // ES_...
		bool TestForceSetup;
		bool TestOverlapImage; // full screen image is currently drawn on screen
		StrGlobalBinoculars GlobBinoculars;
		SalvaSliderInput SliderMusic; // last input values , to fix problem in title custom image
		SalvaSliderInput SliderSfx;
		StrAnchoredBoat BoatAnchored;
		DWORD LastTimeBinoculars; // to stop inventory when exiting from binoculars
		char *pMexLastTGCaller; // text about who called last time triggergroup() procedure (for diagnostic)
		StrItemTr4 *pItemAdrToIgnoreLOF;  // Adr structure to ignore in the objectonlos2() procedure (or NULL=0)
		StrRecording *pBaseDemo;  // to record or play demo
		StrMyDirectInput BaseDirectInputMine; // to temporize fake direct input outside of common game
		StrDemo *pDemoTitle;
		StrDemo *pDemoLevel;
		StrDemo *pDemoNow;  // points to demolevel or demotitle or NULL if missing
		int DemoNumberLoaded; // current number of demo#.pak loaded in structure recording
		int DemoOnDisk;   // number of demo file in data folder
		WORD DemoOnDiskArray[1000]; // indices of demo#.pak files

		StrBaseCutscene *pBaseCutscene;  // data about cutscene and demos
		StrSalvaGlobFloor BaseSalvaFloor; // to save/restore some global variables affected from getheight/getceiling
		StrBaseSwapAnim *pBaseSwapAnim;
		StrBaseMemSwapAnim *pBaseMemSwapAnim; // to save/reload from savegame the last swapping to restore situation
		StrBaseSpeechActor *pBaseSpeechActor; // to store PARAM_ACTOR_SPEECH
		bool TestEditingDemo; // if true demo is recording now or is playing after F10 key
		bool TestDisableDemoOrganizer; // if true while is playing or recording (in editing mode) the organizer will be ignore
		StrBaseFlipMesh BaseFlipMesh;
		StrCreatedItems BaseCreatedItems;
		int TotPluginNgle;
		StrPluginNames *pVetPluginNgle; // qui edevo cambiare definziione dimensione
		StrTablePluginIdFloor *pPluginFloorTable; // to discover the owner for each trigger in floordata
		StrTableScriptPlugin *pPluginScriptTable; // to discover the id of script commands (triggergroup, customize an parameters)

		StrAdrMemory *pVetMemorySavegame; // records about savegame memory  (ngle)
		StrAdrMemory *pVetItemMemory;     // records about item memory (ngle)
		StrAdrMemory *pVetCodeMemory;    // records about code memory (ngle)
		StrAdrMemory *pVetSlotMemory;      // records about slot memory (ngle)
		StrAdrMemory *pVetMemoryAnimation;  // records about animation memory (ngle)
		StrAdrMemory *pVetMemoryInventory;  // record about inventory memory (ngle)

		int *pVetMeshSwapSlot;
		int *pVetStandardSwapMesh;
		int *pVetSlotMeshMoveables;
		int TestOrizzonteVisibile;
		bool TestAlignmentInProgress;  // "true" there is a serie of calling to MoveLaraPosition()
									   // to align in front of ObjectActive
		StrGlobMisc *pMisc; // global miscellanous
							// check control value for 1.3.0.0 version
		DWORD CheckValue1_3_0_0;  // value will be 0x01234567
	};

	// valida per tomb4 e tomb5
	struct StrStateChange {
		WORD StateId;
		WORD N_AnimDispatches;
		WORD AnimDispatchIndex;
	};

	// valida per tomb4 o tomb5
	struct StrAnimDispatch {
		WORD Low;
		WORD High;
		WORD Animation;
		WORD Frame;
	};

	struct StrRecordMemZone {
		DWORD OldAddress;  // original address in tomb4
		DWORD SizeOldMemory;
		DWORD NewAddress;  // new address of allocated memory
		DWORD SizeNewMemory;
	};

	struct StrMemAllocata {
		void *pBaseMem;
		int ThreadId;
		WORD TestFree; // richiesta di liberare memoria
		char *pDescrizione; // testo per ricordare cosa sta allocando
	};

	struct StrBaseMemAllocata {
		int TotAllocata;
		StrMemAllocata VetAllocata[MAX_ALLOCATA];
	};

	struct StrSalvaVettoriRemap {
		short VetObjRemap[6000];
		int  TotRooms;
		short VetRoomRemap[400];
		bool  TestAttivo;
		char NomeFileTom[256];
	};
#pragma pack(pop)
}
