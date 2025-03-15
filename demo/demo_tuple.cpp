#include <soapp/tuple.hpp>
#include <soapp/tuple_helpers/tuple_loop.hpp>

#include <Gender.hpp>

#include <iostream>

enum PersonAttribute : int
{
FISRT_NAME = 0,
LAST_NAME  = 1,
AGE        = 2,
GENDER     = 3
};

int main()
{
	soapp::tuple<std::string, std::string, int, Gender> person("Lucas", "Bennett", 29, Gender::MALE);

	// you can iterate through the items of a tuple
	soapp::static_for(person.integral_size, [&person](const auto i) -> void
	{
		std::cout << person[i] << " ";
	});
	std::cout << std::endl;

	// you can select the items individually
	std::cout << person.get<PersonAttribute::FISRT_NAME>() << " " << person.get<PersonAttribute::LAST_NAME>() << ", " << person.get<PersonAttribute::GENDER>() 
	<< ", " << person.get<PersonAttribute::AGE>() << " years old" << std::endl; 
	// you can also bind the items of the tuple
	auto& [first_name, last_name, age, gender] = person;
	std::cout << first_name << ", " << last_name << ", " << gender << ", " << age << " years old" << std::endl;

	// let's modify our tuple
	// we can do it via structure binding
	gender = Gender::NON_BINARY;
	// via the get function
	person.get<PersonAttribute::FISRT_NAME>() = "Reiley";
	// and via the [] operator 
	person[soapp::tuple_index<PersonAttribute::LAST_NAME>{}] = "Monroe";
	
	soapp::static_for(person.integral_size, [&person](const auto i) -> void
	{
		std::cout << person[i] << " ";
	});
	std::cout << std::endl;
	
	return 0;
}
