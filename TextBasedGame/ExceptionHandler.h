#include "iostream"
#include <stdexcept>
using namespace std;

#pragma once
class ExceptionHandler:public exception
{
protected:
	string message;
public:
	explicit ExceptionHandler(string& message) : message(message) {}
	const char * what(){
		return message.c_str();
	}
};
class invalidActionExeption :public ExceptionHandler
{
public:
	invalidActionExeption() :ExceptionHandler("Invalid action") {}
};

