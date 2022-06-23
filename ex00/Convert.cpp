//
// Created by Louis-gabriel Laplante on 2022-06-21.
//

#include "Convert.h"

Convert::Convert() {
	i_arg = 0;
	d_arg = 0;
	f_arg = 0;
	isWrong = false;
	c_arg = 0;
	type = INVALID;
	def = "";
}

Convert::Convert(const Convert &convert) {
	i_arg = convert.i_arg;
	d_arg = convert.d_arg;
	f_arg = convert.f_arg;
	c_arg = convert.c_arg;
	isWrong = convert.isWrong;
	type = convert.type;
	def = convert.def;
}

Convert & Convert::operator=(const Convert &rhs) {
	if (this == &rhs)
		return *this;
	this->i_arg = rhs.i_arg;
	this->d_arg = rhs.d_arg;
	this->f_arg = rhs.f_arg;
	this->c_arg = rhs.c_arg;
	this->isWrong = rhs.isWrong;
	this->type = rhs.type;
	this->def = rhs.def;
	return *this;
}

Convert::~Convert(){

}

void Convert::detect_type(char *arg)
{
	int i = 0;
	int has_dot = 0;
	int has_f = 0;
	int has_letter = 0;
	int has_num = 0;
	int has_neg = 0;
	this->setDef(std::string(arg));

	if (isLiteral(this->def) == true)
	{
		this->setType(PSEUDOLIT);
		return;
	}
	while(arg[i])
	{
		if (arg[i] == '-' && i == 0)
			has_neg = 1;
		if (std::isdigit(arg[i]))
			has_num = 1;
		if (arg[i] == '.')
			has_dot = 1;
		if (arg[i] == 'f' && i == (int)std::strlen(arg) - 1)
			has_f = 1;
		if (std::isalpha(arg[i]))
			has_letter = 1;
		i++;
	}
	if (has_num == 1 && has_dot == 1 && has_f == 1) {
		this->setType(FLOAT);
		//this->setFArg(std::stof(this->def));
		this->f_arg = std::stof(this->def);
	}
	else if (has_num == 1 && has_dot == 1 && has_f == 0) {
		this->setType(DOUBLE);
		//this->setDArg(std::stod(this->def));
		this->d_arg = std::stod(this->def);
	}
	else if (has_num == 1 && has_dot == 0 && has_f == 0 && has_letter == 0) {
		this->setType(INT);
		//this->setIArg(std::stoi(this->def));
		if (std::stol(this->def) >= INT_MIN && std::stol(this->def) <= INT_MAX) {
			this->i_arg = std::stoi(this->def);
			this->c_arg = this->i_arg;
		}
		else
			this->isWrong = true;
	}
	else
		this->setType(INVALID);
}

void Convert::convert_data()
{
	switch(this->getType())
	{
		case FLOAT:
			this->c_arg = static_cast<char>(this->f_arg);
			this->d_arg = static_cast<double>(this->f_arg);
			this->i_arg = static_cast<int>(this->f_arg);
			break;
		case INT:
			this->f_arg = static_cast<float>(this->i_arg);
			std::cout << std::stof(this->def) << std::endl;
			this->c_arg = static_cast<char>(this->i_arg);
			this->d_arg = static_cast<double>(this->i_arg);
			break;
		case DOUBLE:
			this->c_arg = static_cast<char>(this->d_arg);
			this->f_arg = static_cast<float>(this->d_arg);
			this->i_arg = static_cast<int>(this->d_arg);
			break;
		case CHAR:
			this->i_arg = static_cast<int>(this->c_arg);
			this->d_arg = static_cast<double>(this->c_arg);
			this->f_arg = static_cast<float>(this->c_arg);
			break;
		default:
			break;
	}

}

void Convert::getIArg() const {
	std::cout << "int: ";
	if (this->type == PSEUDOLIT)
		std::cout << "impossible" << std::endl;
	else if (this->isWrong == true)
		std::cout << "overflow" << std::endl;
	else if (stoi(this->def) < INT_MIN || stoi(this->def) > INT_MAX)
		std::cout << "overflow" << std::endl;
	else
		std::cout << this->i_arg << std::endl;
}

void Convert::getFArg() const {
	std::cout << "float: ";
	if (this->type == PSEUDOLIT) {
		if (this->def == "-inf" || this->def == "inf")
			std::cout << this->def << "f" << std::endl;
		else
			std::cout << this->def << std::endl;
	}
	//else if (this->type == INT || this->type == DOUBLE)
	//{
	//
	//}
	else
		std::cout << std::fixed << std::setprecision(1) << this->f_arg << "f" << std::endl;
}


void Convert::getCArg() const {
	std::cout << "char: ";
	if (type == PSEUDOLIT)
		std::cout << "impossible" << std::endl;
	else if (c_arg >= 32 && c_arg <= 126)
		std::cout << c_arg << std::endl;
	else
		std::cout << "Non displayable" << std::endl;
}

void Convert::getDArg() const {
	std::cout << "double: ";
	if (this->type == PSEUDOLIT)
		std::cout << this->def <<std::endl;
	else
		std::cout << d_arg << std::endl;
}

int Convert::getType() const {
	return type;
}

void Convert::setType(int type) {
	Convert::type = type;
}

const std::string &Convert::getDef() const {
	return def;
}

void Convert::setDef(const std::string &def) {
	this->def = def;
}

void Convert::print_data() {
	getCArg();
	getIArg();
	getFArg();
	getDArg();
}

bool isLiteral(std::string str)
{
	if (str == "nan"|| str == "nanf" || str == "+inff" || str == "-inff" || str == "-inf" || str == "+inf")
		return true;
	return false;
}
