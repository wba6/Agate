/**
 * @brief Adds macros based on whether the engine should declare
 *        dynamic exports as well as a binding macro
 */

#ifndef AGATE_CORE_H
#define AGATE_CORE_H

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
#define BindStaticFn(x) std::bind(&x, std::placeholders::_1)

#endif // AGATE_CORE_H
