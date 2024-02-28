/// @file NodeMangement.cpp

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

using namespace rds;
using namespace std;

namespace node_management_test
{
// clang-format off
struct DummyType
{
    DummyType() = default;
    DummyType(int a, float b): a(a), b(b) {}
    explicit DummyType(int a): a(a) {}
    auto operator==(const DummyType& other) const -> bool 
    {
        return a == other.a && b == other.b;
    }
    int a{}; float b{};
};

// clang-format on
} // namespace node_management_test

using namespace node_management_test;

/** @brief CreateNode(const Value_t&) -> Node_D* */
TEST(NodeManagement, CreateNode__const_Value_t_ref)
{
    const int node_val = 99;
    { // Nallocator
        auto* node_ptr = List<int, Nallocator>::CreateNode(node_val);

        EXPECT_EQ(node_ptr->val, node_val);
        EXPECT_EQ(node_ptr->next, nullptr);
        EXPECT_EQ(node_ptr->prev, nullptr);

        List<int, Nallocator>::DeleteNode(node_ptr);
    }
    { // Mallocator
        auto* node_ptr = List<int, Mallocator>::CreateNode(node_val);

        EXPECT_EQ(node_ptr->val, node_val);
        EXPECT_EQ(node_ptr->next, nullptr);
        EXPECT_EQ(node_ptr->prev, nullptr);

        List<int, Mallocator>::DeleteNode(node_ptr);
    }
}

/** @brief CreateNode(__CtorArgs_t&& ...)*/
TEST(NodeManagement, CreateNode__CtorArgs_t_ref_ref)
{
    auto d_0 = DummyType();
    auto d_1 = DummyType(99);
    auto d_2 = DummyType(1, 2.f);

    { // Nallocator
        {
            auto* dnode_0_ptr = List<DummyType, Nallocator>::CreateNode();
            EXPECT_EQ(dnode_0_ptr->val, d_0);
            List<DummyType, Nallocator>::DeleteNode(dnode_0_ptr);
        }
        {
            auto* dnode_1_ptr = List<DummyType, Nallocator>::CreateNode(d_1.a);
            EXPECT_EQ(dnode_1_ptr->val, d_1);
            List<DummyType, Nallocator>::DeleteNode(dnode_1_ptr);
        }
        {
            auto* dnode_2_ptr =
                List<DummyType, Nallocator>::CreateNode(d_2.a, d_2.b);
            EXPECT_EQ(dnode_2_ptr->val, d_2);
            List<DummyType, Nallocator>::DeleteNode(dnode_2_ptr);
        }
    }
    { // Mallocator
        {
            auto* dnode_0_ptr = List<DummyType, Mallocator>::CreateNode();
            EXPECT_EQ(dnode_0_ptr->val, d_0);
            List<DummyType, Mallocator>::DeleteNode(dnode_0_ptr);
        }
        {
            auto* dnode_1_ptr = List<DummyType, Mallocator>::CreateNode(d_1.a);
            EXPECT_EQ(dnode_1_ptr->val, d_1);
            List<DummyType, Mallocator>::DeleteNode(dnode_1_ptr);
        }
        {
            auto* dnode_2_ptr =
                List<DummyType, Mallocator>::CreateNode(d_2.a, d_2.b);
            EXPECT_EQ(dnode_2_ptr->val, d_2);
            List<DummyType, Mallocator>::DeleteNode(dnode_2_ptr);
        }
    }
}

RDT_END