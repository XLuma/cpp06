//
// Created by Louis-gabriel Laplante on 2022-06-27.
//

#ifndef EX01_DATA_H
#define EX01_DATA_H

#include <string>

class Data {

private:
	std::string _someData;

public:
	Data();

	Data(const Data &rhs);

	Data &operator=(const Data &rhs);

	~Data();
	void setData(std::string str);
	std::string getData();

};


#endif //EX01_DATA_H
