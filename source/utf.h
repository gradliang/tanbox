#ifndef UTF_H_46C496776EB61B1E
#define UTF_H_46C496776EB61B1E

#include "tanbox_common.h"

EXTERN_C BOX_EXPORT size_t get_u8len_from_u16(unsigned short* u16str, size_t u16length);
EXTERN_C BOX_EXPORT size_t utf16_to_utf8(unsigned short* u16str, size_t u16length, char* u8str, size_t u8len);

#endif // !UTF_H_46C496776EB61B1E

