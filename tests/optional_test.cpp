#include <catch2/catch.hpp>

#include "ara/core/optional.h"

TEST_CASE("Optional can be constructed",
          "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Optional<int> opt;

    CHECK(opt == std::nullopt);
}

TEST_CASE("Optional can be constructed2",
          "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Optional<int> opt;

    CHECK(opt == std::nullopt);
}

TEST_CASE("Optional can be constructed3",
          "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Optional<int> opt;

    CHECK(opt == std::nullopt);
}