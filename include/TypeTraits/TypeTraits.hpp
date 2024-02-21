#ifndef RDS_TYPE_TRAITS_HPP
#define RDS_TYPE_TRAITS_HPP

#include <type_traits>

#include "RDS_CoreDefs.h"

RDS_BEGIN

// clang-format off
// see https://en.cppreference.com/w/cpp/header/type_traits

#pragma region HELPER_CLASSES

template <class T_t, T_t v>
struct Integral_Constant
{ 
public:
    using Value_t = T_t;
    using Type = Integral_Constant;
public:
    constexpr operator Value_t() const noexcept { return Value; }
    constexpr auto operator()() const noexcept -> Value_t { return Value; }
public:
    static constexpr Value_t Value = v;
};

template<bool B> using Bool_Constant = Integral_Constant<bool, B>;
template<bool B> using Bool_Constant_t = typename Bool_Constant<B>::Type;
template<bool B> inline constexpr bool Bool_Constant_v = Bool_Constant<B>::Value;

using True_t  = Bool_Constant<true>;
using False_t = Bool_Constant<false>;

#pragma endregion HELPER_CLASSES

RDS_END
#endif

/*

#pragma region PRIMARY_TYPE_CATEGORIES

template <class T_t> struct Is_Void: Is_Same<void, Remove_Const_Volatile_t<T_t>> {};
template <class T_t> using Is_Void_t = typename Is_Void<T_t>::Type;
template <class T_t> using Is_Void_v = Is_Void<T_t>::Value;

template <class T_t>
struct Is_Null_Pointer;

template <class T_t>
struct Is_Floating_Point;

template <class T_t>
struct Is_Array;

template <class T_t>
struct Is_Enum;

template <class T_t>
struct Is_Union: public std::is_union<T_t> 
{
    using Value = std::is_union<T_t>::value;
    using Val_t = std::is_union<T_t>::value_type;
    operator bool() const noexcept { return Value; }
    auto operator()() const noexcept -> Value { return Value; }
};

template <class T_t>
struct Is_Class;

template <class T_t>
struct Is_Function;

template <class T_t>
struct Is_Pointer;

template <class T_t>
struct Is_LValue_Reference;

template <class T_t>
struct Is_RValue_Reference;

template <class T_t>
struct Is_Member_Object_Pointer;

template <class T_t>
struct Is_Member_Function_Pointer;

#pragma endregion PRIMARY_TYPE_CATEGORIES

#pragma region COMPOSITE_TYPE_CATEGORIES

#pragma endregion COMPOSITE_TYPE_CATEGORIES

#pragma region TYPE_RELATIONSHIPS

template <class T_t, class U_t>
struct Is_Same : False_t{};

template <class T_t>
struct Is_Same<T_t, T_t> : True_t{};

template <class T_t, class U_t>
inline constexpr bool Is_Same_v = Is_Same<T_t, U_t>::Value;

#pragma endregion TYPE_RELATIONSHIPS


#pragma region CONST_VOLATILITY_SPCECIFIERS

template <class T_t> struct Remove_Const { using Type = T_t; };
template <class T_t> struct Remove_Const<const T_t> { using Type = T_t; };
template <class T_t> using  Remove_Const_t = typename Remove_Const<T_t>::Type;

template <class T_t> struct Remove_Volatile {using Type = T_t;};
template <class T_t> struct Remove_Volatile<volatile T_t> {using Type = T_t;};
template <class T_t> using  Remove_Volatile_t = typename Remove_Volatile<T_t>::Type;

template <class T_t> struct Remove_Const_Volatile { using Type = T_t;};
template <class T_t> struct Remove_Const_Volatile<const T_t> {using Type = T_t;};
template <class T_t> struct Remove_Const_Volatile<volatile T_t> {using Type = T_t;};
template <class T_t> struct Remove_Const_Volatile<const volatile T_t> {using Type = T_t;};
template <class T_t> using  Remove_Const_Volatile_t = typename Remove_Const_Volatile<T_t>::Type;

template <class T_t> struct Add_Const { using Type = const T_t; };
template <class T_t> using  Add_Const_t = typename Add_Const<T_t>::Type;

template <class T_t> struct Add_Volatile { using Type = volatile T_t; };
template <class T_t> using  Add_Volatile_t = typename Add_Volatile<T_t>::Type;

template <class T_t> struct Add_Const_Volatile { using Type = const volatile T_t; };
template <class T_t> using  Add_Const_Volatile_t = typename Add_Const_Volatile<T_t>::Type;

#pragma endregion CONST_VOLATILITY_SPCECIFIERS

#pragma region MISCELLANEOUS TRANSFORMATIONS

template <class T_t> struct Type_Identity { using Type = T_t; };
template <class T_t> using  Type_Identity_t = typename Type_Identity<T_t>::Type;

#pragma endregion MISCELLANEOUS TRANSFORMATIONS

#pragma region REFERENCES

template <class T_t> struct Remove_Reference { using Type = T_t; };
template <class T_t> struct Remove_Reference<T_t&> { using Type = T_t; };
template <class T_t> struct Remove_Reference<T_t&&> { using Type = T_t; };
template <class T_t> using  Remove_Reference_t = typename Remove_Reference<T_t>::Type;

namespace details 
{
    template <class T_t> auto Try_Add_LValue_Reference(int) -> Type_Identity_t<T_t&>;
    template <class T_t> auto Try_Add_LValue_Reference(...) -> Type_Identity_t<T_t>;
    template <class T_t> auto Try_Add_RValue_Reference(int) -> Type_Identity_t<T_t&&>;
    template <class T_t> auto Try_Add_RValue_Reference(...) -> Type_Identity_t<T_t>;
}; // namespace details

template <class T_t> struct Add_LValue_Reference: 
    public decltype(details::Try_Add_LValue_Reference<T_t>(0)) {};
template <class T_t> struct Add_RValue_Reference: 
    public decltype(details::Try_Add_RValue_Reference<T_t>(0)) {};

#pragma endregion REFERENCES

template <class T_t, class U_t>
concept Same_as_h = Is_Same_v<T_t, U_t>;

template <class Left_t, class Right_t>
concept Same_as = Same_as_h<Left_t, Right_t> && Same_as_h<Right_t, Left_t>;


RDS_END


#endif // RDS_TYPE_TRAITS_HPP
*/