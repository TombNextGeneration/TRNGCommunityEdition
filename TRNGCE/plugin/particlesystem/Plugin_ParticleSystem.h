#pragma once

namespace plugin::particlesystem {
	void ControlParticles(void);
	void GameCleanup(void);
}

void Inject_Plugin_Particlesystem(void* module, bool replace);
