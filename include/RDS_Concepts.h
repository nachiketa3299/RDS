/// @file RDS_Concepts.h

#ifndef RDS_CONCEPTS_H
#define RDS_CONCEPTS_H

#include "RDS_CoreDefs.h"
#include <concepts>

RDS_BEGIN

/// @brief 배열 원소의 형식에 대한 필요 사항: Default Constructible 해야 하며, 크기는 0
/// 이상이어야 함.
template <class T_t>
concept ArrayRequirement = std::default_initializable<T_t>;

template <class L_t, class R_t = L_t>
concept type_has_equal_operator = requires(const L_t& left, const R_t& right) {
    {
        left == right
    } -> std::same_as<bool>;
};

RDS_END

#endif // RDS_CONCEPTS_H