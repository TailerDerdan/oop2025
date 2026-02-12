#include "Calculator.h"
#include <stdexcept>

void Calculator::DefineVariable(const std::string& name)
{
	if (m_variables.find(name) == m_variables.end())
	{
		throw std::invalid_argument("Identifier just found: " + name);
	}
	std::shared_ptr<CVariable> newVar;
	m_variables.insert({ name, newVar });
}

void Calculator::SetVariableValue(const std::string& name, double val)
{
	auto iterVar = m_variables.find(name);
	if (iterVar == m_variables.end())
	{
		std::shared_ptr<CVariable> newVar;
		newVar->SetValue(val);
		m_variables.insert({ name, newVar });
		return;
	}
	iterVar->second->SetValue(val);
}

void Calculator::DefineFunction(const std::string& name, const std::string& left, 
	std::optional<OperationType>& op, const std::optional<std::string>& right)
{	
	if (m_functions.find(name) == m_functions.end())
	{
		throw std::invalid_argument("Identifier just found: " + name);
	}

	auto iterLeft = m_variables.find(left);
	if (iterLeft == m_variables.end())
	{
		throw std::invalid_argument("Identifier not found: " + left);
	}

	if (right.has_value())
	{
		if (!op.has_value())
		{
			throw std::invalid_argument("Operation not found");
		}

		auto iterRight = m_variables.find(right.value());
		if (iterRight == m_variables.end())
		{
			throw std::invalid_argument("Identifier not found: " + right.value());
		}

		std::shared_ptr<CFunction> newFunc = std::make_shared<CFunction>(iterLeft->second, iterRight->second, op);
		m_functions.insert({ name, newFunc });
		return;
	}

	std::shared_ptr<CFunction> newFunc = std::make_shared<CFunction>(iterLeft->second);
	m_functions.insert({ name, newFunc });
	return;
}

std::shared_ptr<IValueGetter> Calculator::GetIdentificator(const std::string& name)
{
	auto var = m_variables.find(name);
	if (var != m_variables.end())
	{
		return var->second;
	}

	auto func = m_functions.find(name);
	if (func != m_functions.end())
	{
		return func->second;
	}

	throw std::invalid_argument("Identifier not found: " + name);
}

std::map<std::string, std::shared_ptr<CVariable>> Calculator::GetVariables()
{
	return m_variables;
}

std::map<std::string, std::shared_ptr<CFunction>> Calculator::GetFunctions()
{
	return m_functions;
}