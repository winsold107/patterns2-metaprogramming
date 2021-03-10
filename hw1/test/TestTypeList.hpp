#include <type_traits>
#include "hw1/include/TypeList.hpp"

void testErase(){
    using TL::TypeList;
    using TL::Erase;
    using TL::Create;
    using std::is_same;
    using TL::Length;
    using TL::NullType;

    using t1 = Create<int, double, char>::result;
    using res1 = Erase<t1, int>;
    static_assert(is_same<res1::result, Create<double, char>::result>::value, "Type error");
    static_assert(Length<res1::result>::value == 2, "Length error");

    using res2 = Erase<TypeList<int, NullType>, int>;
    static_assert(is_same<res2::result, NullType>::value, "Type error");
    static_assert(Length<res2::result>::value == 0, "Length error");

    using res3 = Erase<NullType, int>;
    static_assert(is_same<res3::result, NullType>::value, "Type error");
    static_assert(Length<res3::result>::value == 0, "Length error");
}