template<typename...>
struct _Tuple {};


template<typename Head, typename... Tail>
struct _Tuple<Head, Tail...> {
    Head head;
    _Tuple<Tail...> tail;

    _Tuple() {}

    template<class H, class... Ts>
    _Tuple(H&& h, Ts&&... ts) : head
}