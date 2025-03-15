#ifndef SOAPP_NUMBER_OF_ITEMS_HPP
#define SOAPP_NUMBER_OF_ITEMS_HPP

namespace soapp
{

template<typename FirstItem, typename... OtherItems>
struct number_of_items
{
	static constexpr size_t value = 1 + number_of_items<OtherItems...>::value;
};

template<typename Item>
struct number_of_items<Item>
{
	static constexpr size_t value = 1;
};

}

#endif // SOAPP_NUMBER_OF_ITEMS_HPP
