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
}

void CVariable::RegisterObserver(std::weak_ptr<IObserver> observer)
{
	m_observers.push_back(observer);
}

void CVariable::NotifyObserver()
{
	for (auto obs : m_observers)
	{
		if (!obs.expired())
		{
			obs.lock().get()->Update();
		}
	}
}