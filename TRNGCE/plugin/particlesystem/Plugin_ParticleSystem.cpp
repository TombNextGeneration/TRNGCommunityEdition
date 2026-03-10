#include "Plugin_ParticleSystem.h"
#include "../../inject.h"

namespace plugin::particlesystem {
	void ControlParticles(void)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Plugin_Particlesystem(void* module, bool replace)
{
	ModuleProcessInject(module, "ControlParticles", (unsigned int)plugin::particlesystem::ControlParticles, false);
}
