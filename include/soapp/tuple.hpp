#ifndef SOAPP_TUPLE_HPP
#define SOAPP_TUPLE_HPP

#include <soapp/tuple_helpers/typedefs.hpp>
#include <soapp/tuple_helpers/nth_value.hpp>
#include <soapp/tuple_helpers/number_of_items.hpp>
#include <utility>

namespace soapp
{
	
template<typename FirstItem, typename... OtherItems>
class tuple
{
	using value_type = FirstItem;
	using rest_type  = tuple<OtherItems...>;
public:
	static tuple_index< number_of_items<FirstItem, OtherItems...>::value > ic_size;

	tuple() = default;
	tuple(const FirstItem&  value, const OtherItems&...  rest) : m_value(value), m_rest(rest...) {}
	
	template<size_t I>       nth_reference<I, FirstItem, OtherItems...> operator[](tuple_index<I>);
	template<size_t I> const_nth_reference<I, FirstItem, OtherItems...> operator[](tuple_index<I>) const;
	
	template<size_t I>       nth_rvalue_type<I, FirstItem, OtherItems...> get();
	template<size_t I> const_nth_rvalue_type<I, FirstItem, OtherItems...> get() const;
	
	constexpr size_t size() const { return number_of_items<FirstItem, OtherItems...>::value; }
	
	bool     is_equal(const tuple& other) const { return m_value == other.m_value and m_rest.is_equal(other.m_rest);     }
	bool is_not_equal(const tuple& other) const { return m_value != other.m_value or  m_rest.is_not_equal(other.m_rest); }
	
	bool is_less         (const tuple& other) const;
	bool is_less_equal   (const tuple& other) const;
	bool is_greater      (const tuple& other) const;
	bool is_greater_equal(const tuple& other) const;
private:
	      FirstItem&& get_rvalue();
	const FirstItem&& get_rvalue() const;

	value_type m_value;
	rest_type  m_rest;
};

template<typename Item>
class tuple<Item>
{
	using value_type = Item;
public:
	static tuple_index<1> ic_size;

	tuple(const Item&  value) : m_value(value) {}
	
	template<size_t I>       nth_reference<I, Item> operator[](tuple_index<I>);
	template<size_t I> const_nth_reference<I, Item> operator[](tuple_index<I>) const;
	
	template<size_t I>       nth_rvalue_type<I, Item> get();
	template<size_t I> const_nth_rvalue_type<I, Item> get() const;
	
	constexpr size_t size() const { return number_of_items<Item>::value; }
	
	bool     is_equal(const tuple& other) const { return m_value == other.m_value; }
	bool is_not_equal(const tuple& other) const { return m_value != other.m_value; }
	
	bool is_less         (const tuple& other) const { return m_value <  other.m_value;}
	bool is_less_equal   (const tuple& other) const { return m_value <= other.m_value;}
	bool is_greater      (const tuple& other) const { return m_value >  other.m_value;}
	bool is_greater_equal(const tuple& other) const { return m_value >= other.m_value;}
private:
	      Item&& get_rvalue();
	const Item&& get_rvalue() const;
	
	value_type m_value;
};

}

template<typename... Items> inline bool operator==(const soapp::tuple<Items...>& lhs, const soapp::tuple<Items...>& rhs) { return lhs.is_equal(rhs);         }
template<typename... Items> inline bool operator!=(const soapp::tuple<Items...>& lhs, const soapp::tuple<Items...>& rhs) { return lhs.is_not_equal(rhs);     }
template<typename... Items> inline bool operator< (const soapp::tuple<Items...>& lhs, const soapp::tuple<Items...>& rhs) { return lhs.is_less(rhs);          }
template<typename... Items> inline bool operator> (const soapp::tuple<Items...>& lhs, const soapp::tuple<Items...>& rhs) { return lhs.is_greater(rhs);       }
template<typename... Items> inline bool operator<=(const soapp::tuple<Items...>& lhs, const soapp::tuple<Items...>& rhs) { return lhs.is_less_equal(rhs);    }
template<typename... Items> inline bool operator>=(const soapp::tuple<Items...>& lhs, const soapp::tuple<Items...>& rhs) { return lhs.is_greater_equal(rhs); }

// for STL compatibility
namespace std
{
	template<typename... Items>
	struct tuple_size<soapp::tuple<Items...> > : integral_constant<size_t, tuple_size< tuple<Items...> >::value > {};

	template<size_t I, typename... Items>
	struct tuple_element< I, soapp::tuple<Items...> >
	{
		using type = soapp::nth_value_type<I, Items...>;
	};
}

#include <soapp/tuple_impl.hpp>

#endif // SOAPP_TUPLE_HPP
