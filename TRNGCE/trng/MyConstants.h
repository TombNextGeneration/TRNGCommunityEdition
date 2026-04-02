#pragma once

namespace trng {
	inline constexpr int MAX_DIRECT_CB = 100;
	inline constexpr int MAX_PATCHES = 10000;
	inline constexpr int MAX_PLUGINS = 256;
	inline constexpr int MAX_REQUIRED_CB = 5000;
	// max index number-1 for trigger callbacks
	inline constexpr int MAX_CALLBACK_FLIP = 1024;
	inline constexpr int MAX_CALLBACK_ACTION = 256;
	inline constexpr int MAX_CALLBACK_CONDITION = 256;
	inline constexpr int MAX_TRNG_ASM_PATCH = 1000;
	// other max value for index with other callbacks:
	inline constexpr int MAX_CUSTOMIZE = 8000;
	inline constexpr int MAX_PARAM = 8000;
	inline constexpr int MAX_GTRIGGER_CB = 8000;
	inline constexpr int MAX_PLUGIN_NGLE = 1000;

	//  NGFM = NG Flag Main
	inline constexpr int ngfm_NONE = 0;
	inline constexpr int ngfm_Diagnostica = 0x0001;
	inline constexpr int ngfm_CryptScript = 0x0002;
	inline constexpr int ngfm_CryptSavegame = 0x0004;
	inline constexpr int ngfm_CRS = 0x0008;
	inline constexpr int ngfm_BumpMapping_Enable = 0x0010;
	inline constexpr int ngfm_BumpMapping_Disable = 0x0020;
	inline constexpr int ngfm_ShowLaraInTitle = 0x0040;
	inline constexpr int ngfm_DisableBASSEngine = 0x0080;
	inline constexpr int ngfm_Enable_Trlm_Options = 0x0100;

	inline constexpr int LNGC_MAIN = 1;
	inline constexpr int LNGC_TRANSLATION = 2; // My_NG_Costants.txt
	inline constexpr int LNGC_PLUGIN = 3; // carica file "plugin_name.trg"

	inline constexpr int NGTAG_END_SEQUENCE = 0;
	inline constexpr int NGTAG_NON_USATO = 0x8001;  // era NGTAG_N_UV_RANGES
	inline constexpr int NGTAG_ANIMATED_TEXTURES = 0x8002;   // .tom .prj .tr4
	inline constexpr int NGTAG_OLD_EFFECTS = 0x8003;  // savegame
	inline constexpr int NGTAG_OLD_FMV = 0x8004;      // savegame
	inline constexpr int NGTAG_REMAP_OBJ = 0x8005;    // .tom .tr4
	inline constexpr int NGTAG_SALVA_COORDINATE = 0x8006;   // savegame
	inline constexpr int NGTAG_PROGR_ACTIONS = 0x8007;   // savegame
	inline constexpr int NGTAG_OLD_ACTIONS = 0x8008;     // savegame
	inline constexpr int NGTAG_EXTRA_INFO_ROOMS = 0x8009;  // .tom .tr4
	inline constexpr int NGTAG_LANGUAGE_STRINGS = 0x800A;   // english.dat
	inline constexpr int NGTAG_SCRIPT_OPTIONS = 0x800B;   // script.dat
	inline constexpr int NGTAG_SCRIPT_LEVEL = 0x800C;      // script.dat
	inline constexpr int NGTAG_FLAG_LEVEL_TR4 = 0x800D;    // .tom .tr4
	inline constexpr int NGTAG_OLD_CONDITION = 0x800E;   // savegame
	inline constexpr int NGTAG_VARIABLE_DATA = 0x800F;   // savegame
	inline constexpr int NGTAG_PUSH_CLIMB = 0x8010;   // savegame
	inline constexpr int NGTAG_PRINT_STRING = 0x8011;   // savegame
	inline constexpr int NGTAG_ELEVATORS = 0x8012;    // savegame
	inline constexpr int NGTAG_MIRRORS = 0x8013;      // savegame
	inline constexpr int NGTAG_BLIND_SAVE = 0x8014;   // savegame
	inline constexpr int NGTAG_CASUALE = 0x8015;   // savegame
	inline constexpr int NGTAG_CONTROLLO_OPTIONS = 0x8016; // script.dat
	inline constexpr int NGTAG_TEX_PARZIALE = 0x8017;  // .tom .tr4
	inline constexpr int NGTAG_REMAP_TAILS = 0x8018; // .tom .tr4
	inline constexpr int NGTAG_SWAP_MESH = 0x8019; // savegame
	inline constexpr int NGTAG_STATUS_GTRIGGERS = 0x801A;  // savegame
	inline constexpr int NGTAG_ROOM_FLAGS = 0x801C; // savegame
	inline constexpr int NGTAG_WEATHER_INTENSITY = 0x801D; // savegame
	inline constexpr int NGTAG_STATUS_ORGANIZER = 0x801E; // savegame
	inline constexpr int NGTAG_IMPORT_FILE = 0x801F;  // script.dat , sezione options
	inline constexpr int NGTAG_INDICI_PFRAME = 0x8020; // savegame
	inline constexpr int NGTAG_REMAP_STATICS = 0x8021; // tom e tr4
	inline constexpr int NGTAG_SALVA_STATICS = 0x8022; // savegame
	inline constexpr int NGTAG_SALVA_TIMER_OGGETTI = 0x8023; // savegame
	inline constexpr int NGTAG_VERSION_HEADER = 0x8024;  // tutti i file
	inline constexpr int NGTAG_TOM_VERSION = 0x8025; // file tom
	inline constexpr int NGTAG_STATUS_ANIM_RANGES = 0x8030; // savegame
	inline constexpr int NGTAG_SAVEGAME_INFOS = 0x8031; // savegame
	inline constexpr int NGTAG_MINI_SHOT = 0x8032; // savegame
	inline constexpr int NGTAG_LEVEL_NAMES = 0x8033; // script.
	inline constexpr int NGTAG_NG_HUB_HEADERS = 0x8035; // savegame
	inline constexpr int NGTAG_VAR_DATA_LARA = 0x8036; // savegame lara hub
	inline constexpr int NGTAG_VET_REMAP_ROOMS = 0x8037; // file TOM
	inline constexpr int NGTAG_VAR_GLOBAL_TRNG = 0x8038; // var globali savegame e hub
	inline constexpr int NGTAG_VAR_LOCAL_TRNG = 0x8039; // var locali savegame e hub
	inline constexpr int NGTAG_FROZEN_ITEMS = 0x803A; // savegame e hub
	inline constexpr int NGTAG_SAVE_LOCUST = 0x803B; // savegame e hub
	inline constexpr int NGTAG_NO_COLL_ITEMS = 0x803C; // savegame e hub
	inline constexpr int NGTAG_SLOT_NAMES = 0x803D; // project (di ngle)
	inline constexpr int NGTAG_FISH = 0x803E;  // savegame
	inline constexpr int NGTAG_STATUS_TRIGGER_GROUP = 0x803F; // savegame e hub
	inline constexpr int NGTAG_ADAPTIVE_FARVIEW = 0x8040; // savegame e hub
	inline constexpr int NGTAG_KAYAK_EXTRA_DATA = 0x8041; // savegame e hub
	inline constexpr int NGTAG_ASSIGNED_SLOT = 0x8042; // savegame e hub
	inline constexpr int NGTAG_DIARY_DATA = 0x8043; // savegame e hub
	inline constexpr int NGTAG_ANIM_SWAPPING = 0x8044; // savegame locale
	inline constexpr int NGTAG_FLIP_MESH = 0x8045; // savegame locale
	inline constexpr int NGTAG_PLUGIN_DATA = 0x8046;  //  savegame locale
	inline constexpr int NGTAG_PLUGIN_NAMES_NGLE = 0x8047; // prj tom and tr4 (info sui nomi plugin e loro id)
	inline constexpr int NGTAG_PLUGIN_ID_FLOOR_TABLE = 0x8048; // tom and tr4 (mirror of floor data with id of plugin)
	inline constexpr int NGTAG_EXTRA_AI_RECORDS = 0x8049; // savegame locale
	inline constexpr int NGTAG_CUTSCENE_CAMERA = 0x804A; // savegame locale
	inline constexpr int NGTAG_ACTORS_INDICES = 0x804B; // savegame locale
	inline constexpr int NGTAG_SLOT_FLAGS_ARRAY = 0x804C; // savegame globale(?)  usato per tr omni explorer
	inline constexpr int NGTAG_OCB_ITEMS = 0x804D; // savegame locale
	inline constexpr int NGTAG_REMAP_PLUGIN_IDS = 0x804E; // .tr4 file (non sempre presente, solo se usato meta cabinet)
	inline constexpr int NGTAG_SWAP_SINGLE_MESH = 0x804F; // savegame locale
	inline constexpr int NGTAG_NEW_CAMERAS = 0x8050;  // savegame locale
	inline constexpr int NGTAG_SLOT_INFO = 0x8051; // savegame locale

	// --- codici tag per singoli comandi o sezioni script.dat
	// CNT = Codici New Tag
	// nota: non tutti sono presneti in header ng, alcuni sono sono
	// solo usati in codicifica interna in ng_scripter

	inline constexpr int cnt_AssignSlot = 1;
	inline constexpr int cnt_Snow = 2;
	inline constexpr int cnt_LevelFarView = 3;
	inline constexpr int cnt_FogRange = 4;
	inline constexpr int cnt_WorldFarView = 5;
	inline constexpr int cnt_TextFormat = 6;
	inline constexpr int cnt_Rain = 7;
	inline constexpr int cnt_Damage = 8;
	inline constexpr int cnt_Enemy = 9;
	inline constexpr int cnt_Animation = 10;
	inline constexpr int ctn_MirrorEffect = 11;
	inline constexpr int ctn_Elevator = 12;
	inline constexpr int ctn_KeyPad = 13;
	inline constexpr int ctn_AddEffect = 14;
	inline constexpr int ctn_Detector = 15;
	inline constexpr int ctn_Settings = 16;
	inline constexpr int ctn_TextureSequence = 17;
	inline constexpr int ctn_Equipment = 18;
	inline constexpr int ctn_MultEnvCondition = 19;
	inline constexpr int ctn_Customize = 20;
	inline constexpr int ctn_TriggerGroup = 21;
	inline constexpr int ctn_GlobalTrigger = 22;
	inline constexpr int ctn_Organizer = 23;
	inline constexpr int ctn_SoundSettings = 24;
	inline constexpr int ctn_ItemGroup = 25;
	inline constexpr int ctn_ColorRGB = 26;
	inline constexpr int ctn_Parameters = 27;
	inline constexpr int ctn_Turbo = 28;
	inline constexpr int ctn_WindowTitle = 29;
	inline constexpr int ctn_TestPosition = 30;
	inline constexpr int ctn_LogItem = 31;
	inline constexpr int ctn_WindowsFont = 32;
	inline constexpr int ctn_Diary = 33;
	inline constexpr int ctn_Image = 34;
	inline constexpr int ctn_SavegamePanel = 35;
	inline constexpr int cnt_DiagnosticType = 36;
	inline constexpr int cnt_Switch = 37;
	inline constexpr int cnt_CombineItems = 38;
	inline constexpr int cnt_StandBy = 39;
	inline constexpr int cnt_AnimationObj = 40;
	inline constexpr int cnt_DefaultWindowsFont = 41;
	inline constexpr int cnt_Demo = 42;
	inline constexpr int cnt_Plugin = 43;
	inline constexpr int cnt_LaraStartPos = 44;
	inline constexpr int cnt_StaticMIP = 45;
	inline constexpr int cnt_TriggerGroupWord = 46;
	// hidden commands
	inline constexpr int cnt_FlagsOption = 200;
	inline constexpr int cnt_FlagsLevel = 201;

	// ---- COSTANTI NG-----------
	inline constexpr int NG_LONG_CHECK = 0x454C474E;
	inline constexpr int NG_SHORT_CHECK = 0x474E;

	inline constexpr int PLUG_FROM_SCRIPT = 1;   // quelli memorizzati per comandi script customize e parameter
	inline constexpr int PLUG_FROM_NGLE = 2;    // quelli memorizzati nel floor data preso da file .tr4
	inline constexpr int PLUG_FROM_TRNG = 3;  // quelli scansditi e collegati in modo dinamico all'avvio di tomb4

	// flag per savegame info salvate in header savegame
	inline constexpr int FSAV_BLINDED = 0x0001;
	inline constexpr int FSAV_LARA_FLARE = 0x0002;
	inline constexpr int FSAV_LARA_OFF_TORCH = 0x0004;
	inline constexpr int FSAV_LARA_BURNING_TORCH = 0x0008;
	inline constexpr int FSAV_OLD_FORMAT = 0x0010;
}
