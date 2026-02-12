#pragma once

#include <map>
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
	std::shared_ptr<IValue> GetIdentificator(const std::string& name);

	std::map<std::string, std::shared_ptr<CVariable>> GetVariables();
	std::map<std::string, std::shared_ptr<CFunction>> GetFunctions();

private:
	std::map<std::string, std::shared_ptr<CVariable>> m_variables;
	std::map<std::string, std::shared_ptr<CFunction>> m_functions;
};