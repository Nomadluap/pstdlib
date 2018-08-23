

#pragma once

#ifdef PSTDLIB_BUILDING_FOR_TESTING
    #define PSTDLIB_NAMESPACE pstd
#else
    #define PSTDLIB_NAMESPACE std
#endif
