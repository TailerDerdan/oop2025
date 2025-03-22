#pragma once

#include "Car.h"
#include <functional>
#include <iostream>
#include <vector>

// синхронизировать имя файла и имя класса
class GUIOfCar
{
public:
	GUIOfCar(std::istream& input, std::ostream& output);

	void DialogWithUser();

private:
	void OutputGear();
	void OutputStateEngine();
	void OutputDirection();
	void Info();
	bool HandleCommandWithParams(const std::string& line);

private:
	Car m_car;

	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<bool>();

	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;
};