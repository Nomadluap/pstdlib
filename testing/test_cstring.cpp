#include "catch.hpp"
#include "cstring.hpp"
#include <cstring>
#include <type_traits>


namespace p = pstd;

TEST_CASE( "memchr", "[cstring]")
{
    char const* teststring = "the quick brown fox jumps over the lazy dog";
    size_t sl = std::strlen(teststring);

    REQUIRE(p::memchr(teststring, 't', sl) == (void*)teststring);
    REQUIRE(p::memchr(teststring, 'e', sl) == (void*)(teststring + 2));
    REQUIRE(p::memchr(teststring, ' ', sl) == (void*)(teststring + 3));
    REQUIRE(p::memchr(teststring, 'T', sl) == nullptr);
    REQUIRE(p::memchr(teststring, '\0', sl) == nullptr);
    REQUIRE(p::memchr(teststring, ' ', 3) == nullptr);
    REQUIRE(p::memchr(static_cast<char*>(nullptr), ' ', 1233) == nullptr);
}
TEST_CASE( "memcmp", "[cstring]")
{
    auto a = "abcdefg010101";
    auto b = "abcdefg010101";
    auto c = "abcdefg110101";
    auto l = std::strlen(a);
    REQUIRE(p::memcmp(a, b, l) == 0);
    REQUIRE(p::memcmp(a, c, l) < 0);
    REQUIRE(p::memcmp(c, a, l) > 0);
    REQUIRE(p::memcmp(nullptr, a, l) == 0);
}
TEST_CASE( "memcpy", "[cstring]")
{
    GIVEN("Buffers src, dest")
    {
        char src[10] = "123456789";
        char dest[10];
        WHEN("memcpy from source to dest")
        {
            auto result = p::memcpy(dest, src, sizeof(src));

            THEN("result == dest")
            {
                REQUIRE(result == dest);
            }
            THEN("dest contains a copy of src")
            {
                for(size_t i = 0; i < sizeof(src); i++)
                {
                    REQUIRE(src[i] == dest[i]);
                }
            }
        }
    }
}
TEST_CASE( "memmove", "[cstring]")
{
    GIVEN("A Source buffer src")
    {
        char src[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

        WHEN("memmove to separate buffer")
        {
            char dest[10]{};
            auto result = p::memmove(dest, src, 10);
            THEN("dest should be returned")
            {
                REQUIRE(result == dest);
            }
            THEN("Buffers should be equal")
            {
                for(size_t i = 0; i < sizeof(src); i++)
                {
                    REQUIRE(src[i] == dest[i]);
                }
            }
        }
        WHEN("memmove to forward overlapping buffer")
        {
            auto result = memmove(src + 1, src, 9);

            THEN("buffer should be shifted")
            {
                char expected[10] = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                for(size_t i = 0; i < 10; i++)
                {
                    REQUIRE(expected[i] == src[i]);
                }
            }
            THEN("result should be src+1")
            {
                REQUIRE(result == src+1);
            }
        }
        WHEN("memmove to backward overlapping buffer")
        {
            auto result = p::memmove(src, src+2, 8);

            THEN("buffer should be shifted correctly. ")
            {
                char expected[10] = {3, 4, 5, 6, 7, 8, 9, 0, 9, 0};
                for(size_t i = 0; i < 10; i++)
                {
                    REQUIRE(expected[i] == src[i]);
                }
            }
            THEN("Result should be src")
            {
                REQUIRE(result == src);
            }
        }

    }
}
TEST_CASE( "memset", "[cstring]")
{
    GIVEN("A buffer b")
    {
        char b[5] = {1, 2, 3, 4, 5};
        WHEN("filled with ones")
        {
            auto ret = p::memset(b, 1, sizeof(b));
            THEN("buffer is all ones")
            {
                for(size_t i = 0; i < sizeof(b); i++)
                {
                    REQUIRE(b[i] == 1);
                }
            }
        }
    }
}
TEST_CASE( "strcat", "[cstring]")
{
    GIVEN("a string with empty space")
    {
        char buf[14] = {'H', 'e', 'l', 'l', 'o', ',', '\0', 1, 1, 1, 1, 1, 1, 1};

        WHEN("world is appended")
        {
            auto newpart = " world!";
            auto result = p::strcat(buf, newpart);

            THEN("result is dest")
            {
                REQUIRE(result == buf);
            }
            THEN("result is null terminated")
            {
                REQUIRE(buf[13] == '\0');
            }
            THEN("result string should be of proper size")
            {
                REQUIRE(std::strlen(buf) == 13);
            }
            THEN("string should be 'Hello, World!")
            {
                auto expected = "Hello, world!";
                REQUIRE(std::strcmp(buf, expected) == 0);
            }
        }
    }
}
TEST_CASE( "strncat", "[cstring]")
{
    GIVEN("a string with empty space")
    {
        char buf[6] = {'1', '2', '3', '4', 0, 1};
        REQUIRE(std::strlen(buf) == 4);
        WHEN("one char is copied")
        {
            auto s = "5678";
            p::strncat(buf, s, 1);

            THEN("string is one character longer")
            {
                REQUIRE(std::strlen(buf) == 5);
                REQUIRE(buf[4] == '5');
            }

        }
    }

}
TEST_CASE( "strchr", "[cstring]")
{
    GIVEN("a string")
    {
        auto s = "1234567890";
        WHEN("an existing char is searched")
        {
            auto result = pstd::strchr(s, '4');
            THEN("result is not null")
            {
                REQUIRE(result != nullptr);
            }
            THEN("result should point to that location")
            {
                REQUIRE(*result == '4');
            }
        }
        WHEN("a non-existant character is searched")
        {
            auto result = pstd::strchr(s, 'a');
            THEN("result should be nullptr")
            {
                REQUIRE(result == nullptr);
            }
        }
    }
}
TEST_CASE( "strcmp", "[cstring]")
{
    GIVEN("two equal strings")
    {
        auto s1 = "The quick brown fox jumps over the lazy dog";
        auto s2 = "The quick brown fox jumps over the lazy dog";

        WHEN("the strings are compared")
        {
            int res = pstd::strcmp(s1, s2);

            THEN("result should be zero")
            {
                REQUIRE(res == 0);
            }
        }
    }
    GIVEN("A single string")
    {
        auto s1 = "asd;flkajsdcvo;liasj;dlkfj";
        WHEN("the string is compared against itself")
        {
            int res = pstd::strcmp(s1, s1);
            THEN("result should be zero")
            {
                REQUIRE(res == 0);
            }
        }
    }
    GIVEN("A string and it's prefix")
    {
        auto s = "The quick brown fox jumps over the lazy dog";
        auto p = "The quick brown fox";
        WHEN("the string is compared to its prefix")
        {
            auto r1 = pstd::strcmp(s, p);
            auto r2 = pstd::strcmp(p, s);
            THEN("s should compare greater than p")
            {
                REQUIRE(r1 > 0);
                REQUIRE(r2 < 0);
            }
        }
    }
    GIVEN("a string")
    {
        auto s = "1233312354;laskdj;lkj";
        WHEN("the string is compared to nullptr")
        {
            auto res = pstd::strcmp(s, nullptr);
            auto res2 = pstd::strcmp(nullptr, s);
            THEN("The result should be zero")
            {
                REQUIRE(res == 0);
                REQUIRE(res2 == 0);
            }
        }
    }

    GIVEN("a nullptr")
    {
        WHEN("two nullptrs are compared")
        {
            auto res = std::strcmp(nullptr, nullptr);
            THEN("result should be zero")
            {
                REQUIRE(res == 0);
            }
        }
    }

    GIVEN("two different strings of the same length")
    {
        auto s1 = "abcdefg";
        auto s2 = "abcdEfg";
        WHEN("the strings are compared")
        {
            auto r1 = pstd::strcmp(s1, s2);
            auto r2 = pstd::strcmp(s2, s1);
            THEN("strings should not be equal")
            {
                REQUIRE(r1 != r2);
                REQUIRE(r1 > 0);
                REQUIRE(r2 < 0);
            }
        }
    }
}
TEST_CASE( "strncmp", "[cstring]")
{
    GIVEN("two strings equal in their first part")
    {
        auto s1 = "123456Y";
        auto s2  = "123456N";
        WHEN("the equal parts of the strings are compared")
        {
            auto r1 = pstd::strncmp(s1, s2, 6);
            auto r2 = pstd::strncmp(s2, s1, 6);
            THEN("strings should compare equal")
            {
                REQUIRE(r1 == 0);
                REQUIRE(r2 == 0);
            }
        }
        WHEN("The whole strings are compared")
        {
            auto r1 = pstd::strncmp(s1, s2, 7);
            auto r2 = pstd::strncmp(s2, s1, 7);
            THEN("strings should not be equal")
            {
                REQUIRE(r1 > 0);
                REQUIRE(r2 < 0);
            }
        }
        WHEN("strings are compared with length zero")
        {
            auto r = pstd::strncmp(s1, s2, 0);
            THEN("strings should be equal")
            {
                REQUIRE(r == 0);
            }
        }
        WHEN("a string is compared with nullptr")
        {
            auto r1  = pstd::strncmp(s1, nullptr, 6);
            auto r2  = pstd::strncmp(nullptr, s1, 6);
            THEN("the result should be zero")
            {
                REQUIRE(r1 == 0);
                REQUIRE(r2 == 0);
            }
        }
    }
    GIVEN("a single string")
    {
        auto s = "asd;flkajsdf;avoiaj;sdlkj";
        WHEN("a string is compared with itself")
        {
            auto r1 = pstd::strncmp(s, s, 0);
            auto r2 = pstd::strncmp(s, s, 3);
            auto r3 = pstd::strncmp(s, s, 5);
            THEN("the result should be zero")
            {
                REQUIRE(r1 == 0);
                REQUIRE(r2 == 0);
                REQUIRE(r3 == 0);
            }
        }
    }
    GIVEN("a short and long string that share a prefix")
    {
        auto s1 = "a string that is LOOOONG";
        auto s2 = "a string that is";
        WHEN("the strings are compared")
        {
            auto r1 = pstd::strncmp(s1, s2, std::strlen(s2)+1);
            auto r2 = pstd::strncmp(s2, s1, std::strlen(s2)+1);
            THEN("the short string should be  lesser")
            {
                REQUIRE(r1 > 0);
                REQUIRE(r2 < 0);
            }
        }
        WHEN("n is equal to the length of the short string")
        {
            auto r1 = pstd::strncmp(s1, s2, std::strlen(s2));
            auto r2 = pstd::strncmp(s2, s1, std::strlen(s2));
            THEN("the strings should compare equal")
            {
                REQUIRE(r1 == 0);
                REQUIRE(r2 == 0);
            }
        }
    }

}
TEST_CASE( "strcopy", "[cstring]")
{
    GIVEN("a string and a buffer")
    {
        auto s = "1234567890";
        char buf[11] = {3};
        WHEN("the string is copied into the buffer")
        {
            auto r = pstd::strcopy(buf, s);
            THEN("result should be pointer to dest")
            {
                REQUIRE(r == buf);
            }
            THEN("buf should be null-terminated")
            {
                REQUIRE(buf[10] == 0);
            }
            THEN("buf should have same string-length")
            {
                REQUIRE(std::strlen(s) == std::strlen(buf));
            }
            THEN("the strings should be equal")
            {
                REQUIRE(std::strcmp(s, buf) == 0);
            }
        }
    }
}
TEST_CASE( "strncopy", "[cstring]")
{
    GIVEN("a string and a buffer")
    {
        auto s = "1234567890";
        char buf[20] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
        WHEN("a prefix of the string is copied into the buffer")
        {
            auto r = pstd::strncopy(buf, s, 3);
            THEN("result should be pointer to dest")
            {
                REQUIRE(r == buf);
            }
            THEN("buf should be null-terminated")
            {
                REQUIRE(buf[3] == 0);
            }
            THEN("copied part of string should be equal to original")
            {
                REQUIRE(std::strncmp(s, buf, 3) == 0);
            }
        }
        WHEN("n is larger than the source string")
        {
            auto r = pstd::strncopy(buf, s, 12);
            THEN("copying should stop at the end of the source string")
            {
                CHECK(buf[8] == '9');
                CHECK(buf[9] == '0');
                CHECK(buf[10] == 0);
                CHECK(buf[11] == 3);
                CHECK(buf[12] == 3);
            }
        }
    }
}
TEST_CASE( "strcspn", "[cstring]")
{
    auto t1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    GIVEN("a source string that contains excluded characters")
    {
        auto s = "1234567890ABASDFLKAJSDFOLKJ";
        WHEN("strcspn'd to the exclusion string")
        {
            auto res = pstd::strcspn(s, t1);
            THEN("initial run should be reported correctly")
            {
                REQUIRE(res == 10);
            }
        }
    }
    GIVEN("a source string containing no excluded characters")
    {
        auto s= "12093871928370912870129387";
        WHEN("the strings are strcspn'd")
        {
            auto res = pstd::strcspn(s, t1);
            THEN("result should be length of s")
            {
                REQUIRE(res == std::strlen(s));
            }
        }
    }
    GIVEN("a string with an exclusion on the first character")
    {
        auto s = "Cat";
        WHEN("the strings are strcspn'd")
        {
            auto res = pstd::strcspn(s, t1);
            THEN("the result is zero")
            {
                REQUIRE(res == 0);
            }
        }
    }
    GIVEN("an empty input string")
    {
        auto s = "";
        WHEN("the string is used as the search string")
        {
            auto res = pstd::strcspn(s, t1);
            THEN("the result is zero")
            {
                REQUIRE(res == 0);
            }
        }
    }
    GIVEN("an empty match string")
    {
        auto s = "What is this I am not good with computers";
        auto t2 = "";
        WHEN("The string is used as the exclusion string")
        {
            auto res = pstd::strcspn(s, t2);
            THEN("res should be the whole string")
            {
                REQUIRE(res == std::strlen(s));
            }
        }
    }
    GIVEN("null inputs")
    {
        WHEN("one input is null")
        {
            auto r1 = pstd::strcspn(nullptr, t1);
            auto r2 = pstd::strcspn(t1, nullptr);
            THEN("the result is zero")
            {
                REQUIRE(r1 == 0);
                REQUIRE(r2 == 0);
            }
        }
    }

}
TEST_CASE( "strlen", "[cstring]")
{
    REQUIRE(p::strlen("abcde") == 5);
    REQUIRE(p::strlen("abde") == 4);
    REQUIRE(p::strlen("") == 0);
    REQUIRE(p::strlen(nullptr) == 0);
}
TEST_CASE( "strlen_n", "[cstring]")
{
    REQUIRE(p::strlen_n("12345678", 10) == 8);
    REQUIRE(p::strlen_n("12345678", 4) == 4);
    REQUIRE(p::strlen_n("123123123", 0) == 0);
    REQUIRE(p::strlen_n(nullptr, 123) == 0);
}
TEST_CASE( "strpbrk", "[cstring]")
{
    auto s = "abcdEFGHijkF";
    GIVEN("an empty breakset")
    {
        auto b = "";
        WHEN("s is searched with b")
        {
            auto res = p::strpbrk(s, b);
            THEN("result should be nullptr")
            {
                REQUIRE(res == nullptr);
            }
        }
    }
    GIVEN("A single character breakset")
    {
        auto b = "E";
        WHEN("s is searched with b")
        {
            auto res = p::strpbrk(s, b);
            THEN("result should not be null")
            {
                REQUIRE(res != nullptr);
            }
            THEN("result should point to that character")
            {
                REQUIRE(res == s+4);
                REQUIRE(*res == 'E');
            }
        }
    }
    GIVEN("a single character breakset with multiple matches")
    {
        auto b = "F";
        WHEN("s is searched with b")
        {
            auto res = p::strpbrk(s, b);
            THEN("result should not be null ")
            {
                REQUIRE(res != nullptr);
            }
            THEN("result should point to first instance of character")
            {
                REQUIRE(res == s+5);
                REQUIRE(*res == 'F');
            }
        }
    }
    GIVEN("A multi-character breakset")
    {
        auto b = "EFG";
        WHEN("s is searched with b")
        {
            auto res = p::strpbrk(s, b);
            THEN("result should not be null")
            {
                REQUIRE(res != nullptr);
            }
            THEN("result should point to first matched break")
            {
                REQUIRE(res == s + 4);
                REQUIRE(*res == 'E');
            }
        }
    }
    GIVEN("a breakset containing no characters in S")
    {
        auto b = "12345";
        WHEN("s is searched with b")
        {
            auto res = p::strpbrk(s, b);
            THEN("result should be null")
            {
                REQUIRE(res == nullptr);
            }
        }
    }
    GIVEN("a null break set")
    {
        WHEN("s is searched with null")
        {
            auto res = p::strpbrk(s, nullptr);
            THEN("result should be nullptr")
            {
                REQUIRE(res == nullptr);
            }
        }
    }
    GIVEN("a null search string")
    {
        WHEN("null is searched with b")
        {
            auto res = p::strpbrk((const char*)nullptr, s);
            THEN("result should be null")
            {
                REQUIRE(res == nullptr);
            }
        }
    }
}
TEST_CASE( "strrchr", "[cstring]")
{
    auto s = "1234567891";
    GIVEN("a null string")
    {
        WHEN("null string is searched")
        {
            auto res = p::strrchr((const char*)nullptr, 'c');
            THEN("res should be null" )
            {
                REQUIRE(res == nullptr);
            }
        }
    }
    GIVEN("a character not in the string")
    {
        char c = 'a';
        WHEN("s is searched for c")
        {
            auto res = p::strrchr(s, c);
            THEN("result should be null")
            {
                REQUIRE(res == nullptr);
            }
        }
    }
    GIVEN("A character appearing twice in the string")
    {
        char c = '1';
        WHEN("s is searched with c")
        {
            auto res = p::strrchr(s, c);
            THEN("result should not be nullptr")
            {
                REQUIRE(res != nullptr);
            }
            THEN("res should point to the last occurence of c in s")
            {
                REQUIRE(res == s + 9);
                REQUIRE(*res == c);
            }
        }
    }

}
TEST_CASE( "strspn", "[cstring]")
{
    auto s = "abababcdefg";
    GIVEN("a null match string")
    {
        char* m = nullptr;
        WHEN("s is searched with m")
        {
            auto res = p::strspn(s, m);
            THEN("result should be zero")
            {
                REQUIRE(res == 0);
            }
        }
    }
    GIVEN("a match string that contains no matching characters")
    {
        auto m = "123456";
        WHEN("s is searched with m")
        {
            auto res = p::strspn(s, m);
            THEN("result should be zero")
            {
                REQUIRE(res == 0);
            }
        }
    }
    GIVEN("A match string that contains only a prefix of s")
    {
        auto m = "ab";
        WHEN("s is searched with m")
        {
            auto res = p::strspn(s, m);
            THEN("result should be length of the matching span")
            {
                REQUIRE(res == 6);
            }
        }
    }
    GIVEN("match string contains all letters in s")
    {
        auto m = "abcdefg";
        WHEN("s is searched with m")
        {
            auto res = p::strspn(s, m);
            THEN("all of s should match")
            {
                REQUIRE(res == std::strlen(s));
            }
        }
    }
    GIVEN("a null search string")
    {
        auto m = "asdf;laskdf;";
        WHEN("s is searched with m")
        {
            auto res = p::strspn(nullptr, m);
            THEN("result should be zero")
            {
                REQUIRE(res == 0);
            }
        }
    }
}
TEST_CASE( "strstr", "[cstring]")
{
    GIVEN("s is null")
    {
        char* s = nullptr;
        auto ss = "abcd";
        THEN("result should be null")
        {
            REQUIRE(p::strstr(s, ss) == nullptr);
        }
    }
    GIVEN("ss is null")
    {
        auto s = "the quick brown fox jumps over";
        char* ss = nullptr;
        THEN("result should be nullptr")
        {
            REQUIRE(p::strstr(s, ss) == nullptr);
        }
    }
    GIVEN("substring is not in s")
    {
        auto s = "abcdefghijk";
        auto ss = "eg";
        THEN("result should be nullptr");
        {
            REQUIRE(p::strstr(s, ss) == nullptr);
        }
    }
    GIVEN("substring is longer than s")
    {
        auto s = "sss";
        auto ss = "ssss";
        THEN("result should be nullptr")
        {
            REQUIRE(p::strstr(s, ss) == nullptr);
        }
    }
    GIVEN("s contains ss")
    {
        auto s = "scunthorpe scunny";
        auto ss = "cunt";

        auto res = p::strstr(s, ss);
        THEN("res should not be null")
        {
            REQUIRE(res != nullptr);
        }

        THEN("result should point to first character of substring in s")
        {
            REQUIRE(*res == *ss);
            REQUIRE(res == s + 1);
        }
        THEN("res should be equal to the substring")
        {
            REQUIRE(std::strncmp(res, ss, std::strlen(ss)) == 0);
        }
    }
    GIVEN("s contains multiple instances of ss")
    {
        auto s = "scunthorpe scunthorpe";
        auto ss = "cunt";
        auto res = p::strstr(s, ss);

        THEN("result should be not null")
        {
            REQUIRE(res != nullptr);
        }
        THEN("result should be the first substring")
        {
            REQUIRE(*res == *ss);
            REQUIRE(res == s+1);
        }
        THEN("res should be equal to ss")
        {
            REQUIRE(std::strncmp(res, ss, strlen(ss)) == 0);
        }
    }
}


