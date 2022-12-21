#pragma once

#ifdef _WIN32
#ifdef EXPORT_DLL
#define EXPORT_API __declspec(dllexport)
#else   // EXPORT_DLL
#define EXPORT_API __declspec(dllimport)
#endif  // EXPORT_DLL

#else   // _WIN32
#define EXPORT_API
#endif  // _WIN32