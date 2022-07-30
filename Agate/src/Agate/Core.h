#pragma once

#ifdef Agate_STATIC
#define API
#else
#ifdef Agate_DLL
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif// Core
#endif

#define BindFn(x) std::bind(&x, this, std::placeholders::_1)
