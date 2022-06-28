//
// Created by Louis-gabriel Laplante on 2022-06-27.
//

#include "A.h"
#include "B.h"
#include "C.h"
#include "Base.h"

Base *generate()
{
	Base *base;
	int randNum = (rand() % 3) + 1;

	if (randNum == 1)
		base = new A();
	if (randNum == 2)
		base = new B();
	if (randNum == 3)
		base = new C();
	return base;
}

void identify(Base *p)
{
	if (dynamic_cast<A*>(p) != 0)
		std::cout << "The type of base is A !" << std::endl;
	else if (dynamic_cast<B*>(p) != 0)
		std::cout << "The type of base is B !" << std::endl;
	else if (dynamic_cast<C*>(p) != 0)
		std::cout << "The type of base in C !" << std::endl;
	else
		std::cout << "Base is of an invalid type !" << std::endl;
}

void identify(Base &p)//cant use pointers !
{
	Base &b = p;
	
	try{
		b = dynamic_cast<A&>(p);
		std::cout << "Base if of type A !" << std::endl;
	}
	catch (std::bad_cast &e) {
		std::cout << "p is not of type A !" << std::endl;
	}
	try {
		b = dynamic_cast<B&>(p);
		std::cout << "Base if of type B !" << std::endl;
	}
	catch (std::bad_cast &e) {
		std::cout << "p is not of type B !" << std::endl;
	}
	try {
		b = dynamic_cast<C&>(p);
		std::cout << "Base if of type C !" << std::endl;
	}
	catch (std::bad_cast &e) {
		std::cout << "p is not of type C !" << std::endl;
	}
}

int main()
{
	Base *base;
	srand(time(nullptr));

	base = generate();
	std::cout << "Generated a random Base." << std::endl;
	std::cout << "Guessing the type of Base via pointer..." << std::endl;
	identify(base);
	std::cout << "identifying the type of Base via reference..." << std::endl;
	identify(*base);
}