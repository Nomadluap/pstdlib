

#pragma once
#include <stdint.h>
#include <stddef.h>

namespace pstd
{
    /**
     * Search for the first occurence of c in the first n characters of str.
     * @param str String to search
     * @param c Character to find.
     * @param n Length of string, in bytes.
     * @return Pointer to the first byte in str that is equal to c, or null if the byte is not found.
     */
    void* memchr(void const* str, char c, size_t n);

    /**
     * Compare the two memory buffers lexographically.
     * @param str1 First string to compare
     * @param str2 Second string to compare.
     * @param n Buffer size.
     * @return 0 if the strings are equal, otherwise -1 if str1 < str2, otherwise 1 if str1 > str2
     */
    int memcmp(void const* str1, void const* str2, size_t n);


    /**
     * Copies n bytes from src to dest. The buffer regions must not overlap.
     * @param dest Destination buffer.
     * @param src Source buffer
     * @param n Number of bytes.
     * @return dest.
     */
    void* memcpy(void* dest, void const* src, size_t n);

    /**
     * Copies n bytes from src to dest. The buffers are allowed to overlap.
     * @param dest Destination buffer.
     * @param src Source buffer.
     * @param n Number of bytes.
     * @return dest.
     */
    void* memmove(void* dest, void const* src, size_t n);

    /**
     * Set first n bytes of buf to value c.
     * @param buf  Buffer to modify.
     * @param c  Value to set on every byte.
     * @param n  Number of bytes to process.
     * @return buf.
     */
    void* memset(void* buf, char c, size_t n);

    /**
     * Appends a copy of the null-terminated string src onto the end of dest.
     * Note that dest must be at least of size strlen(dest) + strlen(src) + 1 bytes long.
     * The result string will be null-terminated.
     *
     * @param dest Destination buffer.
     * @param src Source buffer.
     * @return dest.
     */
    char* strcat(char* dest, char const* src);

    /**
     * Copy the first n bytes of src to the end of dst. Dst must be appropriately sized.
     * The result string wil be null terminated.
     * @param dest Destination string
     * @param src source string
     * @param n Number of characters to append
     * @return dest
     */
    char* strncat(char* dest, char const* src, size_t n);

    /**
     * Find the first occurence of c in str.
     * @param str  A null-terminated string.
     * @param c Character to find
     * @return Pointer to the first found character, or nullptr if the character could not be
     * found.
     */
    char* strchr(char const* str, char c);

    /**
     * Lexographical comparison of two null-terminated strings.
     * @param str1
     * @param str2
     * @return -1 if str1 < str2, 1 if str1 > str2, or 0 if str1 == str2.
     */
    int strcmp(char const* str1, char const* str2);

    /**
     * Lexographical comparison of the first n characters of str1 and str2.
     * @param str1
     * @param str2
     * @param n Number of characters to compare.
     * @return -1 if str1 < str2, 1 if str1 > str2, 0 if str1 == str2
     */
    int strncmp(char const* str1, char const* str2, size_t n);

    /**
     * Copies source, including the null-terminator, to dest.
     * @param dest Destination buffer. Must be of the apropriate size.
     * @param source Source sttring, null terminated.
     * @return dest.
     */
    char* strcopy(char* dest, char const* source);

    /**
     * Copies the first n characters of source to dest. The result will be null-terminated.
     * @param dest Destination buffer. Must be of size n+1 or greater.
     * @param source Source string. Must be of size at least n.
     * @param n Number of characters to copy.
     * @return dest.
     */
    char* strncopy(char* dest, char const* source, size_t n);

    /**
     * Returns the length of the maximum initial segment of the byte string pointed
     * to by dest, that consists of characters NOT found in src.
     * "complimentary span"
     * @param str String to search in, null-terminated.
     * @param exclusion string of Characters to exclude, null-terminated.
     * @return Length of initial run of str that does not contain characters in exclusion.
     */
    size_t strcspn(char const* str, char const* exclusion);

    /**
     * Length of a given string, not including the null-terminator.
     * @param s1 Query string.  Must be null-terminated.
     * @return Length of s1.
     */
    size_t strlen(char const* s1);

    /**
     * strlen with upper bound.
     * @param s  Input string. Should be null-terminated.
     * @param maxlength Maximum length down the string to search.
     * @return min(maxlength, strlen(s))
     */
    size_t strlen_n(char const* s, size_t maxlength);

    /**
     * Scans str for any character contained in breakset.
     * @param str Input search string, null terminated.
     * @param breakset null-terminated array of characters to break on.
     * @return Pointer to first break character, or nullptr if none can be found.
     */
    char* strpbrk(char const* str, char const* breakset);


    /**
     * Find the LAST occurence of the character c in the string.
     * @param str  Null-terminated input string.
     * @param c Search character.
     * @return pointer to found character in str, or nullptr if c could not be found.
     */
    char* strrchr(char const* str, char c);

    /**
     * Returns the length of the maximal prefix of str that contains only characters found in
     * matches.
     * @param str Null-terminated search string.
     * @param matches null-terminated array of match characters
     * @return Length of the max initial segment that contains only characters from matches.
     */
    size_t strspn(char const* str, char const* matches);

    /**
     * Find the first occurence of substring in string.
     * @param str STring to search. Must be null-terminated.
     * @param needle Substring to find. Must be null-terminated.
     * @return Pointer to the first character of substring in str, or nullptr if substring could
     * not be found.
     */
    char* strstr(char const* str, char const* substring);




}
