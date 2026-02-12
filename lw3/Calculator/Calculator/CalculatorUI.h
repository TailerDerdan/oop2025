#pragma once

#include <fstream>
#include <functional>
#include <unordered_map>

#include "Calculator.h"

using ActionMap = std::unordered_map<std::string, std::function<void>()>;

class CalculatorUI
{
public:
	CalculatorUI(std::ifstream& input, std::ofstream& output, Calculator& calculator);

	void HandleCommand();

private:
	void ParseVarDefination(const std::string& line, std::string& leftOperand, std::string& rightOperand);
	void ParseFuncDefination(const std::string& line, std::string& funcName, 
		std::string& leftOperand, std::optional<std::string>& rightOperand);

	void DefineVariable();
	void UpdateVariable();
	void DefineFunction();

	void PrintIdentifier();
	void PrintVariables() const;
	void PrintFunctions() const;

	OperationType ConvertOperation(const std::string& operationStr);
	bool IsValidIdentifier(const std::string& name);

private:
	Calculator& m_calculator;
	std::ifstream& m_input;
	std::ofstream& m_output;
	ActionMap m_actionMap;
};