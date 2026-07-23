#include "discord.h"
#include <discord_rpc.h>
#include <ctime>
#include "constants.h"

namespace trngce {
	static DiscordRichPresence presence;

	void DiscordCreate() {
		Discord_Initialize(APPLICATION_ID, NULL, 1, NULL);
		presence.startTimestamp = time(NULL);
	}

	void DiscordUpdate(const char *details, const char *state) {
		presence.details = details;
		presence.state = state;
		Discord_UpdatePresence(&presence);
	}

	void DiscordClose() {
		Discord_Shutdown();
	}
}
