# Style guide

## Namespaces

- All code except `#include` should be placed in a namespace.
- `using namespace` should be avoided.

## Macros

- Macros should be avoided.

## Files

- Every .cpp file should have its own .h file, in the same folder and with same name.
- The first line of a header file should be `#pragma once`.
- The first line of a source file should include its associated header file.

## Definitions

- All public definitions of a source file should be declared in its associated header file.
- All internal definitions should be `static`.
