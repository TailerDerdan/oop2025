#pragma once

#include "Car.h"
#include <functional>
#include <map>
#include <iostream>
#include <vector>

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
	void SetGear
	bool HandleCommandWithParams(const std::string& line);

private:
	Car m_car;

	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<bool>();

	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;
};