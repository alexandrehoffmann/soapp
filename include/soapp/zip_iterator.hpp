#ifndef SOAPP_ZIP_ITERATOR_HPP
#define SOAPP_ZIP_ITERATOR_HPP

#include <iterator>

#include <soapp/nth_iterator.hpp>

namespace soapp
{

template<bool is_const, typename... Items>
class zip_iterator
{
	template<typename T> using inner_iterator = std::conditional_t<is_const, typename std::vector<T>::const_iterator, typename std::vector<T>::iterator>;
	
	using core_type = tuple<inner_iterator<Items>...>;
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type        = std::conditional_t<is_const, tuple<const Items...>, tuple<Items...> >;
	using reference         = std::conditional_t<is_const, tuple<const Items&...>, tuple<Items&...> >;
	using pointer           = std::conditional_t<is_const, tuple<const Items*...>, tuple<Items*...> >;
	using difference_type   = ptrdiff_t;
	
	zip_iterator() = delete;
	zip_iterator(inner_iterator<Items>... iterators) : m_core(iterators...) {}
	zip_iterator(const zip_iterator& other) : m_core(other.m_core) {}
	
	zip_iterator& operator=(const zip_iterator& other) { m_core = other.m_core; return *this; }
	
	reference operator*() const { return dereference(); }
	
	zip_iterator& operator++()    { advance(); return *this; }
	zip_iterator  operator++(int) { zip_iterator ret(*this); advance(); return ret; }
	zip_iterator& operator--()    { step_back(); return *this; }
	zip_iterator  operator--(int) { zip_iterator ret(*this); step_back(); return ret; }
	
	zip_iterator& operator+=(const difference_type i) { advance(i);   return *this; } 
	zip_iterator& operator-=(const difference_type i) { step_back(i); return *this; }
	
	reference operator[](const difference_type i) const { return dereference(i); }
	
	friend zip_iterator  operator+(const zip_iterator&   it, const difference_type i ) { zip_iterator ret(it.m_core); return ret += i;}
	friend zip_iterator  operator+(const difference_type i,  const zip_iterator&   it) { zip_iterator ret(it.m_core); return ret += i;}
	friend zip_iterator  operator-(const zip_iterator&   it, const difference_type i ) { zip_iterator ret(it.m_core); return ret -= i;}
	
	friend difference_type operator-(const zip_iterator& lhs, const zip_iterator& rhs) { return lhs.m_core[tuple_index<0>{}] - rhs.m_core[tuple_index<0>{}]; }
			
	friend void swap(zip_iterator& lhs, zip_iterator& rhs) { std::swap(lhs.m_core, rhs.m_core); }
	friend bool operator==(const zip_iterator& lhs, const zip_iterator& rhs) { return lhs.m_core == rhs.m_core; }
	friend bool operator!=(const zip_iterator& lhs, const zip_iterator& rhs) { return lhs.m_core != rhs.m_core; }
	friend bool operator< (const zip_iterator& lhs, const zip_iterator& rhs) { return lhs.m_core <  rhs.m_core; }
	friend bool operator> (const zip_iterator& lhs, const zip_iterator& rhs) { return lhs.m_core >  rhs.m_core; }
	friend bool operator<=(const zip_iterator& lhs, const zip_iterator& rhs) { return lhs.m_core <= rhs.m_core; }
	friend bool operator>=(const zip_iterator& lhs, const zip_iterator& rhs) { return lhs.m_core >= rhs.m_core; }
private:
	template<size_t... Idxs> reference dereference_impl(                   tuple_index_seq<Idxs...>) const { return reference(*m_core[tuple_index<Idxs>{}]...);    }
	template<size_t... Idxs> reference dereference_impl(const ptrdiff_t i, tuple_index_seq<Idxs...>) const { return reference(*m_core[tuple_index<Idxs>{}][i]...); }
	
	reference dereference()                  const { return dereference_impl(   make_tuple_index_seq< std::tuple_size< core_type >::value >{}); }
	reference dereference(const ptrdiff_t i) const { return dereference_impl(i, make_tuple_index_seq< std::tuple_size< core_type >::value >{}); }
	
	void advance();
	void step_back();
	
	void advance  (const difference_type diff);
	void step_back(const difference_type diff);
	
	core_type m_core;
};
	
}

// for STL compatibility
namespace std
{
	
template<bool is_const, typename... Items>
struct iterator_traits< soapp::zip_iterator<is_const, Items...> > 
{        
	using difference_type   = typename soapp::zip_iterator<is_const, Items...>::difference_type;
	using value_type        = typename soapp::zip_iterator<is_const, Items...>::value_type;
	using reference         = typename soapp::zip_iterator<is_const, Items...>::reference;
	using pointer           = typename soapp::zip_iterator<is_const, Items...>::pointer;
	using iterator_category = typename soapp::zip_iterator<is_const, Items...>::iterator_category;
};

}

#include <soapp/zip_iterator_impl.hpp>

#endif // SOAPP_ZIP_ITERATOR_HPP
