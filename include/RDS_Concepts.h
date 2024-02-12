#ifndef RDS_CONCEPTS_H
#define RDS_CONCEPTS_H

#include <concepts>

template <class L_t, class R_t = L_t>
concept type_has_equal_operator = requires(const L_t& left, const R_t& right) {
    {
        left == right
    } -> std::same_as<bool>;
};

#endif // RDS_CONCEPTS_H