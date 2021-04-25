//
// Created by Arina Dolgova on 25.04.2021.
//

#ifndef HW2_ABSTRACTFACTORY_H
#define HW2_ABSTRACTFACTORY_H

#include "ScatterHierarchy.h"
#include "LinearHierarchy.h"
#include "../../hw1/include/TypeList.hpp"

template<typename T>
struct TypeKeeper {};

template<class T>
class IAbstractFactoryUnit {
public:
    virtual T* create(TypeKeeper<T>) = 0;
    virtual ~IAbstractFactoryUnit() { }
};

template <class TList, template <class> class IAbstractFactoryUnit>
class IAbstractFactory: public GenScatterHierarchy<TList, IAbstractFactoryUnit> {
public:
    typedef TList ProductList;
    template <class T>
    T* create() {
        IAbstractFactoryUnit<T>& unit = *this;
        return unit.create(TypeKeeper<T>());
    }
};

template <class ConcreteProduct, class Base>
class AFRealise : public Base {
private:
    typedef typename Base::ProductList BaseProductList;
protected:
    typedef typename BaseProductList::Tail ProductList;
public:
    typedef typename BaseProductList::Head AbstractProduct;

    ConcreteProduct* create(TypeKeeper<AbstractProduct>) {
        return new ConcreteProduct;
    }
};

template <class AbstractFactory, template <class, class> class Creator = AFRealise,
        class TList = typename AbstractFactory::ProductList>
class ConcreteFactory: public GenLinearHierarchy <typename TL::Reverse<TList>::Result, Creator, AbstractFactory>
{};


#endif //HW2_ABSTRACTFACTORY_H
