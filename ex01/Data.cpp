//
// Created by Louis-gabriel Laplante on 2022-06-27.
//

#include "Data.h"

Data::Data() {
	_someData = "";
}

Data::Data(const Data &rhs) {
	_someData = rhs._someData;
}

Data &Data::operator=(const Data &rhs) {
	if (this == &rhs)
		return *this;

	//copy;
	return *this;
}

Data::~Data() {
}

void Data::setData(std::string str) {
	this->_someData = str;
}

std::string Data::getData() {
	return this->_someData;
}