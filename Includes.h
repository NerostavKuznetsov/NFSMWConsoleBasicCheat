#pragma once

// ➡️ Includes 
#include <Iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <String>

// ➡️ Headers 
#include "Cash.h"
#include "InfiniteNitrous.h"
#include "InfiniteSpeedbreaker.h"
#include "NeverBusted.h"
#include "MakeCustomProfileNames.h"

DWORD GetProcessIdByName(const std::wstring& processName);
