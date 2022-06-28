//
// Created by Louis-gabriel Laplante on 2022-06-21.
//

#include "Convert.h"

// -- CLASS CONSTRUCTORS AND DESTRUCTORS -- //
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

// -- Type discovery and conversion -- //
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
		else if (std::isdigit(arg[i]))
			has_num = 1;
		else if (arg[i] == '.')
			has_dot = 1;
		else if (arg[i] == 'f' && i == (int)std::strlen(arg))
			has_f = 1;
		if (std::isalpha(arg[i]))
			has_letter = 1;
		i++;
	}
	if (i == 1)
	{
		this->setType(CHAR);
		this->c_arg = atoi(this->def.c_str());
	}
	else if (has_num == 1 && has_dot == 1 && has_f == 1) {
		this->setType(FLOAT);
		this->f_arg = std::stof(this->def);
	}
	else if (has_num == 1 && has_dot == 1 && has_f == 0) {
		this->setType(DOUBLE);
		this->d_arg = std::stod(this->def);
	}
	else if (has_num == 1 && has_dot == 0 && has_f == 0 && has_letter == 0) {
		this->setType(INT);
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

// -- Checks against each type for printing -- //
void Convert::getIArg() const {
	std::cout << "int: ";
	if (this->type == PSEUDOLIT || this->type == INVALID)
		std::cout << "impossible" << std::endl;
	else if (this->isWrong == true)
		std::cout << "overflow" << std::endl;
	else if (std::stol(this->def) < INT_MIN || std::stol(this->def) > INT_MAX)
		std::cout << "overflow" << std::endl;
	else
		std::cout << this->i_arg << std::endl;
}

void Convert::getFArg() const {
	std::cout << "float: ";
	if (this->type == PSEUDOLIT) {
		if (this->def == "-inf" || this->def == "+inf" || this->def == "nan")
			std::cout << this->def << "f" << std::endl;
		else
			std::cout << this->def << std::endl;
	}
	else if (this->type == INVALID)
		std::cout << "impossible" << std::endl;
	else if (std::stol(this->def) >= INT_MIN && std::stol(this->def) <= INT_MAX)
	{
		std::cout << std::fixed << std::setprecision(1) << this->f_arg << "f" << std::endl;
	}
	else
		std::cout << this->def << "f" << std::endl;
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
	if (this->type == PSEUDOLIT) {
		std::cout << convertLiteralToDouble(this->def) << std::endl;
	}
	else if (this->type == INVALID)
		std::cout << "impossible" << std::endl;
	else if (std::stol(this->def) >= INT_MIN && std::stol(this->def) <= INT_MAX)
	{
		std::cout << std::fixed << std::setprecision(1) << this->d_arg << std::endl;
	}
	else
		std::cout << this->def << std::endl;
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

// -- External Functions -- //
bool isLiteral(std::string str)
{
	if (str == "nan"|| str == "nanf" || str == "+inff" || str == "-inff" || str == "-inf" || str == "+inf")
		return true;
	return false;
}

std::string convertLiteralToDouble(std::string str)
{
	if (str == "nanf")
		return "nan";
	if (str == "+inff")
		return "+inf";
	if (str == "-inff")
		return "-inf";
	return str;
}
