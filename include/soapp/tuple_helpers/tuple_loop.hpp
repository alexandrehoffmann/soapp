#ifndef SOAPP_TUPLE_LOOP_HPP
#define SOAPP_TUPLE_LOOP_HPP

#include <soapp/tuple.hpp>
#include <soapp/tuple_helpers/typedefs.hpp>

namespace soapp
{

template<size_t I_START, size_t I_END, typename Function> constexpr Function static_for(tuple_index<I_START> i_start, tuple_index<I_END> i_end, Function&& func);
template<size_t I_START, size_t I_END, typename Predicate> constexpr size_t  static_find(tuple_index<I_START> i_start, tuple_index<I_END> i_end, Predicate&& pred);

template<size_t I_END, typename Function>  constexpr inline Function static_for (tuple_index<I_END> i_end, Function&& func)  { return static_for (tuple_index<0>{}, i_end, std::forward<Function>(func));  }
template<size_t I_END, typename Predicate> constexpr inline size_t   static_find(tuple_index<I_END> i_end, Predicate&& pred) { return static_find(tuple_index<0>{}, i_end, std::forward<Predicate>(pred)); }

}

#include <soapp/tuple_helpers/tuple_loop_impl.hpp>

#endif // SOAPP_TUPLE_LOOP_HPP
