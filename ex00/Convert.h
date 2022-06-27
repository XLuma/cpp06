//
// Created by Louis-gabriel Laplante on 2022-06-21.
//

#ifndef PISCINE_CP_CONVERSION_H
#define PISCINE_CP_CONVERSION_H

#include <iostream>
#include <iomanip>
#include <string>

#define CHAR 1
#define FLOAT 2
#define DOUBLE 3
#define INT 4
#define INVALID 5
#define PSEUDOLIT 6


class Convert {
private:
	int i_arg;
	float f_arg;
	char c_arg;
	double d_arg;
	std::string def;
	int type;
	bool isWrong;
public:
	Convert();

	Convert(const std::string &def);

	Convert(const Convert &convert);
	~Convert();
	Convert & operator=(const Convert &rhs);

	void detect_type(char *arg);
	void convert_data();
	void print_data();
	void getIArg() const;
	void getFArg() const;
	void getCArg() const;
	void getDArg() const;
	int getType() const;
	void setType(int type);

	const std::string &getDef() const;

	void setDef(const std::string &def);
};
bool isLiteral(std::string str);
std::string convertLiteralToDouble(std::string str);
#endif //PISCINE_CP_CONVERSION_H
