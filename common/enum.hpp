#pragma once

// Helper macros for easier enum creation (using the ENUMS macro)
//
// ## ENUM
// The ENUM macro auto generates the string representations
// from the given enumerators.
// e.g. ENUM(FooBar, Foo, Bar)
//        -> ENUMS(FooBar, ENUMARGS(Foo, Bar), ENUMARGS("Foo", "Bar"))
//
// ## ENUMs
// The ENUMs macro is almost the same as the original ENUMS macro.
// It just frees you from using quotes when defininig the strings.
// e.g. ENUMs(FooBar, ENUMARGS(Foo, Bar), ENUMARGS(foo, bar))
//        -> ENUMS(FooBar, ENUMARGS(Foo, Bar), ENUMARGS("foo", "bar"))
//

#include "enums.hpp"

#define ENUM(NAME, ...) \
    ENUMS(NAME, ENUMARGS(__VA_ARGS__), __ENUM_STRINGS_CONV(__VA_ARGS__))

#define ENUMs(NAME, VALUES, STRINGS) \
    ENUMS(NAME, ENUMARGS(VALUES), __ENUM_STRINGS_CONV(STRINGS))

//
// NOTE:
// these macros support up to 30 enumerations.
// if you need more, you have to extend them,
// or you will get some nasty error messages.
//

#define __ENUM_STR00(...)

#define __ENUM_STR01(A, ...) __ENUM_STRIZ(A)
#define __ENUM_STR02(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR01(__VA_ARGS__))
#define __ENUM_STR03(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR02(__VA_ARGS__))
#define __ENUM_STR04(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR03(__VA_ARGS__))
#define __ENUM_STR05(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR04(__VA_ARGS__))
#define __ENUM_STR06(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR05(__VA_ARGS__))
#define __ENUM_STR07(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR06(__VA_ARGS__))
#define __ENUM_STR08(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR07(__VA_ARGS__))
#define __ENUM_STR09(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR08(__VA_ARGS__))
#define __ENUM_STR10(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR09(__VA_ARGS__))

#define __ENUM_STR11(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR10(__VA_ARGS__))
#define __ENUM_STR12(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR11(__VA_ARGS__))
#define __ENUM_STR13(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR12(__VA_ARGS__))
#define __ENUM_STR14(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR13(__VA_ARGS__))
#define __ENUM_STR15(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR14(__VA_ARGS__))
#define __ENUM_STR16(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR15(__VA_ARGS__))
#define __ENUM_STR17(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR16(__VA_ARGS__))
#define __ENUM_STR18(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR17(__VA_ARGS__))
#define __ENUM_STR19(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR18(__VA_ARGS__))
#define __ENUM_STR20(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR19(__VA_ARGS__))

#define __ENUM_STR21(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR20(__VA_ARGS__))
#define __ENUM_STR22(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR21(__VA_ARGS__))
#define __ENUM_STR23(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR22(__VA_ARGS__))
#define __ENUM_STR24(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR23(__VA_ARGS__))
#define __ENUM_STR25(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR24(__VA_ARGS__))
#define __ENUM_STR26(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR25(__VA_ARGS__))
#define __ENUM_STR27(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR26(__VA_ARGS__))
#define __ENUM_STR28(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR27(__VA_ARGS__))
#define __ENUM_STR29(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR28(__VA_ARGS__))
#define __ENUM_STR30(A, ...) __ENUM_STRIZ(A), __ENUM_EXPAND(__ENUM_STR29(__VA_ARGS__))

#define __ENUM_STRIZ(X) #X
#define __ENUM_EXPAND(X) X

#define __ENUM_GET_NTH_ARG( \
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _10, \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
    N, ...) N

#define __ENUM_STRINGS_CONV(...) \
    __ENUM_EXPAND( \
        __ENUM_GET_NTH_ARG(__VA_ARGS__, \
            __ENUM_STR30, __ENUM_STR29, __ENUM_STR28, __ENUM_STR27, __ENUM_STR26, \
            __ENUM_STR25, __ENUM_STR24, __ENUM_STR23, __ENUM_STR22, __ENUM_STR21, \
            __ENUM_STR20, __ENUM_STR19, __ENUM_STR18, __ENUM_STR17, __ENUM_STR16, \
            __ENUM_STR15, __ENUM_STR14, __ENUM_STR13, __ENUM_STR12, __ENUM_STR11, \
            __ENUM_STR10, __ENUM_STR09, __ENUM_STR08, __ENUM_STR07, __ENUM_STR06, \
            __ENUM_STR05, __ENUM_STR04, __ENUM_STR03, __ENUM_STR02, __ENUM_STR01, \
            __ENUM_STR00 \
        )(__VA_ARGS__) \
    )
