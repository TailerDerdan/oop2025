#include <regex>

#include "CalculatorUI.h"

CalculatorUI::CalculatorUI(std::istream& input, std::ostream& output, Calculator& calculator)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
{
	m_actionMap.emplace("printvars", [this]() { PrintVariables(); });
	m_actionMap.emplace("printfns", [this]() { PrintFunctions(); });
	m_actionMap.emplace("print", [this]() { PrintIdentifier(); });
	m_actionMap.emplace("var", [this]() { DefineVariable(); });
	m_actionMap.emplace("let", [this]() { UpdateVariable(); });
	m_actionMap.emplace("fn", [this]() { DefineFunction(); });
}

void CalculatorUI::HandleCommand()
{
	std::string command;
	m_input >> command;

	if (const auto commandIter = m_actionMap.find(command); commandIter != m_actionMap.end())
	{
		try
		{
			commandIter->second();
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
	}
	else
	{
		m_output << "Unknow command!" << std::endl;
	}
}

void CalculatorUI::PrintVariables() const
{
	m_output.setf(std::ios::fixed);
	m_output.precision(2);

	for (const auto&[fst, snd] : m_calculator.GetVariables())
	{
		m_output << fst << ":" << std::fixed << std::setprecision(2) << snd->GetValue() << std::endl;
	}
}

void CalculatorUI::PrintFunctions() const
{
	m_output.setf(std::ios::fixed);
	m_output.precision(2);

	for (const auto&[fst, snd] : m_calculator.GetFunctions())
	{
		m_output << fst << ":" << std::fixed << std::setprecision(2) << snd->GetValue() << std::endl;
	}
}

void CalculatorUI::PrintIdentifier()
{
	std::string identifier;
	m_input >> identifier;

	std::string value;

	if (!IsValidIdentifier(identifier))
	{
		m_output << "Is not valid identifier!" << std::endl;
		return;
	}

	const auto valueFromCalculator = m_calculator.GetIdentifier(identifier);

	m_output.setf(std::ios::fixed);
	m_output.precision(2);

	m_output << valueFromCalculator->GetValue() << std::endl;
}

void CalculatorUI::DefineVariable()
{
	std::string identifier;
	m_input >> identifier;

	if (!IsValidIdentifier(identifier))
	{
		m_output << "Is not valid identifier!" << std::endl;
		return;
	}

	m_calculator.DefineVariable(identifier);
}

void CalculatorUI::UpdateVariable()
{
	std::string line;
	m_input >> line;

	std::string rightOperand;
	std::string leftOperand;
	double value;

	ParseVarDefination(line, leftOperand, rightOperand);

	if (IsValidIdentifier(rightOperand))
	{
		value = m_calculator.GetIdentifier(rightOperand)->GetValue();
	}
	else
	{
		value = (round(stod(rightOperand) * 100) / 100);
	}

	m_calculator.SetVariableValue(leftOperand, value);
}

void CalculatorUI::DefineFunction()
{
	std::string line;
	m_input >> line;

	std::string funcName;
	std::string leftOperand;
	std::optional<OperationType> operation;
	std::optional<std::string> rightOperand;

	ParseFuncDefination(line, funcName, leftOperand, rightOperand, operation);

	m_calculator.DefineFunction(funcName, leftOperand, operation, rightOperand);
}

void CalculatorUI::ParseVarDefination(const std::string& line, std::string& leftOperand, std::string& rightOperand)
{
	static const std::regex regex(
		R"(^\s*)"
		R"(([a-zA-Z_][a-zA-Z0-9_]*))"
		R"(\s*=\s*)"
		R"(([+-]?(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?)"
		R"(|[a-zA-Z_][a-zA-Z0-9_]*))"
		R"(\s*$)"
	);

	std::smatch matches;
	if (!std::regex_match(line, matches, regex))
	{
		throw std::invalid_argument("Invalid syntax in var: " + line);
	}
	leftOperand  = matches[1].str();
	rightOperand = matches[2].str();
}

void CalculatorUI::ParseFuncDefination(const std::string& line, std::string& funcName,
	std::string& leftOperand, std::optional<std::string>& rightOperand, std::optional<OperationType>& op)
{
	static const std::regex regex(
		R"(^\s*)"
		R"(([a-zA-Z_][a-zA-Z0-9_]*))"
		R"(\s*=\s*)"
		R"(([a-zA-Z_][a-zA-Z0-9_]*))"
		R"((?:\s*([\+\-\*\/])\s*)"
		R"(([a-zA-Z_][a-zA-Z0-9_]*))?)"
		R"(\s*$)"
	);

	std::smatch matches;
	if (!std::regex_match(line, matches, regex))
	{
		throw std::invalid_argument("Invalid syntax in func: " + line);
	}

	funcName = matches[1].str();
	leftOperand = matches[2].str();
	op = matches[3].matched ? std::optional(ConvertOperation(matches[3].str())) : std::nullopt;
	rightOperand = matches[4].matched ? std::optional(matches[4].str()) : std::nullopt;
}

bool CalculatorUI::IsValidIdentifier(const std::string& name)
{
	static const std::regex regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
	return std::regex_match(name, regex);
}

OperationType CalculatorUI::ConvertOperation(const std::string& operationStr)
{
	if (operationStr == "+")
	{
		return OperationType::ADD;
	}
	if (operationStr == "-")
	{
		return OperationType::SUB;
	}
	if (operationStr == "*")
	{
		return OperationType::MUL;
	}
	if (operationStr == "/")
	{
		return OperationType::DIV;
	}
	return OperationType::NONE;
}