#pragma once

#include <unordered_set>

#include "CObservable.h"
#include "IValue.h"

class CVariable : public IValue, public CObservable, public std::enable_shared_from_this<CVariable>
{
public:
	CVariable();

	void SetValue(double value);
	double GetValue() override;
	Dependencies GetDependencies() override;

private:
	double m_value;
};