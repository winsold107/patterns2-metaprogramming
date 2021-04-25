//
// Created by Arina Dolgova on 25.04.2021.
//

#ifndef HW2_SCATTERHIERARCHY_H
#define HW2_SCATTERHIERARCHY_H

#include "../../hw1/include/TypeList.hpp"

template <class TList, template <class> class Unit>
class GenScatterHierarchy;

template <class T1, class T2, template <class> class Unit>
class GenScatterHierarchy<TypeList<T1, T2>, Unit>:
    public GenScatterHierarchy<T1, Unit>,
    public GenScatterHierarchy<T2, Unit> {
public:
    using TList = TypeList<T1, T2>;
    using LeftBase = GenScatterHierarchy<T1, Unit>;
    using RightBase = GenScatterHierarchy<T2, Unit>;
};

template <class AtomicType, template <class> class Unit>
class GenScatterHierarchy: public Unit<AtomicType> {
public:
    using LeftBase = Unit<AtomicType>;
};

template <template <class> class Unit>
class GenScatterHierarchy<NullType, Unit> {};

#endif //HW2_SCATTERHIERARCHY_H
