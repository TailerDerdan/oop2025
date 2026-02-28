#pragma once

#include <fstream>
#include <functional>
#include <unordered_map>

#include "Calculator.h"

using ActionMap = std::unordered_map<std::string, std::function<void()>>;

class CalculatorUI
{
public:
	CalculatorUI(std::istream& input, std::ostream& output, Calculator& calculator);

	void HandleCommand();

private:
	static void ParseVarDefination(const std::string& line, std::string& leftOperand, std::string& rightOperand);
	static void ParseFuncDefination(const std::string& line, std::string& funcName,
		std::string& leftOperand, std::optional<std::string>& rightOperand, std::optional<OperationType>& op);

	void DefineVariable();
	void UpdateVariable();
	void DefineFunction();

	void PrintIdentifier();
	void PrintVariables() const;
	void PrintFunctions() const;

	static OperationType ConvertOperation(const std::string& operationStr);
	static bool IsValidIdentifier(const std::string& name);

private:
	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_actionMap;
};