#pragma once

void ProcessInject(unsigned int from, unsigned int to, bool replace);
void ModuleProcessInject(void *module, const char *name, unsigned int to, bool replace);
void IndirectReferenceInject(void **reference);
void ModuleReferenceInject(void **reference, void *module);
void CopyInject(void *module, const char *name, void *target, unsigned int size);
