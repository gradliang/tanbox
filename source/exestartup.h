
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32)

#include <Windows.h>

__declspec(dllimport) int tanbox1_combine(int argc, char ** argv);
__declspec(dllimport) size_t get_u8len_from_u16(unsigned short * u16str, size_t u16length);
__declspec(dllimport) size_t utf16_to_utf8(unsigned short* u16str, size_t u16length, char * u8str, size_t u8len);

int wmain(int argc, wchar_t** argv)
{
    int ret, i;
    wchar_t* arg;
    char ** newargv = (char**) malloc((argc + 1) * sizeof(void*));

    for (i = 0; i < argc; i++)
    {
        size_t u8length, u16length;
        if (i == 0)
        {
            newargv[i] = (char*)malloc(strlen(COMMAND_STR) + 1);
            strcpy(newargv[i], COMMAND_STR);
        }
        else
        {
            arg = argv[i];
            u16length = wcslen(arg) + 1;
            u8length = get_u8len_from_u16(arg, u16length);
            newargv[i] = (char*)malloc(u8length);
            utf16_to_utf8(arg, u16length, newargv[i], u8length);
        }
    }
    newargv[argc] = NULL;
    
    ret = tanbox1_combine(argc, newargv);

    for (i = 0; i < argc; i++)
        free(newargv[i]);
    free(newargv);

    return ret;
}

#else

int main(int argc, char** argv)
{
    return 0;
}

#endif // _WIN32


