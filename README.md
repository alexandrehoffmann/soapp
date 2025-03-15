# soapp (Struct Of Array Plus Plus)

soapp is a small header only library that provide a STL style array and some tools for tuple manipulation. 

## soapp internal tuple structure

`soapp::tuple` works in a similar manner as std::tuple. In our example we are going to create a tuple that represents a person:
```cpp
#include <soapp/tuple.hpp>
#include <soapp/tuple_helpers/tuple_loop.hpp>

#include <Gender.hpp>

#include <iostream>

int main()
{
  soapp::tuple<std::string, std::string, int, Gender> person("Lucas", "Bennett", 29, Gender::MALE);
```

We provide a simple interface to iterate through our tuple:
```cpp
  // you can iterate through the items of a tuple
  soapp::static_for(person.integral_size, [&person](const auto i) -> void
  {
    std::cout << person[i] << " ";
  });
  std::cout << std::endl;
```

`static_for` takes a `soapp::tuple_index<I_EN>`, which is an alias of `std::integral_constant<size_t, I>`, and a functor. 
The functor is called with `soapp::tuple_index<I>` with I=0, 1, ..., I_END-1.
Our tuple type has a random access operator that takes a `soapp::tuple_index<I>` and return the Ith element by reference.

One can allso access a tuple via the `get<I>` method:
```cpp
enum PersonAttribute : int
{
  FISRT_NAME = 0,
  LAST_NAME  = 1,
  AGE        = 2,
  GENDER     = 3
};

  std::cout << person.get<PersonAttribute::FISRT_NAME>() << " " << person.get<PersonAttribute::LAST_NAME>() << ", " << person.get<PersonAttribute::GENDER>() 
            << ", " << person.get<PersonAttribute::AGE>() << " years old" << std::endl; 
```

Alternatively, a tuple can be binded:
```cpp
  auto& [first_name, last_name, age, gender] = person;
  std::cout << first_name << ", " << last_name << ", " << gender << ", " << age << " years old" << std::endl;
```

## soapp Array and iterators

Soapp provides an `Array` structure that stores each item using the SOA order:
```cpp
  ArrayOfPersons persons;
	
  persons.push_back("Lucas", "Bennett", 34, Gender::MALE);
  persons.push_back("Ava", "Carter", 27, Gender::FEMALE);
  persons.push_back("Noah", "Ramirez", 41, Gender::FEMALE);
  persons.push_back("Riley", "Monroe", 29, Gender::NON_BINARY);
```

We can iterate thought the `Array` using C-style loops:
```cpp
  for (size_t i=0;i<persons.size();++i)
  {
    auto [first_name, last_name, age, gender] = persons[i];
    std::cout << "person " << i+1 << " : " << first_name << " " << last_name << ", " << gender << ", " << age << " years old " << std::endl;
    age += 5;
  }
```

We can aslo iterate through a single item using the `nth_begin<I>` method:
```cpp
for (auto it=persons.nth_begin<PersonAttribute::GENDER>(); it!=persons.nth_end<PersonAttribute::GENDER>(); ++it)
{
  std::cout << "Gender of the person : " << *it << std::endl;
}
```

We can iterate through multiple items using the `begin<Is...>` method:
```cpp
for (auto it=persons.begin<PersonAttribute::FISRT_NAME, PersonAttribute::AGE>(); it!=persons.end<PersonAttribute::FISRT_NAME, PersonAttribute::AGE>(); ++it)
{
  const auto [first_name, age] = *it;
  std::cout << first_name << " is " << age << " years old" << std::endl;
}
```

And, of course, we can iterate through all items simultaneously:
```cpp
for (auto it=persons.begin(); it!=persons.end(); ++it)
{
  auto [first_name, last_name, age, gender] = *it;
  std::cout << "person " << std::distance(persons.begin(), it) << " : " << first_name << " " << last_name << ", " << gender << ", " << age << " years old " << std::endl;
}
```
