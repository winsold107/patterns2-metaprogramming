//
// Created by Arina Dolgova on 25.04.2021.
//

#ifndef HW2_LINEARHIERARCHY_H
#define HW2_LINEARHIERARCHY_H

#include "../../hw1/include/TypeList.hpp"

template <class TList, template <class AtomicType, class base> class Unit, class Root = NullType>
class GenLinearHierarchy;

template <class T1, class T2, template <class, class> class Unit, class Root>
class GenLinearHierarchy<Typelist<T1, T2>, Unit, Root> :
    public Unit<T1, GetLinearHierarchy<T2, Unit, Root>> {};

template <class AtomicType, template <class, class> class Unit, class Root>
class GenLinearHierarchy<Typelist<T>, Unit, Root> :
    public Unit<AtomicType, Root> {};

#endif //HW2_LINEARHIERARCHY_H
