#include <stddef.h>

#ifndef TANBOX_COMMON_H_06D3716724DFB0C5
#define TANBOX_COMMON_H_06D3716724DFB0C5

#if defined(_WIN32)
#define BOX_EXPORT       __declspec(dllexport)
#define BOX_IMPORT       __declspec(dllimport)
#else
#define BOX_IMPORT
#define BOX_IMPORT
#endif

#ifdef __cplusplus
#define EXTERN_C            extern "C" 
#else
#define EXTERN_C
#endif

#endif // !TANBOX_COMMON_H_06D3716724DFB0C5

