#include <fsciolib/fixedpoint.hpp>
#include <fsciolib/fscio.hpp>

#include "test_api.hpp"

void test_fixedpoint::create_instances()
{
    {
        // Various ways to create fixed_point128
       fscio::fixed_point128<18> a(12345667);
       fscio::fixed_point128<18> b(12345667);
       fscio::fixed_point128<16> c(12345667);
       fscio_assert(b == a, "fixed_point128 instances comparison with same number of decimals");
       fscio_assert(c == a, "fixed_point128 instances with different number of decimals");
    }

    {
        // Various ways to create fixed_point64
       fscio::fixed_point64<5> a(12345667);
       fscio::fixed_point64<5> b(12345667);
       fscio::fixed_point64<5> c(12345667);
       fscio_assert(b == a, "fixed_point64 instances comparison with same number of decimals");
       fscio_assert(c == a, "fixed_point64 instances with different number of decimals");
    }

    {
        // Various ways to create fixed_point32
       fscio::fixed_point32<18> a(12345667);
       fscio::fixed_point32<18> b(12345667);
       fscio::fixed_point32<16> c(12345667);
       fscio_assert(b == a, "fixed_point32 instances comparison with same number of decimals");
       fscio_assert(c == a, "fixed_point32 instances with different number of decimals");
    }
}

void test_fixedpoint::test_addition()
{
    {
       // Various ways to create fixed_point32
       fscio::fixed_point32<0> a(100);
       fscio::fixed_point32<0> b(100);
       fscio::fixed_point32<0> c = a + b;
       fscio::fixed_point32<0> d = 200;
       fscio_assert(c == d, "fixed_point32 instances addition with zero decmimals");
    }
    {
       // Various ways to create fixed_point64
       fscio::fixed_point64<0> a(100);
       fscio::fixed_point64<0> b(100);
       fscio::fixed_point64<0> c = a + b;
       fscio::fixed_point64<0> d = 200;
       fscio_assert(c == d, "fixed_point64 instances addition with zero decmimals");
    }
};

void test_fixedpoint::test_subtraction()
{
    {
       // Various ways to create fixed_point64
       fscio::fixed_point64<0> a(100);
       fscio::fixed_point64<0> b(100);
       fscio::fixed_point64<0> c = a - b;
       fscio::fixed_point64<0> d = 0;
       fscio_assert(c == d, "fixed_point64 instances subtraction with zero decmimals");

       fscio::fixed_point64<0> a1(0);
       fscio::fixed_point64<0> c1 = a1 - b;
       fscio::fixed_point64<0> d1 = -100;
       fscio_assert(c1 == d1, "fixed_point64 instances subtraction with zero decmimals");
    }
    {
       // Various ways to create fixed_point32
       fscio::fixed_point32<0> a(100);
       fscio::fixed_point32<0> b(100);
       fscio::fixed_point32<0> c = a - b;
       fscio::fixed_point32<0> d = 0;
       fscio_assert(c == d, "fixed_point32 instances subtraction with zero decmimals");

       // Various ways to create fixed_point32
       fscio::fixed_point32<0> a1(0);
       fscio::fixed_point32<0> c1 = a1 - b;
       fscio::fixed_point32<0> d1 = -100;
       fscio_assert(c1 == d1, "fixed_point32 instances subtraction with zero decmimals");

    }
};

void test_fixedpoint::test_multiplication()
{
    {
       // Various ways to create fixed_point64
       fscio::fixed_point64<0> a(100);
       fscio::fixed_point64<0> b(200);
       fscio::fixed_point128<0> c = a * b;
       fscio::fixed_point128<0> d(200*100);
       fscio_assert(c == d, "fixed_point64 instances multiplication result in fixed_point128");
    }

    {
       // Various ways to create fixed_point32
       fscio::fixed_point32<0> a(100);
       fscio::fixed_point32<0> b(200);
       fscio::fixed_point64<0> c = a * b;
       fscio::fixed_point64<0> d(200*100);
       fscio_assert(c == d, "fixed_point32 instances multiplication result in fixed_point64");
    }
}

void test_fixedpoint::test_division()
{
    {
        uint64_t lhs = 10000000;
        uint64_t rhs = 333;

        fscio::fixed_point64<0> a((int64_t)lhs);
        fscio::fixed_point64<0> b((int64_t)rhs);
        fscio::fixed_point128<5> c = a / b;

        fscio::fixed_point128<5> e = fscio::fixed_divide<5>(lhs, rhs);
        print(e);
        fscio_assert(c == e, "fixed_point64 instances division result from operator and function and compare in fixed_point128");

    }

    {
        uint32_t lhs = 100000;
        uint32_t rhs = 33;

        fscio::fixed_point32<0> a((int32_t)lhs);
        fscio::fixed_point32<0> b((int32_t)rhs);
        fscio::fixed_point64<5> c = a / b;

        fscio::fixed_point64<5> e = fscio::fixed_divide<5>(lhs, rhs);
        fscio_assert(c == e, "fixed_point64 instances division result from operator and function and compare in fixed_point128");

    }
}

void test_fixedpoint::test_division_by_0()
{
    {
        uint64_t lhs = 10000000;
        uint64_t rhs = 0;

        fscio::fixed_point64<0> a((int64_t)lhs);
        fscio::fixed_point64<0> b((int64_t)rhs);

        fscio::fixed_point128<5> e = fscio::fixed_divide<5>(lhs, rhs);
        // in order to get rid of unused parameter warning
        e = 0;
        fscio_assert(false, "should've thrown an error");

    }

 }
