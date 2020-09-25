#include <catch2/catch.hpp>

#include "ara/core/optional.h"

TEST_CASE("Optional can be constructed, operators =,->,*,bool, reset, has_value, value_or, comparison operators",
          "[SWS_CORE], [SWS_CORE_01033]")
{
    constexpr ara::core::Optional<int> o1;
    constexpr ara::core::Optional<int> o2(ara::core::nullopt);
    constexpr ara::core::Optional<int> o3(o2);
    constexpr ara::core::Optional<int> o4(5);

    CHECK(o1 == ara::core::nullopt);
    CHECK(o2 == ara::core::nullopt);
    CHECK(o3 == ara::core::nullopt);
    CHECK(o4 != ara::core::nullopt);

    constexpr ara::core::Optional<int> o5 = o4;
    CHECK(o5 > ara::core::nullopt);
    
    typedef struct {
        int a = 0;
        int b = 1;
    } test_struct;

    constexpr test_struct test_struct_variable;

    ara::core::Optional<test_struct> o6(test_struct_variable);

    int a = o6->a;
    int b = o6->b;
    CHECK(a == 0);
    CHECK(b == 1);
    CHECK((*o6).b == 1);

    CHECK(bool(o6) == true);
    o6.reset();
    CHECK(o6.has_value() == false);
    CHECK(o1.value_or(1) == 1);

    constexpr ara::core::Optional<int> opt_1(1);
    constexpr ara::core::Optional<int> opt_2(2);
    constexpr int value = 3;

    CHECK((opt_1 == opt_2) == false);
    CHECK((opt_1 != opt_2) == true);
    CHECK((opt_1 < opt_2) == true);
    CHECK((opt_1 > opt_2) == false);
    CHECK((opt_1 <= opt_2) == true);
    CHECK((opt_1 >= opt_2) == false);

    CHECK((opt_1 == ara::core::nullopt) == false);
    CHECK((ara::core::nullopt == opt_1) == false);
    CHECK((opt_1 != ara::core::nullopt) == true);
    CHECK((ara::core::nullopt != opt_1) == true);
    CHECK((opt_1 < ara::core::nullopt) == false);
    CHECK((ara::core::nullopt < opt_1) == true);
    CHECK((opt_1 <= ara::core::nullopt) == false);
    CHECK((ara::core::nullopt <= opt_1) == true);
    CHECK((opt_1 > ara::core::nullopt) == true);
    CHECK((ara::core::nullopt > opt_1) == false);
    CHECK((opt_1 >= ara::core::nullopt) == true);
    CHECK((ara::core::nullopt >= opt_1) == false);

    CHECK((opt_1 == value) == false);
    CHECK((value == opt_1) == false);
    CHECK((opt_1 != value) == true);
    CHECK((value != opt_1) == true);
    CHECK((opt_1 < value) == true);
    CHECK((value < opt_1) == false);
    CHECK((opt_1 <= value) == true);
    CHECK((value <= opt_1) == false);
    CHECK((opt_1 > value) == false);
    CHECK((value > opt_1) == true);
    CHECK((opt_1 >= value) == false);
    CHECK((value >= opt_1) == true);
}

TEST_CASE("Swap function", "[SWS_CORE], [SWS_CORE_01096]")
{
    ara::core::Optional<int> opt_1(1);
    ara::core::Optional<int> opt_2(2);

    ara::core::swap(opt_1, opt_2);

    CHECK(*opt_1 == 2);
    CHECK(*opt_2 == 1);
}

TEST_CASE("make_optional", "[SWS_CORE], [SWS_CORE_01033]")
{
    ara::core::Optional x = ara::core::make_optional(1);
    CHECK(*x == 1);
}
