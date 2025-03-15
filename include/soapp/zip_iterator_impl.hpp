#ifndef SOAPP_ZIP_ITERATOR_IMPL_HPP
#define SOAPP_ZIP_ITERATOR_IMPL_HPP

#include <soapp/zip_iterator.hpp>
#include <soapp/tuple_helpers/tuple_loop.hpp>

namespace soapp
{

template<bool is_const, typename... Items>
void zip_iterator<is_const, Items...>::advance()
{ 
	static_for(m_core.integral_size, [this](const auto i) 
	{
		++m_core[i];
	});
}

template<bool is_const, typename... Items>
void zip_iterator<is_const, Items...>::step_back()
{
	static_for(m_core.integral_size, [this](const auto i) 
	{
		--m_core[i];
	});
}

template<bool is_const, typename... Items>
void zip_iterator<is_const, Items...>::advance(const difference_type diff)
{
	static_for(m_core.integral_size, [this, &diff](const auto i) 
	{
		m_core[i] += diff;
	});
}

template<bool is_const, typename... Items>
void zip_iterator<is_const, Items...>::step_back(const difference_type diff)
{
	static_for(m_core.integral_size, [this, &diff](const auto i) 
	{
		m_core[i] -= diff;
	});	
}
	
}

#endif // SOAPP_ZIP_ITERATOR_IMPL_HPP
