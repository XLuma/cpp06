//
// Created by Louis-gabriel Laplante on 2022-06-27.
//

#include "Data.h"
#include <iostream>
#include <sys/types.h>

uintptr_t serialize(Data *ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data *deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data *>(raw);
}

int main()
{
	Data obj;
	uintptr_t obj_ptr;
	obj.setData("Holding your data securely");

	std::cout << "Content of Data: " << obj.getData() << std::endl;
	std::cout << "Address of object obj:" << &obj << std::endl;
	std::cout << "Casting Data object to uintptr_t" << std::endl;
	obj_ptr = serialize(&obj);
	std::cout << "Reinterpreted pointer: " << std::hex << obj_ptr << std::endl;
	std::cout << "Reinterpreting pointer to object..." << std::endl;
	Data *new_obj = deserialize(obj_ptr);
	std::cout << "Content of retrieved Data: " << new_obj->getData() << std::endl;

	std::cout << "Comparing original and deserialized adresses..." << std::endl;
	if (&obj == deserialize(obj_ptr))
		std::cout << "Data retrieved successfully !" << std::endl;
	else
		std::cout << "Something went wrong. Like super bad stuff" << std::endl;

	return 0;
}