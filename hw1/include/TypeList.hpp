namespace TL {
    class NullType{};

    //init
    template<typename T, typename U>
    struct TypeList{
        using Head = T;
        using Tail = U;
    };

    //creation
    template<typename T, typename ... Types>
    struct Create{
        using result = TypeList<T, typename Create<Types...>::result>;
    };

    template<typename T>
    struct Create<T>{
        using result = TypeList<T, NullType>;
    };

    //length
    template<class TypeList>
    struct Length;

    template<>
    struct Length<NullType>{
      enum { value = 0 };
    };

    template<class Head, class Tail>
    struct Length<TypeList<Head, Tail>>{
      enum { value = 1 + Length<Tail>::value };
    };

    //index access
    template<class TypeList, unsigned int index> struct TypeAt;

    template<class Head, class Tail>
    struct TypeAt<TypeList<Head, Tail>, 0>{
        using result = Head;
    };

    template<class Head, class Tail, unsigned int index>
    struct TypeAt<TypeList<Head, Tail>, index>{
        using result = typename TypeAt<Tail, index-1>::result;
    };

    //erase
    template <class TList, class T>
    struct Erase {
        using result = TypeList<typename TList::Head,
            typename Erase<typename TList::Tail, T>::type>;
    };

    template <class T>
    struct Erase<NullType, T> {
        using result = NullType;
    };

    template <class T, class Tail>
    struct Erase<TypeList<T, Tail>, T> {
        using result = Tail;
    };

    //index of type
    template<class TypeList, class T>
    struct IndexOf;

    template<class Head, class Tail, class T>
    struct IndexOf<TypeList<Head, Tail>, T>{
    private:
        enum {
            temp = IndexOf<Tail, T>::value
        };
    public:
        enum {
            value = temp == -1 ? -1 : 1+temp
        };
    };

    template<class T, class Tail>
    struct IndexOf<TypeList<T, Tail>, T>{
        enum {
            value = 0
        };
    };

    template<class T>
    struct IndexOf<NullType, T>{
        enum {
            value = -1
        };
    };

    //append
    template<class TypeList, class T>
    struct Append;

    template<class T>
    struct Append<NullType, T>{
        using result = typename Create<T>::result;
    };

    template<class Head, class Tail, class T>
    struct Append<TypeList<Head, Tail>, T> {
        using result = TypeList<Head, typename Append<Tail, T>::result>;
    };
}