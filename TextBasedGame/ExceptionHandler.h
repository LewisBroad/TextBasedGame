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
	const char* what() const noexcept override {
		return message.c_str();
	}
};
class invalidActionExeption :public ExceptionHandler
{
public:
	invalidActionExeption() :ExceptionHandler("Invalid action") {}
};

