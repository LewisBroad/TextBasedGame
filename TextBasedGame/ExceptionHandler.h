#include "iostream"
#include <stdexcept>
using namespace std;

#pragma once
class ExceptionHandler:public exception
{
protected:
	string message;
public:
	explicit ExceptionHandler(const string& message) : message(message) {}
	const char* what() const override { //override the what function so that other classes can use it
		return message.c_str();
	}
};
class invalidActionExeption :public ExceptionHandler
{
public:
	invalidActionExeption() :ExceptionHandler("Invalid action") {} 
};

