#pragma once


#ifdef Agate_DLL
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif// Core


#define BindFn(x) std::bind(&x, this, std::placeholders::_1)
