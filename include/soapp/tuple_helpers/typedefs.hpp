#ifndef SOAPP_TUPLE_TYPEDEFS_HPP
#define SOAPP_TUPLE_TYPEDEFS_HPP

#include <cstdlib>
#include <type_traits>
#include <utility>

namespace soapp
{
	
template<size_t I>     using tuple_index          = std::integral_constant<size_t, I>;
template<size_t... Is> using tuple_index_seq      = std::integer_sequence<size_t, Is...>;
template<size_t N>     using make_tuple_index_seq = std::make_index_sequence<N>;

}

#endif // SOAPP_TUPLE_TYPEDEFS_HPP
