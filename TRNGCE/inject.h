#pragma once

void ProcessInject(unsigned int from, unsigned int to, bool replace);
void ProcessPatchInject(unsigned int from, unsigned int to, unsigned int patch, bool replace);
void ModuleProcessInject(void *module, const char *name, unsigned int to, bool replace);
void ModuleAddressProcessInject(void *module, unsigned int address, unsigned int to, bool replace);
void IndirectReferenceInject(void **reference);
void ModuleReferenceInject(void **reference, void *module);
void ModuleAddressReferenceInject(void **reference, void *module);
void ConditionalInvalidReferenceInject(void **reference, bool condition);
void ConditionalIndirectReferenceInject(void **reference, bool condition);
void CopyInject(void *module, const char *name, void *target, unsigned int size);
void CopyAddressInject(void *module, unsigned int address, void *target, unsigned int size);
bool ConditionNoScript();
