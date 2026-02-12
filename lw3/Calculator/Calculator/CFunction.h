#pragma once

#include <optional>

#include "IValue.h"
#include "IObservable.h"
#include "IObserver.h"

enum class OperationType
{
	NONE,
	ADD,
	SUB,
	MUL,
	DIV
};

class CFunction : public IValue, public IObserver
{
public:
	CFunction(std::shared_ptr<IValue> leftOperand, 
		std::shared_ptr<IValue> rightOperand, OperationType operation);
	CFunction(std::shared_ptr<IValue> leftOperand);

	double GetValue() override;
	void Update() override;

private:
	double Calculate();

private:
	std::shared_ptr<IValue> m_leftOperand;
	std::shared_ptr<IValue> m_rightOperand;
	OperationType m_operation;
	std::optional<double> m_cachedValue;
};