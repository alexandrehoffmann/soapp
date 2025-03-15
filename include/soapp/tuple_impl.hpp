#ifndef SOAPP_TUPLE_IMPL_HPP
#define SOAPP_TUPLE_IMPL_HPP

#include <soapp/tuple.hpp>

namespace soapp
{

template<typename FirstItem, typename... OtherItems> 
bool tuple<FirstItem, OtherItems...>::is_less(const tuple& other) const
{
	if (m_value < other.m_value) { return true;  }
	if (m_value > other.m_value) { return false; }
	return m_rest.is_less(other.m_rest);
}

template<typename FirstItem, typename... OtherItems> 
bool tuple<FirstItem, OtherItems...>::is_less_equal(const tuple& other) const
{
	if (m_value <= other.m_value) { return true;  }
	if (m_value >= other.m_value) { return false; }
	return m_rest.is_less_equal(other.m_rest);
}

template<typename FirstItem, typename... OtherItems> 
bool tuple<FirstItem, OtherItems...>::is_greater(const tuple& other) const
{
	if (m_value > other.m_value) { return true;  }
	if (m_value < other.m_value) { return false; }
	return m_rest.is_greater(other.m_rest);
}

template<typename FirstItem, typename... OtherItems> 
bool tuple<FirstItem, OtherItems...>::is_greater_equal(const tuple& other) const
{
	if (m_value >= other.m_value) { return true;  }
	if (m_value <= other.m_value) { return false; }
	return m_rest.is_greater_equal(other.m_rest);
}

template<typename FirstItem, typename... OtherItems> template<size_t I> 
nth_reference<I, FirstItem, OtherItems...> tuple<FirstItem, OtherItems...>::operator[](tuple_index<I>)
{
	if constexpr (I == 0) { return m_value;     }
	else                  { return m_rest[std::integral_constant<size_t, I-1>{}]; }
}

template<typename FirstItem, typename... OtherItems> template<size_t I> 
const_nth_reference<I, FirstItem, OtherItems...> tuple<FirstItem, OtherItems...>::operator[](tuple_index<I>) const
{
	if constexpr (I == 0) { return m_value;     }
	else                  { return m_rest[std::integral_constant<size_t, I-1>{}]; }
}

template<typename FirstItem, typename... OtherItems> template<size_t I> 
nth_rvalue_type<I, FirstItem, OtherItems...> tuple<FirstItem, OtherItems...>::get()
{
	if constexpr (I == 0) { return get_rvalue();               }
	else                  { return m_rest.template get<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I> 
const_nth_rvalue_type<I, FirstItem, OtherItems...> tuple<FirstItem, OtherItems...>::get() const
{
	if constexpr (I == 0) { return get_rvalue();               }
	else                  { return m_rest.template get<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> 
FirstItem&& tuple<FirstItem, OtherItems...>::get_rvalue()
{
	if constexpr (std::is_reference<FirstItem>::value) { return std::forward<FirstItem>(m_value); }
	else                                               { return std::move(m_value);             	}
}

template<typename FirstItem, typename... OtherItems> 
const FirstItem&& tuple<FirstItem, OtherItems...>::get_rvalue() const
{
	if constexpr (std::is_reference<FirstItem>::value) { return std::forward<FirstItem>(m_value); }
	else                                               { return std::move(m_value);             	}
}

////////////////////////////////////////////////////////////////////////

template<typename Item> template<size_t I> nth_reference<I, Item> tuple<Item>::operator[](tuple_index<I>)
{
	static_assert(I == 0, "Index out of bounds");
	return m_value;
}

template<typename Item> template<size_t I> const_nth_reference<I, Item> tuple<Item>::operator[](std::integral_constant<size_t, I>) const
{
	static_assert(I == 0, "Index out of bounds");
	return m_value;
}

template<typename Item> template<size_t I> nth_rvalue_type<I, Item> tuple<Item>::get()
{
	static_assert(I == 0, "Index out of bounds");
	return get_rvalue();
}

template<typename Item> template<size_t I> const_nth_rvalue_type<I, Item> tuple<Item>::get() const
{
	static_assert(I == 0, "Index out of bounds");
	return get_rvalue();
}

template<typename Item>
Item&& tuple<Item>::get_rvalue()
{
	if constexpr (std::is_reference<Item>::value) { return std::forward<Item>(m_value); }
	else                                          { return std::move(m_value);          }
}

template<typename Item>
const Item&& tuple<Item>::get_rvalue() const
{
	if constexpr (std::is_reference<Item>::value) { return std::forward<Item>(m_value); }
	else                                          { return std::move(m_value);          }
}

}

#endif // SOAPP_TUPLE_IMPL_HPP
