#ifndef SOAPP_ARRAY_IMPL_HPP
#define SOAPP_ARRAY_IMPL_HPP

#include <soapp/Array.hpp>

namespace soapp
{

////////////////////////////////////////////////////////////////////////

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::sub_iterator<Is...> Array<FirstItem, OtherItems...>::begin()
{
	return sub_iterator<Is...>(nth_begin<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_sub_iterator<Is...> Array<FirstItem, OtherItems...>::begin() const
{
	return const_sub_iterator<Is...>(nth_begin<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_sub_iterator<Is...> Array<FirstItem, OtherItems...>::cbegin() const
{
	return const_sub_iterator<Is...>(nth_begin<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::reverse_sub_iterator<Is...> Array<FirstItem, OtherItems...>::rbegin() 
{
	return reverse_sub_iterator<Is...>(nth_begin<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_reverse_sub_iterator<Is...> Array<FirstItem, OtherItems...>::rbegin() const
{
	return const_reverse_sub_iterator<Is...>(nth_begin<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_reverse_sub_iterator<Is...> Array<FirstItem, OtherItems...>::crbegin() const
{
	return const_reverse_sub_iterator<Is...>(nth_begin<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::sub_iterator<Is...> Array<FirstItem, OtherItems...>::end()
{
	return sub_iterator<Is...>(nth_end<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_sub_iterator<Is...> Array<FirstItem, OtherItems...>::end() const
{
	return const_sub_iterator<Is...>(nth_end<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_sub_iterator<Is...> Array<FirstItem, OtherItems...>::cend() const
{
	return const_sub_iterator<Is...>(nth_end<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::reverse_sub_iterator<Is...> Array<FirstItem, OtherItems...>::rend() 
{
	return reverse_sub_iterator<Is...>(nth_end<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_reverse_sub_iterator<Is...> Array<FirstItem, OtherItems...>::rend() const
{
	return const_reverse_sub_iterator<Is...>(nth_end<Is>()...);
}

template<typename FirstItem, typename... OtherItems> template<size_t... Is> 
typename Array<FirstItem, OtherItems...>::const_reverse_sub_iterator<Is...> Array<FirstItem, OtherItems...>::crend() const
{
	return const_reverse_sub_iterator<Is...>(nth_end<Is>()...);
}

////////////////////////////////////////////////////////////////////////

template<typename FirstItem, typename... OtherItems> template<size_t I>
nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_begin()
{
	if constexpr (I == 0) { return m_values.begin();                 }
	else                  { return m_rest.template nth_begin<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_begin() const
{
	if constexpr (I == 0) { return m_values.begin();                 }
	else                  { return m_rest.template nth_begin<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_cbegin() const
{
	if constexpr (I == 0) { return m_values.cbegin();                 }
	else                  { return m_rest.template nth_cbegin<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
reverse_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_rbegin()
{
	if constexpr (I == 0) { return m_values.rbegin();                 }
	else                  { return m_rest.template nth_rbegin<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_rbegin() const
{
	if constexpr (I == 0) { return m_values.rbegin();                 }
	else                  { return m_rest.template nth_rbegin<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_crbegin() const
{
	if constexpr (I == 0) { return m_values.crbegin();                 }
	else                  { return m_rest.template nth_crbegin<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_end()
{
	if constexpr (I == 0) { return m_values.end();                 }
	else                  { return m_rest.template nth_end<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_end() const
{
	if constexpr (I == 0) { return m_values.end();                 }
	else                  { return m_rest.template nth_end<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_cend() const
{
	if constexpr (I == 0) { return m_values.cend();                 }
	else                  { return m_rest.template nth_cend<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
reverse_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_rend()
{
	if constexpr (I == 0) { return m_values.rend();                 }
	else                  { return m_rest.template nth_rend<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_rend() const
{
	if constexpr (I == 0) { return m_values.rend();                 }
	else                  { return m_rest.template nth_rend<I-1>(); }
}

template<typename FirstItem, typename... OtherItems> template<size_t I>
const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> Array<FirstItem, OtherItems...>::nth_crend() const
{
	if constexpr (I == 0) { return m_values.crend();                 }
	else                  { return m_rest.template nth_crend<I-1>(); }
}

////////////////////////////////////////////////////////////////////////

template<typename Item> template<size_t I>
nth_iterator_t<I, Item> Array<Item>::nth_begin()
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.begin();
}

template<typename Item> template<size_t I>
const_nth_iterator_t<I, Item> Array<Item>::nth_begin() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.begin();
}

template<typename Item> template<size_t I>
const_nth_iterator_t<I, Item> Array<Item>::nth_cbegin() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.cbegin();
}

template<typename Item> template<size_t I>
reverse_nth_iterator_t<I, Item> Array<Item>::nth_rbegin()
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.rbegin();
}

template<typename Item> template<size_t I>
const_reverse_nth_iterator_t<I, Item> Array<Item>::nth_rbegin() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.rbegin();
}

template<typename Item> template<size_t I>
const_reverse_nth_iterator_t<I, Item> Array<Item>::nth_crbegin() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.crbegin();
}

template<typename Item> template<size_t I>
nth_iterator_t<I, Item> Array<Item>::nth_end()
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.end();
}

template<typename Item> template<size_t I>
const_nth_iterator_t<I, Item> Array<Item>::nth_end() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.end();
}

template<typename Item> template<size_t I>
const_nth_iterator_t<I, Item> Array<Item>::nth_cend() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.cend();
}

template<typename Item> template<size_t I>
reverse_nth_iterator_t<I, Item> Array<Item>::nth_rend()
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.rend();
}

template<typename Item> template<size_t I>
const_reverse_nth_iterator_t<I, Item> Array<Item>::nth_rend() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.rend();
}

template<typename Item> template<size_t I>
const_reverse_nth_iterator_t<I, Item> Array<Item>::nth_crend() const
{
	static_assert(I == 0, "Requested for non existant item");
	return m_values.crend();
}

}

#endif // SOAPP_ARRAY_IMPL_HPP
