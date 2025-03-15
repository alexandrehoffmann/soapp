#ifndef SOAPP_TUPLE_LOOP_IMPL_HPP
#define SOAPP_TUPLE_LOOP_IMPL_HPP

#include <soapp/tuple_helpers/tuple_loop.hpp>

namespace soapp
{
	
template<size_t I_START, size_t I_END, typename Function> 
constexpr Function static_for(tuple_index<I_START> i_start, tuple_index<I_END> i_end, Function&& func)
{
	if constexpr (i_start != i_end)
	{
		func(i_start);
		return static_for(tuple_index<I_START+1>{}, i_end, std::forward<Function>(func));
	}
	else 
	{
		return func;
	}
}

template<size_t I_START, size_t I_END, typename Predicate> 
constexpr size_t static_find(tuple_index<I_START> i_start, tuple_index<I_END> i_end, Predicate&& pred)
{
	if constexpr (i_start != i_end)
	{
		if (pred(i_start)) { return I_START; } 
		else               { return static_find(tuple_index<I_START+1>{}, i_end, std::forward<Predicate>(pred)); }
	}
	else 
	{
		return I_END;
	}
}

}

#endif // SOAPP_TUPLE_LOOP_IMPL_HPP
