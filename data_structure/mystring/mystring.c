#include "mystring.h"

bool String_init(string *str)
{
    memset(str, 0x0, sizeof(string));
    return true;
}


bool String_assign(string *str, const char *ch)   
{
    str->elem = malloc(sizeof(char) * (strlen(ch) + 1)); 
    if(!str->elem)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return false;
    }

    strcpy(str->elem, ch);
    str->length = strlen(str->elem);
    return true;
}


size_t String_length(const string *str)
{
    return str->length;
}


int String_compare(const string *str_a, const string *str_b)
{

    return 0;
}


bool String_clear(string *str)
{
    
   if(str->length)
    {
        free(str->elem);
        str->length = 0;
    }
    return true; 
}


bool String_concat(const string *str_a, const string *str_b, string *out_str)
{

    return true;
}


bool String_substr(const string *str, int pos, int len, string *out_str)
{

    return true;
}


int String_index(const string *str, const string *child_str, int pos)
{

    return true;
}


