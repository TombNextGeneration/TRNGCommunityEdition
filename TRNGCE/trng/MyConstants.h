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
}
