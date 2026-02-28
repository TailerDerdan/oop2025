#pragma once

#include <optional>
#include <unordered_set>

#include "CObservable.h"
#include "IValue.h"
#include "IObserver.h"

enum class OperationType
{
	NONE,
	ADD,
	SUB,
	MUL,
	DIV
};

class CFunction : public IValue,
				public IObserver,
				public CObservable,
				public std::enable_shared_from_this<CFunction>
{
public:
	CFunction(std::shared_ptr<IValue> leftOperand, 
		std::shared_ptr<IValue> rightOperand, OperationType operation);

	explicit CFunction(std::shared_ptr<IValue> leftOperand);

	double GetValue() override;
	void Update() override;

	void SubscribeToDependencies();
	Dependencies GetDependencies() override;

private:
	void InitDependencies();
	double Calculate();

private:
	std::shared_ptr<IValue> m_leftOperand;
	std::shared_ptr<IValue> m_rightOperand;
	OperationType m_operation;
	std::optional<double> m_cachedValue;
	Dependencies m_dependencies;
};