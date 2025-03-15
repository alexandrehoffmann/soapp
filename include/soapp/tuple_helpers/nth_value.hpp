#ifndef SOAPP_NTH_VALUE_HPP
#define SOAPP_NTH_VALUE_HPP

#include <cstdlib>
#include <type_traits>

#include <soapp/tuple_helpers/number_of_items.hpp>

namespace soapp
{

template<size_t I, typename FirstItem, typename... OtherItems>
struct nth_value
{
	static_assert(I < number_of_items<FirstItem, OtherItems...>::value);
	using type = typename nth_value<I-1, OtherItems...>::type;
};

template<typename FirstItem, typename... OtherItems>
struct nth_value<0, FirstItem, OtherItems...>
{
	using type = FirstItem;
};

template<size_t I, typename... Items> using       nth_value_type  = typename nth_value<I,Items...>::type;
template<size_t I, typename... Items> using const_nth_value_type  = std::add_const_t< nth_value_type<I, Items...> >;
template<size_t I, typename... Items> using       nth_rvalue_type =       nth_value_type<I, Items...>&&;
template<size_t I, typename... Items> using const_nth_rvalue_type = const_nth_value_type<I, Items...>&&; 
template<size_t I, typename... Items> using       nth_reference   =       nth_value_type<I, Items...>&;     
template<size_t I, typename... Items> using const_nth_reference   = const_nth_value_type<I, Items...>&;

}


#endif // SOAPP_NTH_VALUE_HPP
