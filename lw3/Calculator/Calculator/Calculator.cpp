#include "Calculator.h"

#include <ostream>
#include <stdexcept>

void Calculator::DefineVariable(const std::string& name)
{
	if (m_variables.contains(name))
	{
		throw std::invalid_argument("Identifier just found: " + name);
	}
	auto newVar = std::make_shared<CVariable>();
	m_variables.insert({ name, newVar });
}

void Calculator::SetVariableValue(const std::string& name, double val)
{
	const auto iterVar = m_variables.find(name);
	if (iterVar == m_variables.end())
	{
		auto newVar = std::make_shared<CVariable>();
		newVar->SetValue(val);
		m_variables.insert({ name, newVar });
		return;
	}
	iterVar->second->SetValue(val);
}

void Calculator::DefineFunction(const std::string& name, const std::string& left,
	std::optional<OperationType>& op, const std::optional<std::string>& right)
{	
	if (m_functions.contains(name))
	{
		throw std::invalid_argument("Identifier just found: " + name);
	}

	auto iterLeft = FindIdentifier(left);

	std::shared_ptr<CFunction> newFunc;
	if (right.has_value())
	{
		if (!op.has_value())
		{
			throw std::invalid_argument("Operation not found");
		}

		const auto iterRight = FindIdentifier(right.value());

		newFunc = std::make_shared<CFunction>(iterLeft, iterRight, op.value());
	}
	else
	{
		newFunc = std::make_shared<CFunction>(iterLeft);
	}

	m_functions.emplace(name, newFunc);
	newFunc->SubscribeToDependencies();
}

std::shared_ptr<IValue> Calculator::GetIdentifier(const std::string& name)
{
	if (const auto var = m_variables.find(name); var != m_variables.end())
	{
		return var->second;
	}

	if (const auto func = m_functions.find(name); func != m_functions.end())
	{
		return func->second;
	}

	throw std::invalid_argument("Identifier not found: " + name);
}

std::unordered_map<std::string, std::shared_ptr<CVariable>> Calculator::GetVariables()
{
	return m_variables;
}

std::unordered_map<std::string, std::shared_ptr<CFunction>> Calculator::GetFunctions()
{
	return m_functions;
}

std::shared_ptr<IValue> Calculator::FindIdentifier(const std::string& name)
{
	if (const auto iterVar = m_variables.find(name); iterVar != m_variables.end())
	{
		return iterVar->second;
	}
	if (const auto iterFn = m_functions.find(name); iterFn != m_functions.end())
	{
		return iterFn->second;
	}

	throw std::invalid_argument("Identifier not found: " + name);
}