#ifndef SOAPP_ARRAY_HPP
#define SOAPP_ARRAY_HPP

#include <vector>

#include <soapp/tuple.hpp>
#include <soapp/nth_iterator.hpp>
#include <soapp/zip_iterator.hpp>

namespace soapp
{

template<typename FirstItem, typename... OtherItems>
class Array
{
public:
	static constexpr size_t nElem = 1 + Array<OtherItems...>::nElem;
	
	using               iterator = zip_iterator<false, FirstItem, OtherItems...>;
	using         const_iterator = zip_iterator<true,  FirstItem, OtherItems...>;
	using       reverse_iterator = std::reverse_iterator< zip_iterator<false, FirstItem, OtherItems...> >;
	using const_reverse_iterator = std::reverse_iterator< zip_iterator<true,  FirstItem, OtherItems...> >;
	
	template<size_t... Is> using               sub_iterator = zip_iterator<false, nth_value_type<Is, FirstItem, OtherItems...>... >;
	template<size_t... Is> using         const_sub_iterator = zip_iterator<true,  nth_value_type<Is, FirstItem, OtherItems...>... >;
	template<size_t... Is> using       reverse_sub_iterator = std::reverse_iterator< zip_iterator<false, nth_value_type<Is, FirstItem, OtherItems...>... > >;
	template<size_t... Is> using const_reverse_sub_iterator = std::reverse_iterator< zip_iterator<true,  nth_value_type<Is, FirstItem, OtherItems...>... > >;
	
	using       reference = soapp::tuple<      FirstItem&,       OtherItems&...>;
	using const_reference = soapp::tuple<const FirstItem&, const OtherItems&...>;
	
	      reference operator[] (const size_t i)       { return random_access_impl(i, make_tuple_index_seq<nElem-1>{}); }
	const_reference operator[] (const size_t i) const { return random_access_impl(i, tuple_index_seq<nElem-1>{}); }
	
	bool   empty()         const { return m_values.empty(); }
	size_t size()          const { return m_values.size();  }
	size_t max_size()      const { return m_values.size();  }
	void   reserve()       const { m_values.reserve(); m_rest.reserve(); }
	void   capacity()      const { m_values.capacity(); }
	void   shrink_to_fit() const { m_values.shrink_to_fit(); m_rest.shrink_to_fit(); }
	
	void clear() { m_values.clear(); m_rest.clear(); }
	
	void push_back(const FirstItem& firstItem, const OtherItems&... otherItems) { m_values.push_back(firstItem); m_rest.push_back(otherItems...); }
	void push_back(FirstItem&& firstItem, OtherItems&&... otherItems)           { m_values.push_back(std::forward<FirstItem>(firstItem)); m_rest.push_back(std::forward<OtherItems>(otherItems)...); }
	
	              iterator   begin()       { return   begin_impl(make_tuple_index_seq<nElem>{}); }
	        const_iterator   begin() const { return   begin_impl(make_tuple_index_seq<nElem>{}); }
	        const_iterator  cbegin() const { return  cbegin_impl(make_tuple_index_seq<nElem>{}); }
	      reverse_iterator  rbegin()       { return  rbegin_impl(make_tuple_index_seq<nElem>{}); }
	const_reverse_iterator  rbegin() const { return  rbegin_impl(make_tuple_index_seq<nElem>{}); }
	const_reverse_iterator crbegin() const { return crbegin_impl(make_tuple_index_seq<nElem>{}); }
												 
	              iterator   end()       { return   end_impl(make_tuple_index_seq<nElem>{}); }
	        const_iterator   end() const { return   end_impl(make_tuple_index_seq<nElem>{}); }
	        const_iterator  cend() const { return  cend_impl(make_tuple_index_seq<nElem>{}); }
	      reverse_iterator  rend()       { return  rend_impl(make_tuple_index_seq<nElem>{}); }
	const_reverse_iterator  rend() const { return  rend_impl(make_tuple_index_seq<nElem>{}); }
	const_reverse_iterator crend() const { return crend_impl(make_tuple_index_seq<nElem>{}); }
	
	template<size_t... Is>               sub_iterator<Is...>   begin();
	template<size_t... Is>         const_sub_iterator<Is...>   begin() const;
	template<size_t... Is>         const_sub_iterator<Is...>  cbegin() const;
	template<size_t... Is>       reverse_sub_iterator<Is...>  rbegin();
	template<size_t... Is> const_reverse_sub_iterator<Is...>  rbegin() const;
	template<size_t... Is> const_reverse_sub_iterator<Is...> crbegin() const;
	
	template<size_t... Is>               sub_iterator<Is...>   end();
	template<size_t... Is>         const_sub_iterator<Is...>   end() const;
	template<size_t... Is>         const_sub_iterator<Is...>  cend() const;
	template<size_t... Is>       reverse_sub_iterator<Is...>  rend();
	template<size_t... Is> const_reverse_sub_iterator<Is...>  rend() const;
	template<size_t... Is> const_reverse_sub_iterator<Is...> crend() const;
	
	template<size_t I>               nth_iterator_t<I, FirstItem, OtherItems...> nth_begin();
	template<size_t I>         const_nth_iterator_t<I, FirstItem, OtherItems...> nth_begin()   const;
	template<size_t I>         const_nth_iterator_t<I, FirstItem, OtherItems...> nth_cbegin()  const;
	template<size_t I>       reverse_nth_iterator_t<I, FirstItem, OtherItems...> nth_rbegin();
	template<size_t I> const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> nth_rbegin()  const;
	template<size_t I> const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> nth_crbegin() const;
																																							 
	template<size_t I>               nth_iterator_t<I, FirstItem, OtherItems...> nth_end();
	template<size_t I>         const_nth_iterator_t<I, FirstItem, OtherItems...> nth_end()   const;
	template<size_t I>         const_nth_iterator_t<I, FirstItem, OtherItems...> nth_cend()  const;
	template<size_t I>       reverse_nth_iterator_t<I, FirstItem, OtherItems...> nth_rend();
	template<size_t I> const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> nth_rend()  const;
	template<size_t I> const_reverse_nth_iterator_t<I, FirstItem, OtherItems...> nth_crend() const;	
private:
	template<size_t... Is>               iterator   begin_impl(tuple_index_seq<Is...>)       { return   begin<Is...>(); }
	template<size_t... Is>         const_iterator   begin_impl(tuple_index_seq<Is...>) const { return   begin<Is...>(); }
	template<size_t... Is>         const_iterator  cbegin_impl(tuple_index_seq<Is...>) const { return  cbegin<Is...>(); }
	template<size_t... Is>       reverse_iterator  rbegin_impl(tuple_index_seq<Is...>)       { return  rbegin<Is...>(); }
	template<size_t... Is> const_reverse_iterator  rbegin_impl(tuple_index_seq<Is...>) const { return  rbegin<Is...>(); }
	template<size_t... Is> const_reverse_iterator crbegin_impl(tuple_index_seq<Is...>) const { return crbegin<Is...>(); }
												  
	template<size_t... Is>               iterator   end_impl(tuple_index_seq<Is...>)       { return   end<Is...>(); }
	template<size_t... Is>         const_iterator   end_impl(tuple_index_seq<Is...>) const { return   end<Is...>(); }
	template<size_t... Is>         const_iterator  cend_impl(tuple_index_seq<Is...>) const { return  cend<Is...>(); }
	template<size_t... Is>       reverse_iterator  rend_impl(tuple_index_seq<Is...>)       { return  rend<Is...>(); }
	template<size_t... Is> const_reverse_iterator  rend_impl(tuple_index_seq<Is...>) const { return  rend<Is...>(); }
	template<size_t... Is> const_reverse_iterator crend_impl(tuple_index_seq<Is...>) const { return crend<Is...>(); }

	template<size_t... Is>       reference random_access_impl(const size_t i, tuple_index_seq<Is...>)       { return       reference(m_values[i], m_rest[i][tuple_index<Is>{}]...); }
	template<size_t... Is> const_reference random_access_impl(const size_t i, tuple_index_seq<Is...>) const { return const_reference(m_values[i], m_rest[i][tuple_index<Is>{}]...); }

	std::vector<FirstItem> m_values;
	Array<OtherItems...>   m_rest;
};

template<typename Item>
class Array<Item>
{
public:
	static constexpr size_t nElem = 1;
	
	using               iterator =       nth_iterator_t<0, Item>;
	using         const_iterator = const_nth_iterator_t<0, Item>;
	using       reverse_iterator = std::reverse_iterator<       nth_iterator_t<0, Item> >;
	using const_reverse_iterator = std::reverse_iterator< const_nth_iterator_t<0, Item> >;
	
	using       reference = soapp::tuple<Item&>;
	using const_reference = const soapp::tuple<Item&>;
	
	      reference operator[] (const size_t i)       { return m_values[i]; }
	const_reference operator[] (const size_t i) const { return m_values[i]; }

	bool   empty()         const { return m_values.empty();  }
	size_t size()          const { return m_values.size();   }
	size_t max_size()      const { return m_values.size();   }
	void   reserve()       const { m_values.reserve();       }
	void   capacity()      const { m_values.capacity();      }
	void   shrink_to_fit() const { m_values.shrink_to_fit(); }
	
	void clear() { m_values.clear(); }
	
		           iterator    begin()       { return   m_values.begin(); }
	       const_iterator    begin() const { return   m_values.begin(); }
	       const_iterator   cbegin() const { return  m_values.cbegin(); }
	      reverse_iterator  rbegin()       { return  m_values.rbegin(); }
	const_reverse_iterator  rbegin() const { return  m_values.rbegin(); }
	const_reverse_iterator crbegin() const { return m_values.crbegin(); }
	
	             iterator    end()       { return   m_values.end(); }
	       const_iterator    end() const { return   m_values.end(); }
	       const_iterator   cend() const { return  m_values.cend(); }
	      reverse_iterator  rend()       { return  m_values.rend(); }
	const_reverse_iterator  rend() const { return  m_values.rend(); }
	const_reverse_iterator crend() const { return m_values.crend(); }
	
	template<size_t I> nth_iterator_t<I, Item>               nth_begin();
	template<size_t I> const_nth_iterator_t<I, Item>         nth_begin()   const;
	template<size_t I> const_nth_iterator_t<I, Item>         nth_cbegin()  const;
	template<size_t I> reverse_nth_iterator_t<I, Item>       nth_rbegin();
	template<size_t I> const_reverse_nth_iterator_t<I, Item> nth_rbegin()  const;
	template<size_t I> const_reverse_nth_iterator_t<I, Item> nth_crbegin() const;

	template<size_t I> nth_iterator_t<I, Item>               nth_end();
	template<size_t I> const_nth_iterator_t<I, Item>         nth_end()   const;
	template<size_t I> const_nth_iterator_t<I, Item>         nth_cend()  const;
	template<size_t I> reverse_nth_iterator_t<I, Item>       nth_rend();
	template<size_t I> const_reverse_nth_iterator_t<I, Item> nth_rend()  const;
	template<size_t I> const_reverse_nth_iterator_t<I, Item> nth_crend() const;

	void push_back(const Item& item) { m_values.push_back(item); }
	void push_back(Item&& item)      { m_values.push_back(item); }
private:
	std::vector<Item> m_values;
};

}

#include <soapp/Array_impl.hpp>

#endif // SOAPP_ARRAY_HPP
