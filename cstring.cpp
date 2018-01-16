
#include "cstring.hpp"
using namespace pstd;

void* pstd::memchr(void const* str, char c, size_t n)
{
    if(str == nullptr) return nullptr;
    auto p = static_cast<char const*>(str);
    for(size_t count = 0; count < n; count++, p++)
    {
        if(*p == c) return const_cast<void*>((void const*)p);
    }
    return nullptr;
}

int pstd::memcmp(void const* str1, void const* str2, size_t n)
{
    if(str1 == nullptr or str2 == nullptr) return 0;
    auto p1 = static_cast<const char*>(str1);
    auto p2 = static_cast<const char*>(str2);
    for(size_t i = 0; i < n; i++)
    {
        auto diff = (p1 - p2);
        if(diff < 0) return -1;
        if(diff > 0) return 1;
    }
    return 0;
}


void* pstd::memcpy(void* dest, void const* src, size_t n)
{
    //no large-buffer optimization here.
    //can optimize by moving data 8 bytes at a time.
    auto d = static_cast<uint8_t*>(dest);
    auto s = static_cast<uint8_t const*>(src);
    if(d == s) return dest;
    for(size_t i = 0; i< n; i++)
    {
        d[i] = s[i];
    }
    return dest;
}

void* pstd::memmove(void* dest, void const* src, size_t n)
{
    auto d = static_cast<uint8_t*> (dest);
    auto s = static_cast<uint8_t const*>(src);

    if(d == s) return dest;

    //special case: dest < src + n
    if((d > s) and (d < s + n))
    {
        //copy backwards.
        for(size_t i = 0; i < n; i++)
        {
            d[n-1-i] = s[n-1-i];
        }
        return dest;
    }
    else
    {
        //copy forwards as normal
        return pstd::memcpy(dest, src, n);
    }
}

void* pstd::memset(void* buf, char c, size_t n)
{
    auto b = static_cast<char*>(buf);
    for(size_t i = 0; i < n; i++)
    {
        b[i] = c;
    }
    return buf;

}

char* pstd::strcat(char* dest, char const* src)
{
    size_t n = strlen(src);
    return pstd::strncat(dest, src, n);
}

char* pstd::strncat(char* dest, char const* src, size_t n)
{
    //find first insertion point
    char* p = dest + strlen(dest);
    for(size_t i = 0; i < n; i++)
    {
        *p = src[i];
        p++;
    }
    //cap off with null terminator
    *p = '\0';
    return dest;
}

char* pstd::strchr(char const* str, char c)
{
    for(auto p = str; *p != '\0'; p++)
    {
        if(*p == c) return const_cast<char*>(p);
    }
    return nullptr;
}

int pstd::strcmp(char const* str1, char const* str2)
{
    if(str1 == nullptr or str2 == nullptr) return 0;
    auto s1 = str1;
    auto s2 = str2;
    for(; *s1 != '\0' and *s2 != '\0'; s1++, s2++)
    {
        if(*s1 < *s2) return -1;
        else if(*s1 > *s2) return 1;
    }
    //check which string ended early.
    if(*s1 == '\0' and *s2 != '\0') return -1;//s1 ended early
    if(*s1 != '\0' and *s2 == '\0') return 1; //s2 ended early
    return 0; //string are equal.
}

int pstd::strncmp(char const* str1, char const* str2, size_t n)
{
    if(str1 == nullptr or str2 == nullptr or n == 0) return 0;
    auto s1 = str1;
    auto s2 = str2;
    size_t i = 0;
    for(; i < n and *s1 != '\0' and *s2 != '\0'; i++, s1++, s2++)
    {
        if(*s1 < *s2) return -1;
        else if(*s1 > *s2) return 1;
    }
    if(i == n) return 0;
    //check which string ended early.
    if(*s1 == '\0' and *s2 != '\0') return -1;//s1 ended early
    if(*s1 != '\0' and *s2 == '\0') return 1; //s2 ended early
    return 0; //string are equal.
}

char* pstd::strcopy(char* dest, char const* source)
{
    auto d = dest;
    auto s = source;
    while(*s != '\0')
    {
        *d = *s;
        d++;
        s++;
    }
    return dest;
}

char* pstd::strncopy(char* dest, char const* source, size_t n)
{
    if(dest == nullptr) return nullptr;
    if(source == nullptr or n == 0) return dest;
    auto s = source;
    auto d = dest;
    size_t count = 0;
    while(*s != '\0' and count < n)
    {
        *d = *s;
        d++;
        s++;
        count++;
    }
    //append null char
    *d = 0;
    return dest;
}

size_t pstd::strcspn(char const* str, char const* exclusion)
{
    if(str == nullptr or exclusion == nullptr) return 0;
    auto exclusion_length = pstd::strlen(exclusion);
    size_t count = 0;
    while(str[count] != '\0')
    {
        char c = str[count];
        if(pstd::memchr(exclusion, c, exclusion_length) != nullptr)
        {
            //character found in exclusion
            return count;
        }
        count++;
    }
    return count;
}

size_t pstd::strlen(char const* s1)
{
    if(s1 == nullptr) return 0;
    size_t count = 0;
    while(*s1 != 0)
    {
        s1++;
        count++;
    }
    return count;
}

size_t pstd::strlen_n(char const* s, size_t maxlength)
{
    if(s == nullptr) return 0;
    size_t count = 0;
    while(*s != 0 and count < maxlength)
    {
        s++;
        count++;
    }
    return count;
}

char* pstd::strpbrk(char const* str, char const* breakset)
{
    if(str == nullptr or breakset == nullptr) return nullptr;
    auto breakset_len = strlen(breakset);
    auto p = str;
    while(*p != 0)
    {
        char c = *p;
        if(pstd::memchr(breakset, c, breakset_len) != nullptr)
        {
            return const_cast<char*>(p);
        }
        p++;
    }
    return nullptr;
}


char* pstd::strrchr(char const* str, char c)
{
    if(str == nullptr) return nullptr;
    auto slen = strlen(str);

    for(size_t i = 0; i < slen; i++)
    {
        if(str[slen - 1 - i] == c)
        {
            return const_cast<char*>(str + slen-1-i);
        }
    }
    return nullptr;
}

size_t pstd::strspn(char const* str, char const* matches)
{
    if(str == nullptr or matches == nullptr) return 0;
    auto match_len = pstd::strlen(matches);
    size_t count = 0;
    while(str[count] != 0)
    {
        char c = str[count];
        if(pstd::memchr(matches, c, match_len) == nullptr) //found a non-matcher
        {
            return count;
        }
        count++;
    }
    return count;
}

char* pstd::strstr(char const* str, char const* substring)
{
    // a proper approach would be to use boyer-moore here, but I'm lazy.
    //could also early-exit when the search string is shorter than the substring.
    if(str == nullptr or substring == nullptr) return nullptr;
    auto sslen = strlen(substring);
    auto p = str; // p: starting point of search.
    while(*p != 0)
    {
        auto cmp = strncmp(p, substring, sslen);
        if(cmp == 0)
        {
            return const_cast<char*>(p);
        }
        p++;
    }
    return nullptr;
}
