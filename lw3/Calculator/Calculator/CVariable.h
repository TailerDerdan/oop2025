#pragma once

#include <vector>

#include "IValueGetter.h"
#include "IObservable.h"
#include "IObserver.h"

class CVariable : public IValueGetter, public IObservable
{
public:
	CVariable();

	void SetValue(double value);

	double GetValue() override;

	void RegisterObserver(std::weak_ptr<IObserver> observer) override;
	void NotifyObserver() override;

private:
	double m_value;
	std::vector<std::weak_ptr<IObserver>> m_observers;
};