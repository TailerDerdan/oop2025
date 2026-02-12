#include <regex>

#include "CalculatorUI.h"

CalculatorUI::CalculatorUI(std::ifstream& input, std::ofstream& output, Calculator& calculator)
	: m_input(input)
	, m_output(output)
	, m_calculator(calculator)
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

	auto commandIter = m_actionMap.find(command);
	if (commandIter != m_actionMap.end())
	{
		try
		{
			commandIter->second();
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
		return;
	}
	else
	{
		m_output << "Unknow command!" << std::endl;
	}
}

void CalculatorUI::PrintVariables() const
{
	for (auto var : m_calculator.GetVariables())
	{
		m_output << var.first << ":" << var.second->GetValue();
	}
}

void CalculatorUI::PrintFunctions() const
{
	for (auto func : m_calculator.GetFunctions())
	{
		m_output << func.first << ":" << func.second->GetValue();
	}
}

void CalculatorUI::PrintIdentifier()
{
	std::string identifier;
	m_input >> identifier;

	if (!IsValidIdentifier(identifier))
	{
		m_output << "Is not valid identifier!" << std::endl;
		return;
	}

	try
	{
		m_calculator.GetIdentificator(identifier);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
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

	try
	{
		m_calculator.DefineVariable(identifier);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorUI::UpdateVariable()
{
	std::string line;
	m_input >> line;

	std::string rightOperand;
	std::string leftOperand;
	double value;

	ParseVarDefination(line, leftOperand, rightOperand);

	if (CalculatorUI::IsValidIdentifier(rightOperand))
	{
		value = m_calculator.GetIdentificator(rightOperand)->GetValue();
	}
	else
	{
		value = (round(stod(rightOperand) * 100) / 100);
	}

	try
	{
		m_calculator.SetVariableValue(leftOperand, value);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

void CalculatorUI::ParseVarDefination(const std::string& line, std::string& leftOperand, std::string& rightOperand)
{
	static const std::regex pattern(
		R"(^\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([+-]?(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?|[a-zA-Z_][a-zA-Z0-9_]*)\s*$)"
	);
}

void CalculatorUI::ParseFuncDefination(const std::string& line, std::string& funcName,
	std::string& leftOperand, std::optional<std::string>& rightOperand)
{

}

bool CalculatorUI::IsValidIdentifier(const std::string& name)
{
	static const std::regex pattern("^[a-zA-Z_][a-zA-Z0-9_]*$");
	return std::regex_match(name, pattern);
}