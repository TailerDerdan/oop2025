#include "CVariable.h"

CVariable::CVariable()
{
	m_value = std::numeric_limits<double>::quiet_NaN();
}

double CVariable::GetValue()
{
	return m_value;
}

void CVariable::SetValue(double value)
{
	m_value = value;
	NotifyObserver();
}

Dependencies CVariable::GetDependencies()
{
	return { shared_from_this() };
}