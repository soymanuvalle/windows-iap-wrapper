#pragma once

// Full C++/WinRT projections (order matters). Incomplete includes cause C3779
// ("cannot use a function that returns 'auto' before it is defined").
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Services.Store.h>

#include <Windows.h>
#include <shobjidl.h>
#include <Shlobj.h>
