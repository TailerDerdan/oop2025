#include "CFunction.h"
#include <cmath>

CFunction::CFunction(std::shared_ptr<IValueGetter> leftOperand, 
	std::shared_ptr<IValueGetter> rightOperand, OperationType operation)
{
	m_leftOperand = leftOperand;
	m_rightOperand = rightOperand;
	m_operation = operation;
}

CFunction::CFunction(std::shared_ptr<IValueGetter> leftOperand)
{
	m_leftOperand = leftOperand;
	m_operation = OperationType::NONE;
}

double CFunction::GetValue()
{
	if (m_cachedValue.has_value())
	{
		return m_cachedValue.value();
	}

	return Calculate();
}

void CFunction::Update()
{
	m_cachedValue.reset();
}

double CFunction::Calculate()
{
	if (std::isnan(m_leftOperand->GetValue()) || std::isnan(m_rightOperand->GetValue()))
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

	if (m_operation == OperationType::NONE)	return m_leftOperand->GetValue();

	double result = 0.0;
	if (m_operation == OperationType::ADD)
	{
		result = m_leftOperand->GetValue() + m_rightOperand->GetValue();
	}
	if (m_operation == OperationType::SUB)
	{
		result = m_leftOperand->GetValue() - m_rightOperand->GetValue();
	}
	if (m_operation == OperationType::MUL)
	{
		result = m_leftOperand->GetValue() * m_rightOperand->GetValue();
	}
	if (m_operation == OperationType::DIV)
	{
		if (m_rightOperand->GetValue() == 0)
			return std::numeric_limits<double>::quiet_NaN();

		result = m_leftOperand->GetValue() / m_rightOperand->GetValue();
	}
	m_cachedValue = result;
	return result;
}