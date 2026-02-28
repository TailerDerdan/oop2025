#pragma once

#include <unordered_map>
#include <string>

#include "CFunction.h"
#include "CVariable.h"

class Calculator
{
public:
	Calculator() = default;

	void DefineVariable(const std::string& name);
	void SetVariableValue(const std::string& name, double val);
	void DefineFunction(const std::string& name, const std::string& left, 
		std::optional<OperationType>& op, const std::optional<std::string>& right);
	std::shared_ptr<IValue> GetIdentifier(const std::string& name);

	std::unordered_map<std::string, std::shared_ptr<CVariable>> GetVariables();
	std::unordered_map<std::string, std::shared_ptr<CFunction>> GetFunctions();

private:
	std::shared_ptr<IValue> FindIdentifier(const std::string& name);

private:
	std::unordered_map<std::string, std::shared_ptr<CVariable>> m_variables;
	std::unordered_map<std::string, std::shared_ptr<CFunction>> m_functions;
};