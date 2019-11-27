#include "Diff_Head.h"

const int PHRASE_SIZE = 1024;

void Read_Aloud (char* str, ...)
{
    va_list ptr;

    va_start (ptr, str);

    char* phrase = (char*) calloc (1, PHRASE_SIZE);
    vsprintf (phrase, str, ptr);
    va_end (ptr);

    char* pattern = (char*)calloc (1, PHRASE_SIZE);
    sprintf (pattern, "festival -b \'(begin (voice_msu_ru_nsh_clunits) (SayText \"%s\"))\'", phrase);

    system (pattern);

    free (pattern);
    free (phrase);
}
