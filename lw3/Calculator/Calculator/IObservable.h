#pragma once

#include <memory>

#include "IObserver.h"

class IObservable
{
public:
	virtual void RegisterObserver(std::weak_ptr<IObserver> observer) = 0;
	virtual void NotifyObserver() = 0;

	virtual ~IObservable() = default;
};