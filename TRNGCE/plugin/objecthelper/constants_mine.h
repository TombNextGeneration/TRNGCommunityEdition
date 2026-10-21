#pragma once

namespace plugin::objecthelper {
	inline constexpr int QUERY_SPRITE = 0x1;
	inline constexpr int QUERY_GUNFLASH = 0x2;
	inline constexpr int QUERY_ZOMBIE = 0x4;
	inline constexpr int QUERY_KILLER = 0x8;
	inline constexpr int QUERY_DEATH = 0x10;
	inline constexpr int QUERY_HEADSHOT = 0x20;
	inline constexpr int QUERY_PATROL = 0x40;
	inline constexpr int QUERY_PATROL2 = 0x80;
	inline constexpr int QUERY_VAULT = 0x100;
	inline constexpr int QUERY_TOUCH = 0x200;

	inline constexpr int QUERY_MASK = 0x3FF;

	inline constexpr int PLUGIN_FLIPEFFECT_FUNCTION = 1;
	inline constexpr int PLUGIN_FLIPEFFECT_GLOBAL = 2;
	inline constexpr int PLUGIN_FLIPEFFECT_QUERY = 3;

	inline constexpr int TIMER_EXTENDED = 0;
	inline constexpr int TIMER_THRESHOLD = 128;

	inline constexpr int PLUGINS = 12;
}
