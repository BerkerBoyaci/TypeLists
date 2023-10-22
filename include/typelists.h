#pragma once


class null_typelist {};
struct empty_type {};

template <typename ... Ts>
struct typelist {};

template <typename ... Ts>
struct transformer
{
using input_types = typelist<Ts...>;
using output_types = typelist<std::add_const_t<Ts>...>;
};


template <typename TL>
struct length;

template <template <typename...> typename TL, typename... Ts>
struct length<TL<Ts...>>
{
    using type = std::integral_constant<std::size_t, sizeof...(Ts)>;
};


template <typename TL>
using length_t = typename length<TL>::type;

template <typename TL>
constexpr std::size_t length_v = length_t<TL>::value;


template <typename TL>
struct back_type;

template <template <typename...> typename TL,typename T, typename... Ts>
struct back_type<TL<T, Ts...>>
{
    using type = back_type<TL<Ts...>>::type;
};

template <template <typename...> typename TL,typename T>
struct back_type<TL<T>>
{
    using type = T;
};

template <template <typename...> typename TL>
struct back_type<TL<>>
{
    using type = empty_type;
};

template <typename TL>
using back_t = typename back_type<TL>::type;


template <std::size_t I, std::size_t N, typename TL>
struct at_type;

template <std::size_t I, std::size_t N,template <typename...> typename TL,typename T, typename... Ts>
struct at_type<I, N, TL<T, Ts...>>
{
    using type = std::conditional_t<I == N,T,typename at_type<I, N + 1, TL<Ts...>>::type>;
};

template <std::size_t I, std::size_t N>
struct at_type<I, N, typelist<>>
{
    using type = empty_type;
};

template <std::size_t I, typename TL>
using at_t = typename at_type<I, 0, TL>::type;


template <typename TL, typename T>
struct push_back_type;

template <template <typename...> typename TL,typename T, typename... Ts>
struct push_back_type<TL<Ts...>, T>
{
    using type = TL<Ts..., T>;
};

template <typename TL, typename T>
struct push_front_type;

template <template <typename...> typename TL,typename T, typename... Ts>
struct push_front_type<TL<Ts...>, T>
{
    using type = TL<T, Ts...>;
};

template <typename TL, typename T>
using push_back_t = typename push_back_type<TL, T>::type;
template <typename TL, typename T>
using push_front_t = typename push_front_type<TL, T>::type;


template <typename TL>
struct pop_front_type;

template <template <typename...> typename TL,typename T, typename... Ts>
struct pop_front_type<TL<T, Ts...>>
{
    using type = TL<Ts...>;
};

template <template <typename...> typename TL>
struct pop_front_type<TL<>>
{
    using type = TL<>;
};

template <typename TL>
using pop_front_t = typename pop_front_type<TL>::type;



template <std::ptrdiff_t N, typename R, typename TL>
struct pop_back_type;

template <std::ptrdiff_t N, typename... Ts,typename U, typename... Us>
struct pop_back_type<N, typelist<Ts...>, typelist<U, Us...>>
{
    using type = typename pop_back_type<N - 1,typelist<Ts..., U>,typelist<Us...>>::type;
};

template <typename... Ts, typename... Us>
struct pop_back_type<0, typelist<Ts...>,
typelist<Us...>>
{
    using type = typelist<Ts...>;
};

template <typename... Ts, typename U, typename... Us>
struct pop_back_type<0, typelist<Ts...>,
typelist<U, Us...>>
{
    using type = typelist<Ts...>;
};

template <>
struct pop_back_type<-1, typelist<>, typelist<>>
{
    using type = typelist<>;
};

template <typename TL>
using pop_back_t = typename pop_back_type<static_cast<std::ptrdiff_t>(length_v<TL>)-1, typelist<>, TL>::type;