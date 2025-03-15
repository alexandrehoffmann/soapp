#ifndef SOAPP_NTH_ITERATOR_HPP
#define SOAPP_NTH_ITERATOR_HPP

#include <vector>

#include <soapp/tuple_helpers/nth_value.hpp>

namespace soapp
{
	
template<size_t I, typename... Items> using nth_iterator_t               = typename std::vector< nth_value_type<I, Items...> >::iterator;
template<size_t I, typename... Items> using const_nth_iterator_t         = typename std::vector< nth_value_type<I, Items...> >::const_iterator;
template<size_t I, typename... Items> using reverse_nth_iterator_t       = typename std::vector< nth_value_type<I, Items...> >::iterator;
template<size_t I, typename... Items> using const_reverse_nth_iterator_t = typename std::vector< nth_value_type<I, Items...> >::const_reverse_iterator;

}

#endif //  SOAPP_NTH_ITERATOR_HPP
