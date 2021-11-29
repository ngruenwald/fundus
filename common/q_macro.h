#pragma once

///
/// A set of macros (QN, QC, QA) to access chains of potentially non-existent
/// member variables (e.g. std::optional, std::shared_ptr, ...).
/// The encapsulating types must be boolean testable ( if (x) ) and must allow
/// access to the contained value via pointer semantic ( x->y ).
///
/// Example:
///    struct A { std::optional<int> value; A() {} A(int v) : value{v} {} };
///    auto a = std::make_shared<A>(42);
///    auto b = std::make_shared<A>();
///    QA(-1, a, value);  // returns 42
///    QA(-1, b, value);  // returns -1
///
/// WHY? These macros currently handle a depth of up to ten parameters.
/// So you can access deeply nested "optional" parameters, e.g. when working
/// with some overly complex SOAP datatypes.
///    QA({}, GetListResult, List, ReturnEntity)
///

#ifndef __COMMON_Q_MACRO_H__474bb90644cb41f5bf2daeae7b34ddb8__
#define __COMMON_Q_MACRO_H__474bb90644cb41f5bf2daeae7b34ddb8__

/// Access chain of parameters (without capture, def must be a constant)
/// @param[in] def Default value (constant value)
/// @param[in] ... Arguments
#define QN(def, ...) \
    []() { __Q_FN(__VA_ARGS__)(def, __VA_ARGS__) }()

/// Access chain of parameters (capturing the default variable by reference)
/// @param[in] def Default value (captured variable)
/// @param[in] ... Arguments
#define QC(def, ...) \
    [&def]() { __Q_FN(__VA_ARGS__)(def, __VA_ARGS__) }()

/// Access chain of parameters (capturing all by reference)
/// @param[in] def Default value
/// @param[in] ... Arguments
#define QA(def, ...) \
    [&]() { __Q_FN(__VA_ARGS__)(def, __VA_ARGS__) }()

//
// Helper macros
//

#define ___Q00(N, D, E, ...)
#define ___Q01(N, D, E, ...) __QX(N,D,E) return *tr ## N;
#define ___Q02(N, D, E, ...) __QX(N,D,E) __Q01(D, __QP(N, __VA_ARGS__))
#define ___Q03(N, D, E, ...) __QX(N,D,E) __Q02(D, __QP(N, __VA_ARGS__))
#define ___Q04(N, D, E, ...) __QX(N,D,E) __Q03(D, __QP(N, __VA_ARGS__))
#define ___Q05(N, D, E, ...) __QX(N,D,E) __Q04(D, __QP(N, __VA_ARGS__))
#define ___Q06(N, D, E, ...) __QX(N,D,E) __Q05(D, __QP(N, __VA_ARGS__))
#define ___Q07(N, D, E, ...) __QX(N,D,E) __Q06(D, __QP(N, __VA_ARGS__))
#define ___Q08(N, D, E, ...) __QX(N,D,E) __Q07(D, __QP(N, __VA_ARGS__))
#define ___Q09(N, D, E, ...) __QX(N,D,E) __Q08(D, __QP(N, __VA_ARGS__))
#define ___Q10(N, D, E, ...) __QX(N,D,E) __Q09(D, __QP(N, __VA_ARGS__))

#define __Q00(def, expression, ...) ___Q00(00, def, expression, __VA_ARGS__)
#define __Q01(def, expression, ...) ___Q01(01, def, expression, __VA_ARGS__)
#define __Q02(def, expression, ...) ___Q02(02, def, expression, __VA_ARGS__)
#define __Q03(def, expression, ...) ___Q03(03, def, expression, __VA_ARGS__)
#define __Q04(def, expression, ...) ___Q04(04, def, expression, __VA_ARGS__)
#define __Q05(def, expression, ...) ___Q05(05, def, expression, __VA_ARGS__)
#define __Q06(def, expression, ...) ___Q06(06, def, expression, __VA_ARGS__)
#define __Q07(def, expression, ...) ___Q07(07, def, expression, __VA_ARGS__)
#define __Q08(def, expression, ...) ___Q08(08, def, expression, __VA_ARGS__)
#define __Q09(def, expression, ...) ___Q09(09, def, expression, __VA_ARGS__)
#define __Q10(def, expression, ...) ___Q10(10, def, expression, __VA_ARGS__)


#define __QF(first, ...) first
#define __QR(first, ...) __VA_ARGS__

#define __QX(N, def, expression, ...) \
    auto tr ## N = (expression); if (!tr ## N) { return (def); }

#define __QP(N, ...) \
    tr ## N -> __QF(__VA_ARGS__), __QR(__VA_ARGS__)

#define __Q_EXPAND(X) X

#define __Q_GET_NTH_ARG(                                \
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _10,   \
    N, ...) N

#define __Q_FN(...) __Q_EXPAND(__Q_GET_NTH_ARG(__VA_ARGS__, \
    __Q10, __Q09, __Q08, __Q07, __Q06, __Q05, __Q04, __Q03, __Q02, __Q01, \
    __Q00))

#endif // __COMMON_Q_MACRO_H__474bb90644cb41f5bf2daeae7b34ddb8__
