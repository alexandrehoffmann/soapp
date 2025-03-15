#include <soapp/Array.hpp>
#include <ostream>

#include <Gender.hpp>

#include <iostream>

using ArrayOfPersons = soapp::Array<std::string, std::string, int, Gender>;

enum PersonAttribute : int
{
	FISRT_NAME = 0,
	LAST_NAME  = 1,
	AGE        = 2,
	GENDER     = 3
};

#include <iostream>

int main()
{
	ArrayOfPersons persons;
	
	persons.push_back("Lucas", "Bennett", 34, Gender::MALE);
	persons.push_back("Ava", "Carter", 27, Gender::FEMALE);
	persons.push_back("Noah", "Ramirez", 41, Gender::FEMALE);
	persons.push_back("Riley", "Monroe", 29, Gender::NON_BINARY);
	
	// we can iterate like a normal array
	// let's age our persons
	for (size_t i=0;i<persons.size();++i)
	{
		auto [first_name, last_name, age, gender] = persons[i];
		std::cout << "person " << i+1 << " : " << first_name << " " << last_name << ", " << gender << ", " << age << " years old " << std::endl;
		age += 5;
	}
	std::cout << "5 years have past" << std::endl;
	for (size_t i=0;i<persons.size();++i)
	{
		auto [first_name, last_name, age, gender] = persons[i];
		std::cout << "person " << i+1 << " : " << first_name << " " << last_name << ", " << gender << ", " << age << " years old " << std::endl;
	}
	
	// we can iterate through an item with begin<I> and end<I> 
	
	for (auto it=persons.nth_begin<PersonAttribute::GENDER>(); it!=persons.nth_end<PersonAttribute::GENDER>(); ++it)
	{
		std::cout << "Gender of the person : " << *it << std::endl;
	}
	
	// We can also iterate through two items with two iterators
	
	auto it_firstname = persons.nth_begin<PersonAttribute::FISRT_NAME>();
	for (auto it_age=persons.nth_begin<PersonAttribute::AGE>(); it_age!=persons.nth_end<PersonAttribute::AGE>(); ++it_age, ++it_firstname)
	{
		std::cout << *it_firstname << " is " << *it_age << " years old" << std::endl;
	}
	
	// We can bind theses two iterators
	for (auto it=persons.begin<PersonAttribute::FISRT_NAME, PersonAttribute::AGE>(); it!=persons.end<PersonAttribute::FISRT_NAME, PersonAttribute::AGE>(); ++it)
	{
		const auto [first_name, age] = *it;
		std::cout << first_name << " is " << age << " years old" << std::endl;
	}
	// we can off-course, iterate through the whole tuple
	for (auto it=persons.begin(); it!=persons.end(); ++it)
	{
		auto [first_name, last_name, age, gender] = *it;
		std::cout << "person " << std::distance(persons.begin(), it) << " : " << first_name << " " << last_name << ", " << gender << ", " << age << " years old " << std::endl;
	}
	
	return EXIT_SUCCESS;
}
