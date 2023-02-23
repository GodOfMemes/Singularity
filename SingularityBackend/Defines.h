#pragma once
#include "Core/Types.h"

#define SAPI extern "C" __declspec(dllexport)

SAPI void Start(GameConfig* config);
SAPI double GetRuntime();

// TODO
// 1. Error Callback
// 2. Rendering
// 3. Physics
// 4. Support dx12 and vulkan
// 5. Add support for linux