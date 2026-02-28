#pragma once
#include "IObservable.h"

using Dependencies = std::unordered_set<std::shared_ptr<IObservable>>;

class IValue
{
public:
	virtual double GetValue() = 0;
	//using
	virtual Dependencies GetDependencies() = 0;

	virtual ~IValue() = default;
};
