#include "CFunction.h"
#include <cmath>
#include <utility>

CFunction::CFunction(std::shared_ptr<IValue> leftOperand,
	std::shared_ptr<IValue> rightOperand, OperationType operation)
{
	m_leftOperand = std::move(leftOperand);
	m_rightOperand = std::move(rightOperand);
	m_operation = operation;
}

CFunction::CFunction(std::shared_ptr<IValue> leftOperand)
{
	m_leftOperand = std::move(leftOperand);
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
	NotifyObserver();
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
		{
			return std::numeric_limits<double>::quiet_NaN();
		}

		result = m_leftOperand->GetValue() / m_rightOperand->GetValue();
	}
	m_cachedValue = result;
	return result;
}

//IValue -> IObservable
void CFunction::InitDependencies()
{
	if (auto obs = std::dynamic_pointer_cast<IObservable>(m_leftOperand))
	{
		m_dependencies.insert(obs);
	}

	if (m_rightOperand)
	{
		if (auto obs = std::dynamic_pointer_cast<IObservable>(m_rightOperand))
		{
			m_dependencies.insert(obs);
		}
	}
}

void CFunction::SubscribeToDependencies()
{
	InitDependencies();

	for (const auto& dependency : m_dependencies)
	{
		dependency->RegisterObserver(shared_from_this());
	}
}

Dependencies CFunction::GetDependencies()
{
	return m_dependencies;
}